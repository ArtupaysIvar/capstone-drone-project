#include <rclcpp/rclcpp.hpp>
#include "pixel_msgs/msg/pixel_coordinates.hpp"
#include "geometry_msgs/msg/point.hpp"
#include <px4_msgs/msg/vehicle_odometry.hpp>
#include <px4_msgs/msg/vehicle_global_position.hpp>
# include <geometry_msgs/msg/point.hpp>
#include <Eigen/Dense>
#include <cmath>
#include <vector>
#include <chrono>
// #include "sensor_msgs/msg/camera_info.hpp"
// #include <sensor_msgs/msg/nav_sat_fix.hpp>
// #include <Eigen/Cholesky>
// #include <Eigen/Eigenvalues>

class DataCollectionNode : public rclcpp::Node
{   
public:
    // constructor
    DataCollectionNode();

private:
};

DataCollectionNode::DataCollectionNode() : Node("data_collection_node")
    {
        drone1_pix_subs = this->create_subscription<pixel_msgs::msg::PixelCoordinates>
        ("/pixel_topic1", 10, std::bind(&DataCollectionNode::pixelCallback1, this, 
        std::placeholders::_1));
        drone2_pix_subs = this->create_subscription<pixel_msgs::msg::PixelCoordinates>
        ("/pixel_topic2", 10, std::bind(&DataCollectionNode::pixelCallback2, this, 
        std::placeholders::_1));
        drone3_pix_subs = this->create_subscription<pixel_msgs::msg::PixelCoordinates>
        ("/pixel_topic3", 10, std::bind(&DataCollectionNode::pixelCallback3, this, 
        std::placeholders::_1));
        
        auto qos1 = rclcpp::QoS(rclcpp::KeepLast(10))
            .best_effort()
            .durability_volatile();

        drone1_gps_sub1 = this->create_subscription<geometry_msgs::msg::Point>
        ("/point_location", qos1, std::bind(&DataCollectionNode::triangulationCallback, this, 
        std::placeholders::_1));
                        
        auto qos2 = rclcpp::QoS(rclcpp::KeepLast(10))
            .best_effort()
            .transient_local();

        drone1_conf_subs = this->create_subscription<px4_msgs::msg::VehicleOdometry>
        ("/px4_1/fmu/out/vehicle_odometry", qos2, std::bind(&DataCollectionNode::odomCallback1, this, 
        std::placeholders::_1));
        drone2_conf_subs = this->create_subscription<px4_msgs::msg::VehicleOdometry>
        ("/px4_2/fmu/out/vehicle_odometry", qos2, std::bind(&DataCollectionNode::odomCallback2, this, 
        std::placeholders::_1));
        drone3_conf_subs = this->create_subscription<px4_msgs::msg::VehicleOdometry>
        ("/px4_3/fmu/out/vehicle_odometry", qos2, std::bind(&DataCollectionNode::odomCallback3, this, 
        std::placeholders::_1));
        
        csv_file_.open("triangulation_data.csv", std::ios::out | std::ios::trunc);
    if (!csv_file_.is_open()) {
        RCLCPP_ERROR(this->get_logger(), "Failed to open triangulation_data.csv for writing.");
    } else {
        csv_file_ << "mission_time_s, target_location, detected, x1, x2, x3, y1, y2, y3, z1, z2, z3\n";
        csv_file_ << std::fixed << std::setprecision(6);
        RCLCPP_INFO(this->get_logger(), "Writing data to triangulation_data.csv");
    }

    };
DataCollectionNode::~DataCollectionNode()
{
    if (csv_file_.is_open()) {
        csv_file_.close();
    }
}

void DataCollectionNode::triangulationCallback(const geometry_msgs::msg::Point::SharedPtr point_msg){
    target_location << point_msg->x, point_msg->y, point_msg->z;
}
void DataCollectionNode::pixelCallback1(const pixel_msgs::msg::PixelCoordinates::SharedPtr YOLOmsg1){
    conf1 = YOLOmsg1->confidence;
    pixel_vec1 << YOLOmsg1->u, YOLOmsg1->v, 1.0;
    if(conf1 > 0.5){
        pixel1_received = true;;
    }
}
void DataCollectionNode::pixelCallback2(const pixel_msgs::msg::PixelCoordinates::SharedPtr YOLOmsg2){
    conf2 = YOLOmsg2->confidence;
    pixel_vec2 << YOLOmsg2->u, YOLOmsg2->v, 1.0;
    if(conf2 > 0.5){
        pixel2_received = true;
    }
}
void DataCollectionNode::pixelCallback3(const pixel_msgs::msg::PixelCoordinates::SharedPtr YOLOmsg3){
    conf3 = YOLOmsg3->confidence;
    pixel_vec3 << YOLOmsg3->u, YOLOmsg3->v, 1.0;
    if(conf3 > 0.5){
        pixel3_received = true;
    }
}

void DataCollectionNode::odomCallback1(const px4_msgs::msg::VehicleOdometry::SharedPtr odom_msg1){
    x1 = odom_msg1->position[0];
    y1 = odom_msg1->position[1];
    z1 = odom_msg1->position[2];
    odom1_received = true;
    if (odom1_received && odom2_received && odom3_received) {
        csvLogging();
    }
}

void DataCollectionNode::odomCallback2(const px4_msgs::msg::VehicleOdometry::SharedPtr odom_msg2){
    x2 = odom_msg2->position[0];
    y2 = odom_msg2->position[1];
    z2 = odom_msg2->position[2];
    odom2_received = true;
    if (odom1_received && odom2_received && odom3_received) {
        csvLogging();
    }
}

void DataCollectionNode::odomCallback3(const px4_msgs::msg::VehicleOdometry::SharedPtr odom_msg3){
    x3 = odom_msg3->position[0];
    y3 = odom_msg3->position[1];
    z3 = odom_msg3->position[2];
    odom3_received = true;
    if (odom1_received && odom2_received && odom3_received) {
        csvLogging();
    }
}

void DataCollectionNode::csvLogging(){
    if(pixel1_received || pixel2_received || pixel3_received){
        detected = 1;
    }
    if (csv_file_.is_open()) {
        csv_file_ << mission_time_s << ","
                  << target_location << ","
                  << detected << ","
                  << x1+origin_drone1(0)<< "," << x2+origin_drone2(0) << "," << x3+origin_drone3(0) << ","
                  << y1+origin_drone1(1) << "," << y2+origin_drone2(1) << "," << y3+origin_drone3(1) << ","
                  << z1+origin_drone1(2) << "," << z2+origin_drone2(2) << "," << z3+origin_drone3(2) << "\n";
    } else {
        RCLCPP_ERROR(this->get_logger(), "Unable to write to CSV file.");
    }

    odom1_received = false;
    odom2_received = false;
    odom3_received = false;
}
int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<DataCollectionNode>());
    rclcpp::shutdown();
    return 0;
}
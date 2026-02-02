// #include <iostream>
// #include <ctime>
// #include <Eigen/Dense>
// #include <random>
// #include <iostream>
// #include <fstream>
// #include <ceres/ceres.h>
#include <rclcpp/rclcpp.hpp>
#include "pixel_msgs/msg/pixel_coordinates.hpp"
#include "geometry_msgs/msg/point.hpp"
#include <px4_msgs/msg/vehicle_odometry.hpp>
#include <Eigen/Cholesky>
#include <Eigen/Eigenvalues>
#include <Eigen/Jacobi>
#include <cmath>
#include <vector>
#include <chrono>

class CalcGPSNode : public rclcpp::Node
{   
public:
    // constructor
    CalcGPSNode();

private:

    // callback funcs
    void pixelCallback1(const pixel_msgs::msg::PixelCoordinates::SharedPtr YOLOmsg1);
    void pixelCallback2(const pixel_msgs::msg::PixelCoordinates::SharedPtr YOLOmsg2);
    void pixelCallback3(const pixel_msgs::msg::PixelCoordinates::SharedPtr YOLOmsg3);
    void confCallback1(const px4_msgs::msg::VehicleOdometry::SharedPtr confmsg1);
    void confCallback2(const px4_msgs::msg::VehicleOdometry::SharedPtr confmsg2);
    void confCallback3(const px4_msgs::msg::VehicleOdometry::SharedPtr confmsg3);
    bool dataCheck();
    void timerCallback();
    bool ready();
    void projectionFormula();
    bool MVMP_triangulation();


    // buat pixelCallback
    float conf1, conf2, conf3;
    
    // buat confCallback
    double drone1_xpos, drone1_ypos, drone1_zpos;
    double drone2_xpos, drone2_ypos, drone2_zpos;
    double drone3_xpos, drone3_ypos, drone3_zpos;
    Eigen::Vector3d drone1_pos_vec;
    Eigen::Vector3d drone2_pos_vec;
    Eigen::Vector3d drone3_pos_vec;
    Eigen::Quaterniond q1;
    Eigen::Quaterniond q2;
    Eigen::Quaterniond q3;
    
    // buat checking
    bool pixel1_received = false;
    bool pixel2_received = false;
    bool pixel3_received = false;
    bool odom1_received = false;
    bool odom2_received = false;
    bool odom3_received = false;

    // buat projection
    // std::vector<Eigen::Vector3d> proj_vec;
    // std::vector<Eigen::Vector3d> proj_uvec;
    // std::vector<Eigen::Matrix3d> rot_mat;
    Eigen::Vector3d pixel_vec1;
    Eigen::Vector3d pixel_vec2;
    Eigen::Vector3d pixel_vec3;
    // cam intrinsic 
    Eigen::Matrix3d cam_mat;    
    // for the cam body rotation
    Eigen::Matrix3d rot_cam_mat;
    // for the drone body rotation
    Eigen::Matrix3d rot_mat1;
    Eigen::Matrix3d rot_mat2;
    Eigen::Matrix3d rot_mat3;

    Eigen::Vector3d proj_vec1;
    Eigen::Vector3d proj_vec2;
    Eigen::Vector3d proj_vec3;

    Eigen::Vector3d proj_uvec1;
    Eigen::Vector3d proj_uvec2;
    Eigen::Vector3d proj_uvec3;
    
    // buat MVMP_triangulation
    Eigen::Matrix3d A_sum;
    Eigen::Vector3d B_sum;
    Eigen::Vector3d target_point;
    bool target_valid = false;

    // Eigen::Matrix3d A_sum = Eigen::Matrix3d::Zero();
    // Eigen::Vector3d b_sum = Eigen::Vector3d::Zero();

    // subscribers
    rclcpp::Subscription<pixel_msgs::msg::PixelCoordinates>::SharedPtr drone1_pix_subs;
    rclcpp::Subscription<pixel_msgs::msg::PixelCoordinates>::SharedPtr drone2_pix_subs;
    rclcpp::Subscription<pixel_msgs::msg::PixelCoordinates>::SharedPtr drone3_pix_subs;
    
    rclcpp::Subscription<px4_msgs::msg::VehicleOdometry>::SharedPtr drone1_conf_subs;
    rclcpp::Subscription<px4_msgs::msg::VehicleOdometry>::SharedPtr drone2_conf_subs;
    rclcpp::Subscription<px4_msgs::msg::VehicleOdometry>::SharedPtr drone3_conf_subs;

    // publisher & timer
    rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

CalcGPSNode::CalcGPSNode() : Node("calc_gps_node")
    {
        RCLCPP_INFO(this->get_logger(), "GPS approx. node started");

        drone1_pix_subs = this->create_subscription<pixel_msgs::msg::PixelCoordinates>
        ("pixel_topic1", 10, std::bind(&CalcGPSNode::pixelCallback1, this, 
        std::placeholders::_1));
        drone2_pix_subs = this->create_subscription<pixel_msgs::msg::PixelCoordinates>
        ("pixel_topic2", 10, std::bind(&CalcGPSNode::pixelCallback2, this, 
        std::placeholders::_1));
        drone3_pix_subs = this->create_subscription<pixel_msgs::msg::PixelCoordinates>
        ("pixel_topic3", 10, std::bind(&CalcGPSNode::pixelCallback3, this, 
        std::placeholders::_1));
        
        // GA MUNGKIN PAKE PIXEL MESSAGE
        drone1_conf_subs = this->create_subscription<px4_msgs::msg::VehicleOdometry>
        ("/px4_1/fmu/out/vehicle_odometry", 10, std::bind(&CalcGPSNode::confCallback1, this, 
        std::placeholders::_1));
        drone2_conf_subs = this->create_subscription<px4_msgs::msg::VehicleOdometry>
        ("/px4_2/fmu/out/vehicle_odometry", 10, std::bind(&CalcGPSNode::confCallback2, this, 
        std::placeholders::_1));
        drone3_conf_subs = this->create_subscription<px4_msgs::msg::VehicleOdometry>
        ("/px4_3/fmu/out/vehicle_odometry", 10, std::bind(&CalcGPSNode::confCallback3, this, 
        std::placeholders::_1));
       
        timer_ = this->create_wall_timer(std::chrono::milliseconds(10), std::bind(&CalcGPSNode::timerCallback, this));

        publisher_ = this->create_publisher<geometry_msgs::msg::Point>
        ("point_location", 10);
        
        double fx = 400.0, fy = 400.0, cx = 320.0, cy = 240.0;
        cam_mat << fx, 0,  cx,
                    0,  fy, cy,
                    0,  0,  1;
        // downward cam
        rot_cam_mat << 0, 1, 0,
                        1, 0, 0,
                        0, 0, -1;
    };

        // CALLBACK BUAT PIXEL
void CalcGPSNode::pixelCallback1(const pixel_msgs::msg::PixelCoordinates::SharedPtr YOLOmsg1){
        conf1 = YOLOmsg1->confidence;
        pixel_vec1 << YOLOmsg1->u, YOLOmsg1->v, 1.0;
        pixel1_received = true;
    }

void CalcGPSNode::pixelCallback2(const pixel_msgs::msg::PixelCoordinates::SharedPtr YOLOmsg2){
        conf2 = YOLOmsg2->confidence;
        pixel_vec2 << YOLOmsg2->u, YOLOmsg2->v, 1;
        pixel2_received = true;
    }

void CalcGPSNode::pixelCallback3(const pixel_msgs::msg::PixelCoordinates::SharedPtr YOLOmsg3){
        conf3 = YOLOmsg3->confidence;
        pixel_vec3 << YOLOmsg3->u, YOLOmsg3->v, 1;
        pixel3_received = true;
    }

        // CALLBACK BUAT conf
        // rotational matrix will be the functions of drone's rotation

void CalcGPSNode::confCallback1(const px4_msgs::msg::VehicleOdometry::SharedPtr confmsg1){
        // drone1_xpos = confmsg1 -> position[0];
        // drone1_ypos = confmsg1 -> position[1];
        // drone1_zpos = confmsg1 -> position[2];

        drone1_pos_vec << confmsg1 -> position[0], confmsg1 -> position[1], confmsg1 -> position[2];
        // Check if PX4 quaternion order is [w,x,y,z] or [x,y,z,w]
        q1 = Eigen::Quaterniond(confmsg1->q[0], confmsg1->q[1], confmsg1->q[2], confmsg1->q[3]);
        rot_mat1 = q1.toRotationMatrix();
        odom1_received = true;
    }

void CalcGPSNode::confCallback2(const px4_msgs::msg::VehicleOdometry::SharedPtr confmsg2){
        // drone2_xpos = confmsg2 -> position[0];
        // drone2_ypos = confmsg2 -> position[1];
        // drone2_zpos = confmsg2 -> position[2];

        drone2_pos_vec << confmsg2 -> position[0], confmsg2 -> position[1], confmsg2 -> position[2];
        q2 = Eigen::Quaterniond(confmsg2->q[0], confmsg2->q[1], confmsg2->q[2], confmsg2->q[3]);
        rot_mat2 = q2.toRotationMatrix();
        odom2_received = true;
    }

void CalcGPSNode::confCallback3(const px4_msgs::msg::VehicleOdometry::SharedPtr confmsg3){
        // drone3_xpos = confmsg3 -> position[0];
        // drone3_ypos = confmsg3 -> position[1];
        // drone3_zpos = confmsg3 -> position[2];

        drone3_pos_vec << confmsg3 -> position[0], confmsg3 -> position[1], confmsg3 -> position[2];
        q3 = Eigen::Quaterniond(confmsg3->q[0], confmsg3->q[1], confmsg3->q[2], confmsg3->q[3]);
        rot_mat3 = q3.toRotationMatrix();
        odom3_received = true;
    }

bool CalcGPSNode::dataCheck()
{
    return (pixel1_received && pixel2_received && pixel3_received &&
            odom1_received && odom2_received && odom3_received);
}


bool CalcGPSNode::ready(){
        // if(conf1>0.5 || conf2>0.5 || conf3>0.5);
        return (conf1 > 0.5f && conf2 > 0.5f && conf3 > 0.5f);
}

    // start triangulation
void CalcGPSNode::projectionFormula()
    {
        // x = K^-1 * x'
        // Eigen::Vector3d cam_mat_curr =  cam_mat_curr[0];    
        // INGETIN URUTANNYA 
        proj_vec1 =  (rot_mat1*rot_cam_mat).transpose() * cam_mat.inverse() * pixel_vec1;
        proj_vec2 =  (rot_mat2*rot_cam_mat).transpose() * cam_mat.inverse() * pixel_vec2;
        proj_vec3 =  (rot_mat3*rot_cam_mat).transpose() * cam_mat.inverse() * pixel_vec3;
        
        proj_uvec1 = proj_vec1/proj_vec1.norm();
        proj_uvec2 = proj_vec2/proj_vec2.norm();
        proj_uvec3 = proj_vec3/proj_vec3.norm();
         
    }

bool CalcGPSNode::MVMP_triangulation(){
    
    std::vector<Eigen::Vector3d> b_vec = {proj_uvec1, proj_uvec2, proj_uvec3};
    std::vector<Eigen::Vector3d> o_vec = {drone1_pos_vec, drone2_pos_vec, drone3_pos_vec};
    A_sum.setZero();
    B_sum.setZero();
    
    for (int i = 0; i < 3; ++i) {
        Eigen::Matrix3d  B = Eigen::Matrix3d::Identity() - b_vec[i] * b_vec[i].transpose();
        
        A_sum += B;
        B_sum += B * o_vec[i];
    }
     
    // target_point = A_sum.ldlt().solve(B_sum);
    // res = A_sum.jacobiSvd(Eigen::ComputeFullU | Eigen::ComputeFullV).solve(b_sum);

    // 1st check: cek determinant
    double det = A_sum.determinant();
    if (std::abs(det) < 1e-10) {
        // RCLCPP_WARN(this->get_logger(), "Triangulation failed: A_sum is near-singular (det=%.2e)", det);
        target_valid = false;
        return false;
    }

    target_point = A_sum.ldlt().solve(B_sum); // solve
    
    // 2nd check: cek solution
    if (!target_point.allFinite()) {
        // RCLCPP_WARN(this->get_logger(), "Triangulation failed: result contains NaN or Inf");
        target_valid = false;
        return false;
    }
    
    // 3rd check: check if point is in front of all cameras 
    for (int i = 0; i < 3; ++i) {
        Eigen::Vector3d to_point = target_point - o_vec[i];
        double depth = to_point.dot(b_vec[i]);
        if (depth < 0.0) {
            // RCLCPP_WARN(this->get_logger(), "Triangulation warning: point behind camera %d (depth=%.2f)", i+1, depth);
            target_valid = false;
            return false;
        }
    }

    target_valid = true;

    return true;
}

void CalcGPSNode::timerCallback(){

    if (!dataCheck()) {
    return;
    }

if (!ready()) {
    return;
    }

projectionFormula();

if (MVMP_triangulation()) {
    // publish 
    geometry_msgs::msg::Point GPSmsg;
    GPSmsg.x = target_point.x();
    GPSmsg.y = target_point.y();
    GPSmsg.z = target_point.z();
    publisher_->publish(GPSmsg);
    
    // RCLCPP_INFO(this->get_logger(), 
    //     "Published target: x=%.2f, y=%.2f, z=%.2f", 
    //     GPSmsg.x, GPSmsg.y, GPSmsg.z);
} else {
    RCLCPP_WARN(this->get_logger(), "Triangulation failed");
}
}
  /*
    if (ready() && odom1_received && odom2_received && odom3_received) {
        projectionFormula();
        if (MVMP_triangulation()) {
            geometry_msgs::msg::Point GPSmsg;
            GPSmsg.x = target_point.x();
            GPSmsg.y = target_point.y();
            GPSmsg.z = target_point.z();
            publisher_->publish(GPSmsg);
            
            RCLCPP_INFO(this->get_logger(), "Published target: x=%.2f, y=%.2f, z=%.2f", 
                       GPSmsg.x, GPSmsg.y, GPSmsg.z);
        }
    }

    */

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CalcGPSNode>());
    rclcpp::shutdown();
    return 0;
}


/*
    void timer_callback(){
        geometry_msgs::msg::Point GPSmsg;
        
        placeholder_1 = 0;
        placeholder_2 = 0;
        placeholder_3 = 0;

        GPSmsg.x = placeholder_1;
        GPSmsg.y = placeholder_2;
        GPSmsg.z = placeholder_3;

        publisher_->publish(GPSmsg);

        RCLCPP_INFO(
            this->get_logger(),
            "Published Point: x=%.2f y=%.2f z=%.2f",
            GPSmsg.x, GPSmsg.y, GPSmsg.z
        );

    }
    */

  
// #include <iostream>
// #include <ctime>
// #include <Eigen/Dense>
// #include <random>
// #include <iostream>
// #include <fstream>
#include "pixel_msgs/msg/pixel_coordinates.hpp"
#include <rclcpp/rclcpp.hpp>
#include "geometry_msgs/msg/point.hpp"
#include <ceres/ceres.h>
#include <Eigen/Cholesky>
#include <cmath>
#include <vector>


class CalcGPSNode : public rclcpp::Node
{   
public:
    //constructor
    CalcGPSNode();

private:

    void pixelCallback(
        const pixel_msgs::msg::PixelCoordinates::SharedPtr YOLOmsg);

    void projectionFormula(
        const Eigen::Vector4d& pixel_vec, 
        const Eigen::Matrix4d& transformation_mat);

    void MVMP_triangulation();

    // buat pixelCallback
    double pixel_u, pixel_v; 
    float conf;
    int placeholder_1, placeholder_2, placeholder_3; 
    
    // buat projection
    // std::vector<Eigen::Vector3d> proj_vec;
    // std::vector<Eigen::Vector3d> proj_uvec;
    // std::vector<Eigen::Vector3d> pixel_vec;
    // std::vector<Eigen::Matrix3d> rot_mat;
    
    Eigen::Vector3d proj_vec;
    Eigen::Vector3d proj_uvec;
    Eigen::Vector3d pixel_vec;
    Eigen::Matrix3d rot_mat;
    
    Eigen::Matrix3d cam_mat;    
    
    // buat MVMP_triangulation
    

    // publishers subscribers
    rclcpp::Subscription<pixel_msgs::msg::PixelCoordinates>::SharedPtr drone1_subscriber;
    rclcpp::Subscription<pixel_msgs::msg::PixelCoordinates>::SharedPtr drone2_subscriber;
    rclcpp::Subscription<pixel_msgs::msg::PixelCoordinates>::SharedPtr drone3_subscriber;
    rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr publisher_;
    // rclcpp::TimerBase::SharedPtr timer_;
};

CalcGPSNode::CalcGPSNode() : Node("calc_gps_node")
    {
        RCLCPP_INFO(this->get_logger(), "GPS approx. node started");

        drone1_subscriber = this->create_subscription<pixel_msgs::msg::PixelCoordinates>
        ("pixel_topic1", 10, std::bind(&CalcGPSNode::pixelCallback, this, 
        std::placeholders::_1));
        
        drone2_subscriber = this->create_subscription<pixel_msgs::msg::PixelCoordinates>
        ("pixel_topic2", 10, std::bind(&CalcGPSNode::pixelCallback, this, 
        std::placeholders::_1));
        
        drone3_subscriber = this->create_subscription<pixel_msgs::msg::PixelCoordinates>
        ("pixel_topic3", 10, std::bind(&CalcGPSNode::pixelCallback, this, 
        std::placeholders::_1));

        publisher_ = this->create_publisher<geometry_msgs::msg::Point>
        ("pixel_topic", 10);

        // timer_ =  this->create_wall_timer(std::chrono::milliseconds(500), 
        // std::bind(&CalcGPSNode::timer_callback), this);
    };

void CalcGPSNode::pixelCallback(const pixel_msgs::msg::PixelCoordinates::SharedPtr YOLOmsg){
        conf = YOLOmsg->confidence;

        pixel_u = YOLOmsg->u;
        pixel_v = YOLOmsg->v;
        for
        pixel_vec << pixel_u, pixel_v, 1;

        geometry_msgs::msg::Point GPSmsg;
        
        GPSmsg.x = placeholder_1;
        GPSmsg.y = placeholder_2;
        GPSmsg.z = placeholder_3;

        publisher_->publish(GPSmsg);
    }

void CalcGPSNode::projectionFormula(
    const Eigen::Vector4d &pixel_vec, 
    const Eigen::Matrix4d &transformation_mat)
    {
        // x = K^-1 * x'
        proj_vec = cam_mat.inverse() * rot_mat.inverse() * pixel_vec;
        proj_uvec = proj_vec/proj_vec.norm();   
    }

void CalcGPSNode::MVMP_triangulation(){
    Eigen::Matrix3d A_sum = Eigen::Matrix3d::Zero();
    Eigen::Vector3d b_sum = Eigen::Vector3d::Zero();
    
    for(int i = 0; i < .size(); i ++)
    {
        Eigen::Vector3d cur_b = b_vec_[i];
        Eigen::RowVector3d v_t = cur_b.transpose();

      //  std::cout << cur_b << std::endl;

        Eigen::Matrix3d A = Eigen::Matrix3d::Identity() - cur_b * v_t;
      //  std::cout << A << std::endl;

        A_sum += A;
        b_sum += (A * cams_[i].t_inv());

    }

    res = A_sum.jacobiSvd(Eigen::ComputeFullU | Eigen::ComputeFullV).solve(b_sum);

    
}

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
    




#include <rclcpp/rclcpp.hpp>
#include "pixel_msgs/msg/pixel_coordinates.hpp"
#include "geometry_msgs/msg/point.hpp"
#include <px4_msgs/msg/vehicle_odometry.hpp>
// #include "sensor_msgs/msg/camera_info.hpp"
// #include <sensor_msgs/msg/nav_sat_fix.hpp>
#include <px4_msgs/msg/vehicle_global_position.hpp>
// #include <Eigen/Cholesky>
// #include <Eigen/Eigenvalues>
#include <Eigen/De>
#include <cmath>
#include <vector>
#include <chrono>

class CalcGPSNode : public rclcpp::Node
{   
public:
    // constructor
    CalcGPSNode();

private:
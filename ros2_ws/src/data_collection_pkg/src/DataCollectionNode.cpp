#include <rclcpp/rclcpp.hpp>
#include "pixel_msgs/msg/pixel_coordinates.hpp"
#include "geometry_msgs/msg/point.hpp"
#include <px4_msgs/msg/vehicle_odometry.hpp>

#include <Eigen/Dense>

#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <limits>
#include <string>

class DataCollectionNode : public rclcpp::Node
{
public:
  DataCollectionNode();
  ~DataCollectionNode() override;

private:
  void triangulationCallback(const geometry_msgs::msg::Point::SharedPtr point_msg);
  void pixelCallback1(const pixel_msgs::msg::PixelCoordinates::SharedPtr msg);
  void pixelCallback2(const pixel_msgs::msg::PixelCoordinates::SharedPtr msg);
  void pixelCallback3(const pixel_msgs::msg::PixelCoordinates::SharedPtr msg);
  void odomCallback1(const px4_msgs::msg::VehicleOdometry::SharedPtr msg);
  void odomCallback2(const px4_msgs::msg::VehicleOdometry::SharedPtr msg);
  void odomCallback3(const px4_msgs::msg::VehicleOdometry::SharedPtr msg);
  void csvLogging();

  // Subscribers
  rclcpp::Subscription<pixel_msgs::msg::PixelCoordinates>::SharedPtr drone1_pix_subs_;
  rclcpp::Subscription<pixel_msgs::msg::PixelCoordinates>::SharedPtr drone2_pix_subs_;
  rclcpp::Subscription<pixel_msgs::msg::PixelCoordinates>::SharedPtr drone3_pix_subs_;
  rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr target_sub_;
  rclcpp::Subscription<px4_msgs::msg::VehicleOdometry>::SharedPtr drone1_odom_sub_;
  rclcpp::Subscription<px4_msgs::msg::VehicleOdometry>::SharedPtr drone2_odom_sub_;
  rclcpp::Subscription<px4_msgs::msg::VehicleOdometry>::SharedPtr drone3_odom_sub_;

  // Detection / target state
  static constexpr float kConfThreshold = 0.5f;
  bool pixel1_detected_{false};
  bool pixel2_detected_{false};
  bool pixel3_detected_{false};
  Eigen::Vector3d estimated_target_{Eigen::Vector3d::Zero()};
  bool has_target_update_{false};
  rclcpp::Time last_target_update_;
  const rclcpp::Duration target_stale_timeout_{std::chrono::seconds(2)};

  // Odom sync
  bool odom1_received_{false};
  bool odom2_received_{false};
  bool odom3_received_{false};
  double x1_{0.0}, y1_{0.0}, z1_{0.0};
  double x2_{0.0}, y2_{0.0}, z2_{0.0};
  double x3_{0.0}, y3_{0.0}, z3_{0.0};

  // Offsets (if required by your local frame setup)
  Eigen::Vector3d origin_drone1_{Eigen::Vector3d::Zero()};
  Eigen::Vector3d origin_drone2_{Eigen::Vector3d::Zero()};
  Eigen::Vector3d origin_drone3_{Eigen::Vector3d::Zero()};

  // CSV / mission metadata
  std::ofstream csv_file_;
  rclcpp::Time start_time_;
  std::string act_target_location_;
};

DataCollectionNode::DataCollectionNode()
: Node("data_collection_node")
{
  // User-configurable input (launch file / CLI):
  // ros2 run ... --ros-args -p act_target_location:="lat,lon,alt or any label"
  this->declare_parameter<std::string>("act_target_location", "");
  act_target_location_ = this->get_parameter("act_target_location").as_string();

  drone1_pix_subs_ = this->create_subscription<pixel_msgs::msg::PixelCoordinates>(
    "/pixel_topic1", 10,
    std::bind(&DataCollectionNode::pixelCallback1, this, std::placeholders::_1));
  drone2_pix_subs_ = this->create_subscription<pixel_msgs::msg::PixelCoordinates>(
    "/pixel_topic2", 10,
    std::bind(&DataCollectionNode::pixelCallback2, this, std::placeholders::_1));
  drone3_pix_subs_ = this->create_subscription<pixel_msgs::msg::PixelCoordinates>(
    "/pixel_topic3", 10,
    std::bind(&DataCollectionNode::pixelCallback3, this, std::placeholders::_1));

  auto target_qos = rclcpp::QoS(rclcpp::KeepLast(10)).best_effort().durability_volatile();
  target_sub_ = this->create_subscription<geometry_msgs::msg::Point>(
    "/point_location", target_qos,
    std::bind(&DataCollectionNode::triangulationCallback, this, std::placeholders::_1));

  auto odom_qos = rclcpp::QoS(rclcpp::KeepLast(10)).best_effort().transient_local();
  drone1_odom_sub_ = this->create_subscription<px4_msgs::msg::VehicleOdometry>(
    "/px4_1/fmu/out/vehicle_odometry", odom_qos,
    std::bind(&DataCollectionNode::odomCallback1, this, std::placeholders::_1));
  drone2_odom_sub_ = this->create_subscription<px4_msgs::msg::VehicleOdometry>(
    "/px4_2/fmu/out/vehicle_odometry", odom_qos,
    std::bind(&DataCollectionNode::odomCallback2, this, std::placeholders::_1));
  drone3_odom_sub_ = this->create_subscription<px4_msgs::msg::VehicleOdometry>(
    "/px4_3/fmu/out/vehicle_odometry", odom_qos,
    std::bind(&DataCollectionNode::odomCallback3, this, std::placeholders::_1));

  start_time_ = this->now();
  csv_file_.open("triangulation_data.csv", std::ios::out | std::ios::trunc);
  if (!csv_file_.is_open()) {
    RCLCPP_ERROR(this->get_logger(), "Failed to open triangulation_data.csv for writing.");
    return;
  }

  csv_file_ << "mission_time_s,act_target_location,estimated_target_x,estimated_target_y,estimated_target_z,"
            << "detected_all_3,x1,x2,x3,y1,y2,y3,z1,z2,z3\n";
  csv_file_ << std::fixed << std::setprecision(6);

  RCLCPP_INFO(this->get_logger(), "Writing data to triangulation_data.csv");
  RCLCPP_INFO(this->get_logger(), "act_target_location input: '%s'", act_target_location_.c_str());
}

DataCollectionNode::~DataCollectionNode()
{
  if (csv_file_.is_open()) {
    csv_file_.close();
  }
}

void DataCollectionNode::triangulationCallback(const geometry_msgs::msg::Point::SharedPtr point_msg)
{
  estimated_target_ << point_msg->x, point_msg->y, point_msg->z;
  has_target_update_ = true;
  last_target_update_ = this->now();
}

void DataCollectionNode::pixelCallback1(const pixel_msgs::msg::PixelCoordinates::SharedPtr msg)
{
  pixel1_detected_ = (msg->confidence > kConfThreshold);
}

void DataCollectionNode::pixelCallback2(const pixel_msgs::msg::PixelCoordinates::SharedPtr msg)
{
  pixel2_detected_ = (msg->confidence > kConfThreshold);
}

void DataCollectionNode::pixelCallback3(const pixel_msgs::msg::PixelCoordinates::SharedPtr msg)
{
  pixel3_detected_ = (msg->confidence > kConfThreshold);
}

void DataCollectionNode::odomCallback1(const px4_msgs::msg::VehicleOdometry::SharedPtr msg)
{
  x1_ = msg->position[0];
  y1_ = msg->position[1];
  z1_ = msg->position[2];
  odom1_received_ = true;
  if (odom1_received_ && odom2_received_ && odom3_received_) {
    csvLogging();
  }
}

void DataCollectionNode::odomCallback2(const px4_msgs::msg::VehicleOdometry::SharedPtr msg)
{
  x2_ = msg->position[0];
  y2_ = msg->position[1];
  z2_ = msg->position[2];
  odom2_received_ = true;
  if (odom1_received_ && odom2_received_ && odom3_received_) {
    csvLogging();
  }
}

void DataCollectionNode::odomCallback3(const px4_msgs::msg::VehicleOdometry::SharedPtr msg)
{
  x3_ = msg->position[0];
  y3_ = msg->position[1];
  z3_ = msg->position[2];
  odom3_received_ = true;
  if (odom1_received_ && odom2_received_ && odom3_received_) {
    csvLogging();
  }
}

void DataCollectionNode::csvLogging()
{
  if (!csv_file_.is_open()) {
    RCLCPP_ERROR(this->get_logger(), "Unable to write to CSV file.");
    return;
  }

  const bool detected_all_3 = pixel1_detected_ && pixel2_detected_ && pixel3_detected_;
  const bool target_fresh = has_target_update_ &&
    ((this->now() - last_target_update_) <= target_stale_timeout_);
  const bool can_use_estimated_target = detected_all_3 && target_fresh;

  const double mission_time_s = (this->now() - start_time_).seconds();
  const double nan = std::numeric_limits<double>::quiet_NaN();
  const Eigen::Vector3d target_to_log = can_use_estimated_target ? estimated_target_ : Eigen::Vector3d(nan, nan, nan);

  csv_file_ << mission_time_s << ","
            << act_target_location_ << ","
            << target_to_log.x() << "," << target_to_log.y() << "," << target_to_log.z() << ","
            << (detected_all_3 ? 1 : 0) << ","
            << (x1_ + origin_drone1_(0)) << "," << (x2_ + origin_drone2_(0)) << "," << (x3_ + origin_drone3_(0)) << ","
            << (y1_ + origin_drone1_(1)) << "," << (y2_ + origin_drone2_(1)) << "," << (y3_ + origin_drone3_(1)) << ","
            << (z1_ + origin_drone1_(2)) << "," << (z2_ + origin_drone2_(2)) << "," << (z3_ + origin_drone3_(2))
            << "\n";

  odom1_received_ = false;
  odom2_received_ = false;
  odom3_received_ = false;
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<DataCollectionNode>());
  rclcpp::shutdown();
  return 0;
}

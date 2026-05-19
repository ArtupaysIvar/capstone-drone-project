/*
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.hpp>
#include <opencv2/opencv.hpp>

class gst_node : public rclcpp::Node
{
public:
  gst_node() : Node("udp_cam_publisher")
  {
    publisher_ = image_transport::create_publisher(this, "camera/image_raw");
    

    std::string pipeline =
    "udpsrc port=5000 caps=\"application/x-rtp,encoding-name=H264,payload=96\" ! "
    "rtph264depay ! "
    "h264parse ! "
    "avdec_h264 ! "
    "videoconvert ! "
    "video/x-raw,format=BGR ! "
    "appsink drop=1 sync=false max-buffers=3";

    cap_.open(pipeline, cv::CAP_GSTREAMER);

    if (!cap_.isOpened()) {
      RCLCPP_ERROR(this->get_logger(), "Failed to open GStreamer pipeline!");
      return;
    }

    timer_ = this->create_wall_timer(
      std::chrono::milliseconds(33),
      std::bind(&gst_node::timer_callback, this));
      
  }

private:
  void timer_callback()
  {
  
    cv::Mat frame;

    if (cap_.read(frame)) {
      
      // define header
      std_msgs::msg::Header header;
      header.stamp = this->get_clock()->now();
      header.frame_id = "camera_frame";

      sensor_msgs::msg::Image::SharedPtr msg = cv_bridge::CvImage(header, "bgr8", frame).toImageMsg();
      // auto msg = cv_bridge::CvImage(header, "bgr8", frame).toImageMsg();

      publisher_.publish(*msg);
    }
  }

  image_transport::Publisher publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  cv::VideoCapture cap_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<gst_node>());
  rclcpp::shutdown();
  return 0;
}
*/

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.hpp>
#include <opencv2/opencv.hpp>

class gst_node : public rclcpp::Node
{
public:
  gst_node() : Node("udp_cam_publisher"), recording_(false)
  {
    publisher_ = image_transport::create_publisher(this, "camera/image_raw");

    std::string pipeline =
      "udpsrc port=5000 caps=\"application/x-rtp,encoding-name=H264,payload=96\" ! "
      "rtph264depay ! "
      "h264parse ! "
      "avdec_h264 ! "
      "videoconvert ! "
      "video/x-raw,format=BGR ! "
      "appsink sync=false max-buffers=10 drop=false";  // more buffers, no drop

    cap_.open(pipeline, cv::CAP_GSTREAMER);

    if (!cap_.isOpened()) {
      RCLCPP_ERROR(this->get_logger(), "Failed to open GStreamer pipeline!");
      return;
    }

    // get actual frame size
    frame_width_  = (int)cap_.get(cv::CAP_PROP_FRAME_WIDTH);
    frame_height_ = (int)cap_.get(cv::CAP_PROP_FRAME_HEIGHT);
    RCLCPP_INFO(this->get_logger(), "Stream opened: %dx%d", frame_width_, frame_height_);

    // start recording immediately — change to false if you want manual start
    start_recording("/home/ubuntu/Videos/recording.avi");

    // use thread instead of timer to avoid frame timing issues
    capture_thread_ = std::thread(&gst_node::capture_loop, this);
  }

  ~gst_node()
  {
    running_ = false;
    if (capture_thread_.joinable())
      capture_thread_.join();
    stop_recording();
  }

  void start_recording(const std::string & path)
  {
    writer_.open(path,
      cv::VideoWriter::fourcc('H','2','6','4'),
      30.0,
      cv::Size(frame_width_, frame_height_));

    if (writer_.isOpened()) {
      recording_ = true;
      RCLCPP_INFO(this->get_logger(), "Recording to: %s", path.c_str());
    } else {
      RCLCPP_ERROR(this->get_logger(), "Failed to open video writer!");
    }
  }

  void stop_recording()
  {
    if (recording_) {
      writer_.release();
      recording_ = false;
      RCLCPP_INFO(this->get_logger(), "Recording stopped.");
    }
  }

private:
  void capture_loop()
  {
    while (running_ && rclcpp::ok()) {
      cv::Mat frame;
      if (!cap_.read(frame) || frame.empty())
        continue;

      // publish to ROS
      std_msgs::msg::Header header;
      header.stamp = this->get_clock()->now();
      header.frame_id = "camera_frame";
      auto msg = cv_bridge::CvImage(header, "bgr8", frame).toImageMsg();
      publisher_.publish(*msg);

      // write to file
      if (recording_ && writer_.isOpened())
        writer_.write(frame);
    }
  }

  image_transport::Publisher publisher_;
  cv::VideoCapture cap_;
  cv::VideoWriter writer_;
  std::thread capture_thread_;
  std::atomic<bool> running_{true};
  std::atomic<bool> recording_{false};
  int frame_width_ = 640;
  int frame_height_ = 480;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<gst_node>());
  rclcpp::shutdown();
  return 0;
}
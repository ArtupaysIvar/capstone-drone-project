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

    // GStreamer Pipeline for the Receiver
    // We receive UDP -> Depayload -> Decode -> Convert to BGR for OpenCV
    std::string pipeline =
           "udpsrc port=5000 caps=\"video/mpegts\" ! "
    "tsdemux ! "
    "h264parse ! "
    "avdec_h264 ! "
    "videoconvert ! "
    "video/x-raw,format=BGR ! "
    "appsink drop=1 sync=false max-buffers=3";

    // Open the pipeline using the GStreamer backend
    cap_.open(pipeline, cv::CAP_GSTREAMER);

    if (!cap_.isOpened()) {
      RCLCPP_ERROR(this->get_logger(), "Failed to open GStreamer pipeline!");
      return;
    }

    // Timer loop at 30 Hz
    timer_ = this->create_wall_timer(
      std::chrono::milliseconds(33),
      std::bind(&gst_node::timer_callback, this));
      
    RCLCPP_INFO(this->get_logger(), "UDP Stream Started...");
  }

private:
  void timer_callback()
  {
    cv::Mat frame;
    // Capture the next frame
    if (cap_.read(frame)) {
      // Convert OpenCV Mat to ROS Image message
      std_msgs::msg::Header header;
      header.stamp = this->get_clock()->now();
      header.frame_id = "camera_frame";

      sensor_msgs::msg::Image::SharedPtr msg = 
        cv_bridge::CvImage(header, "bgr8", frame).toImageMsg();

      // Publish
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

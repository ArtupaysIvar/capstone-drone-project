cmake_minimum_required(VERSION 3.10)
project(gst_publisher_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)
find_package(image_transport REQUIRED)

add_executable(gst_node src/gst_node.cpp)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GST REQUIRED
  gstreamer-1.0
  gstreamer-app-1.0
  gstreamer-video-1.0
)

# target_include_directories(udp_cam_node PUBLIC
#   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#   $<INSTALL_INTERFACE:include>
#   ${OpenCV_INCLUDE_DIRS}
# )

ament_target_dependencies(gst_node rclcpp sensor_msgs cv_bridge image_transport)

target_include_directories(gst_node PUBLIC
  ${OpenCV_INCLUDE_DIRS}
  ${GST_INCLUDE_DIRS}
)

target_link_libraries(gst_node
  ${OpenCV_LIBRARIES}
  ${GST_LIBRARIES}
)

install(TARGETS 
gst_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()
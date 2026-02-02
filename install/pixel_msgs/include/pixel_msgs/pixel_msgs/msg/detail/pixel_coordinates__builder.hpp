// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from pixel_msgs:msg/PixelCoordinates.idl
// generated code does not contain a copyright notice

#ifndef PIXEL_MSGS__MSG__DETAIL__PIXEL_COORDINATES__BUILDER_HPP_
#define PIXEL_MSGS__MSG__DETAIL__PIXEL_COORDINATES__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "pixel_msgs/msg/detail/pixel_coordinates__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace pixel_msgs
{

namespace msg
{

namespace builder
{

class Init_PixelCoordinates_confidence
{
public:
  explicit Init_PixelCoordinates_confidence(::pixel_msgs::msg::PixelCoordinates & msg)
  : msg_(msg)
  {}
  ::pixel_msgs::msg::PixelCoordinates confidence(::pixel_msgs::msg::PixelCoordinates::_confidence_type arg)
  {
    msg_.confidence = std::move(arg);
    return std::move(msg_);
  }

private:
  ::pixel_msgs::msg::PixelCoordinates msg_;
};

class Init_PixelCoordinates_v
{
public:
  explicit Init_PixelCoordinates_v(::pixel_msgs::msg::PixelCoordinates & msg)
  : msg_(msg)
  {}
  Init_PixelCoordinates_confidence v(::pixel_msgs::msg::PixelCoordinates::_v_type arg)
  {
    msg_.v = std::move(arg);
    return Init_PixelCoordinates_confidence(msg_);
  }

private:
  ::pixel_msgs::msg::PixelCoordinates msg_;
};

class Init_PixelCoordinates_u
{
public:
  explicit Init_PixelCoordinates_u(::pixel_msgs::msg::PixelCoordinates & msg)
  : msg_(msg)
  {}
  Init_PixelCoordinates_v u(::pixel_msgs::msg::PixelCoordinates::_u_type arg)
  {
    msg_.u = std::move(arg);
    return Init_PixelCoordinates_v(msg_);
  }

private:
  ::pixel_msgs::msg::PixelCoordinates msg_;
};

class Init_PixelCoordinates_header
{
public:
  Init_PixelCoordinates_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PixelCoordinates_u header(::pixel_msgs::msg::PixelCoordinates::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_PixelCoordinates_u(msg_);
  }

private:
  ::pixel_msgs::msg::PixelCoordinates msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::pixel_msgs::msg::PixelCoordinates>()
{
  return pixel_msgs::msg::builder::Init_PixelCoordinates_header();
}

}  // namespace pixel_msgs

#endif  // PIXEL_MSGS__MSG__DETAIL__PIXEL_COORDINATES__BUILDER_HPP_

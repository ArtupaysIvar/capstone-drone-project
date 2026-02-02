// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from pixel_msgs:msg/PixelCoordinates.idl
// generated code does not contain a copyright notice

#ifndef PIXEL_MSGS__MSG__DETAIL__PIXEL_COORDINATES__TRAITS_HPP_
#define PIXEL_MSGS__MSG__DETAIL__PIXEL_COORDINATES__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "pixel_msgs/msg/detail/pixel_coordinates__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace pixel_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const PixelCoordinates & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: u
  {
    out << "u: ";
    rosidl_generator_traits::value_to_yaml(msg.u, out);
    out << ", ";
  }

  // member: v
  {
    out << "v: ";
    rosidl_generator_traits::value_to_yaml(msg.v, out);
    out << ", ";
  }

  // member: confidence
  {
    out << "confidence: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PixelCoordinates & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: u
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "u: ";
    rosidl_generator_traits::value_to_yaml(msg.u, out);
    out << "\n";
  }

  // member: v
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "v: ";
    rosidl_generator_traits::value_to_yaml(msg.v, out);
    out << "\n";
  }

  // member: confidence
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "confidence: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PixelCoordinates & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace pixel_msgs

namespace rosidl_generator_traits
{

[[deprecated("use pixel_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const pixel_msgs::msg::PixelCoordinates & msg,
  std::ostream & out, size_t indentation = 0)
{
  pixel_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use pixel_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const pixel_msgs::msg::PixelCoordinates & msg)
{
  return pixel_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<pixel_msgs::msg::PixelCoordinates>()
{
  return "pixel_msgs::msg::PixelCoordinates";
}

template<>
inline const char * name<pixel_msgs::msg::PixelCoordinates>()
{
  return "pixel_msgs/msg/PixelCoordinates";
}

template<>
struct has_fixed_size<pixel_msgs::msg::PixelCoordinates>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<pixel_msgs::msg::PixelCoordinates>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<pixel_msgs::msg::PixelCoordinates>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // PIXEL_MSGS__MSG__DETAIL__PIXEL_COORDINATES__TRAITS_HPP_

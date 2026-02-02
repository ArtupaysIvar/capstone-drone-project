// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from pixel_msgs:msg/PixelCoordinates.idl
// generated code does not contain a copyright notice

#ifndef PIXEL_MSGS__MSG__DETAIL__PIXEL_COORDINATES__STRUCT_HPP_
#define PIXEL_MSGS__MSG__DETAIL__PIXEL_COORDINATES__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__pixel_msgs__msg__PixelCoordinates __attribute__((deprecated))
#else
# define DEPRECATED__pixel_msgs__msg__PixelCoordinates __declspec(deprecated)
#endif

namespace pixel_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct PixelCoordinates_
{
  using Type = PixelCoordinates_<ContainerAllocator>;

  explicit PixelCoordinates_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->u = 0.0;
      this->v = 0.0;
      this->confidence = 0.0f;
    }
  }

  explicit PixelCoordinates_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->u = 0.0;
      this->v = 0.0;
      this->confidence = 0.0f;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _u_type =
    double;
  _u_type u;
  using _v_type =
    double;
  _v_type v;
  using _confidence_type =
    float;
  _confidence_type confidence;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__u(
    const double & _arg)
  {
    this->u = _arg;
    return *this;
  }
  Type & set__v(
    const double & _arg)
  {
    this->v = _arg;
    return *this;
  }
  Type & set__confidence(
    const float & _arg)
  {
    this->confidence = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    pixel_msgs::msg::PixelCoordinates_<ContainerAllocator> *;
  using ConstRawPtr =
    const pixel_msgs::msg::PixelCoordinates_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<pixel_msgs::msg::PixelCoordinates_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<pixel_msgs::msg::PixelCoordinates_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      pixel_msgs::msg::PixelCoordinates_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<pixel_msgs::msg::PixelCoordinates_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      pixel_msgs::msg::PixelCoordinates_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<pixel_msgs::msg::PixelCoordinates_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<pixel_msgs::msg::PixelCoordinates_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<pixel_msgs::msg::PixelCoordinates_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__pixel_msgs__msg__PixelCoordinates
    std::shared_ptr<pixel_msgs::msg::PixelCoordinates_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__pixel_msgs__msg__PixelCoordinates
    std::shared_ptr<pixel_msgs::msg::PixelCoordinates_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PixelCoordinates_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->u != other.u) {
      return false;
    }
    if (this->v != other.v) {
      return false;
    }
    if (this->confidence != other.confidence) {
      return false;
    }
    return true;
  }
  bool operator!=(const PixelCoordinates_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PixelCoordinates_

// alias to use template instance with default allocator
using PixelCoordinates =
  pixel_msgs::msg::PixelCoordinates_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace pixel_msgs

#endif  // PIXEL_MSGS__MSG__DETAIL__PIXEL_COORDINATES__STRUCT_HPP_

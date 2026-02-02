// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from pixel_msgs:msg/PixelCoordinates.idl
// generated code does not contain a copyright notice

#ifndef PIXEL_MSGS__MSG__DETAIL__PIXEL_COORDINATES__STRUCT_H_
#define PIXEL_MSGS__MSG__DETAIL__PIXEL_COORDINATES__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"

/// Struct defined in msg/PixelCoordinates in the package pixel_msgs.
typedef struct pixel_msgs__msg__PixelCoordinates
{
  std_msgs__msg__Header header;
  double u;
  double v;
  float confidence;
} pixel_msgs__msg__PixelCoordinates;

// Struct for a sequence of pixel_msgs__msg__PixelCoordinates.
typedef struct pixel_msgs__msg__PixelCoordinates__Sequence
{
  pixel_msgs__msg__PixelCoordinates * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} pixel_msgs__msg__PixelCoordinates__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PIXEL_MSGS__MSG__DETAIL__PIXEL_COORDINATES__STRUCT_H_

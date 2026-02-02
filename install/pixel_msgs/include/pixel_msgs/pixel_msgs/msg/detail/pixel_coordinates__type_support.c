// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from pixel_msgs:msg/PixelCoordinates.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "pixel_msgs/msg/detail/pixel_coordinates__rosidl_typesupport_introspection_c.h"
#include "pixel_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "pixel_msgs/msg/detail/pixel_coordinates__functions.h"
#include "pixel_msgs/msg/detail/pixel_coordinates__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void pixel_msgs__msg__PixelCoordinates__rosidl_typesupport_introspection_c__PixelCoordinates_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  pixel_msgs__msg__PixelCoordinates__init(message_memory);
}

void pixel_msgs__msg__PixelCoordinates__rosidl_typesupport_introspection_c__PixelCoordinates_fini_function(void * message_memory)
{
  pixel_msgs__msg__PixelCoordinates__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember pixel_msgs__msg__PixelCoordinates__rosidl_typesupport_introspection_c__PixelCoordinates_message_member_array[4] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(pixel_msgs__msg__PixelCoordinates, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "u",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(pixel_msgs__msg__PixelCoordinates, u),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "v",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(pixel_msgs__msg__PixelCoordinates, v),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "confidence",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(pixel_msgs__msg__PixelCoordinates, confidence),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers pixel_msgs__msg__PixelCoordinates__rosidl_typesupport_introspection_c__PixelCoordinates_message_members = {
  "pixel_msgs__msg",  // message namespace
  "PixelCoordinates",  // message name
  4,  // number of fields
  sizeof(pixel_msgs__msg__PixelCoordinates),
  pixel_msgs__msg__PixelCoordinates__rosidl_typesupport_introspection_c__PixelCoordinates_message_member_array,  // message members
  pixel_msgs__msg__PixelCoordinates__rosidl_typesupport_introspection_c__PixelCoordinates_init_function,  // function to initialize message memory (memory has to be allocated)
  pixel_msgs__msg__PixelCoordinates__rosidl_typesupport_introspection_c__PixelCoordinates_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t pixel_msgs__msg__PixelCoordinates__rosidl_typesupport_introspection_c__PixelCoordinates_message_type_support_handle = {
  0,
  &pixel_msgs__msg__PixelCoordinates__rosidl_typesupport_introspection_c__PixelCoordinates_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_pixel_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, pixel_msgs, msg, PixelCoordinates)() {
  pixel_msgs__msg__PixelCoordinates__rosidl_typesupport_introspection_c__PixelCoordinates_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!pixel_msgs__msg__PixelCoordinates__rosidl_typesupport_introspection_c__PixelCoordinates_message_type_support_handle.typesupport_identifier) {
    pixel_msgs__msg__PixelCoordinates__rosidl_typesupport_introspection_c__PixelCoordinates_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &pixel_msgs__msg__PixelCoordinates__rosidl_typesupport_introspection_c__PixelCoordinates_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

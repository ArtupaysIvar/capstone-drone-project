// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from pixel_msgs:msg/PixelCoordinates.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "pixel_msgs/msg/detail/pixel_coordinates__struct.h"
#include "pixel_msgs/msg/detail/pixel_coordinates__type_support.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace pixel_msgs
{

namespace msg
{

namespace rosidl_typesupport_c
{

typedef struct _PixelCoordinates_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _PixelCoordinates_type_support_ids_t;

static const _PixelCoordinates_type_support_ids_t _PixelCoordinates_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _PixelCoordinates_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _PixelCoordinates_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _PixelCoordinates_type_support_symbol_names_t _PixelCoordinates_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, pixel_msgs, msg, PixelCoordinates)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, pixel_msgs, msg, PixelCoordinates)),
  }
};

typedef struct _PixelCoordinates_type_support_data_t
{
  void * data[2];
} _PixelCoordinates_type_support_data_t;

static _PixelCoordinates_type_support_data_t _PixelCoordinates_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _PixelCoordinates_message_typesupport_map = {
  2,
  "pixel_msgs",
  &_PixelCoordinates_message_typesupport_ids.typesupport_identifier[0],
  &_PixelCoordinates_message_typesupport_symbol_names.symbol_name[0],
  &_PixelCoordinates_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t PixelCoordinates_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_PixelCoordinates_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace msg

}  // namespace pixel_msgs

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, pixel_msgs, msg, PixelCoordinates)() {
  return &::pixel_msgs::msg::rosidl_typesupport_c::PixelCoordinates_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

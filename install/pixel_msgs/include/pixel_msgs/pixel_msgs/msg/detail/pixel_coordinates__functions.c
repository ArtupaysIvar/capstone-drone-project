// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from pixel_msgs:msg/PixelCoordinates.idl
// generated code does not contain a copyright notice
#include "pixel_msgs/msg/detail/pixel_coordinates__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
pixel_msgs__msg__PixelCoordinates__init(pixel_msgs__msg__PixelCoordinates * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    pixel_msgs__msg__PixelCoordinates__fini(msg);
    return false;
  }
  // u
  // v
  // confidence
  return true;
}

void
pixel_msgs__msg__PixelCoordinates__fini(pixel_msgs__msg__PixelCoordinates * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // u
  // v
  // confidence
}

bool
pixel_msgs__msg__PixelCoordinates__are_equal(const pixel_msgs__msg__PixelCoordinates * lhs, const pixel_msgs__msg__PixelCoordinates * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // u
  if (lhs->u != rhs->u) {
    return false;
  }
  // v
  if (lhs->v != rhs->v) {
    return false;
  }
  // confidence
  if (lhs->confidence != rhs->confidence) {
    return false;
  }
  return true;
}

bool
pixel_msgs__msg__PixelCoordinates__copy(
  const pixel_msgs__msg__PixelCoordinates * input,
  pixel_msgs__msg__PixelCoordinates * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // u
  output->u = input->u;
  // v
  output->v = input->v;
  // confidence
  output->confidence = input->confidence;
  return true;
}

pixel_msgs__msg__PixelCoordinates *
pixel_msgs__msg__PixelCoordinates__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  pixel_msgs__msg__PixelCoordinates * msg = (pixel_msgs__msg__PixelCoordinates *)allocator.allocate(sizeof(pixel_msgs__msg__PixelCoordinates), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(pixel_msgs__msg__PixelCoordinates));
  bool success = pixel_msgs__msg__PixelCoordinates__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
pixel_msgs__msg__PixelCoordinates__destroy(pixel_msgs__msg__PixelCoordinates * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    pixel_msgs__msg__PixelCoordinates__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
pixel_msgs__msg__PixelCoordinates__Sequence__init(pixel_msgs__msg__PixelCoordinates__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  pixel_msgs__msg__PixelCoordinates * data = NULL;

  if (size) {
    data = (pixel_msgs__msg__PixelCoordinates *)allocator.zero_allocate(size, sizeof(pixel_msgs__msg__PixelCoordinates), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = pixel_msgs__msg__PixelCoordinates__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        pixel_msgs__msg__PixelCoordinates__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
pixel_msgs__msg__PixelCoordinates__Sequence__fini(pixel_msgs__msg__PixelCoordinates__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      pixel_msgs__msg__PixelCoordinates__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

pixel_msgs__msg__PixelCoordinates__Sequence *
pixel_msgs__msg__PixelCoordinates__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  pixel_msgs__msg__PixelCoordinates__Sequence * array = (pixel_msgs__msg__PixelCoordinates__Sequence *)allocator.allocate(sizeof(pixel_msgs__msg__PixelCoordinates__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = pixel_msgs__msg__PixelCoordinates__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
pixel_msgs__msg__PixelCoordinates__Sequence__destroy(pixel_msgs__msg__PixelCoordinates__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    pixel_msgs__msg__PixelCoordinates__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
pixel_msgs__msg__PixelCoordinates__Sequence__are_equal(const pixel_msgs__msg__PixelCoordinates__Sequence * lhs, const pixel_msgs__msg__PixelCoordinates__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!pixel_msgs__msg__PixelCoordinates__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
pixel_msgs__msg__PixelCoordinates__Sequence__copy(
  const pixel_msgs__msg__PixelCoordinates__Sequence * input,
  pixel_msgs__msg__PixelCoordinates__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(pixel_msgs__msg__PixelCoordinates);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    pixel_msgs__msg__PixelCoordinates * data =
      (pixel_msgs__msg__PixelCoordinates *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!pixel_msgs__msg__PixelCoordinates__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          pixel_msgs__msg__PixelCoordinates__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!pixel_msgs__msg__PixelCoordinates__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}

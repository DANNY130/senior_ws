// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from nav_2d_msgs:msg/Pose2D32.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "nav_2d_msgs/msg/pose2_d32.h"


#ifndef NAV_2D_MSGS__MSG__DETAIL__POSE2_D32__STRUCT_H_
#define NAV_2D_MSGS__MSG__DETAIL__POSE2_D32__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/Pose2D32 in the package nav_2d_msgs.
typedef struct nav_2d_msgs__msg__Pose2D32
{
  float x;
  float y;
  float theta;
} nav_2d_msgs__msg__Pose2D32;

// Struct for a sequence of nav_2d_msgs__msg__Pose2D32.
typedef struct nav_2d_msgs__msg__Pose2D32__Sequence
{
  nav_2d_msgs__msg__Pose2D32 * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} nav_2d_msgs__msg__Pose2D32__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // NAV_2D_MSGS__MSG__DETAIL__POSE2_D32__STRUCT_H_

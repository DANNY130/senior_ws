// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from nav_2d_msgs:msg/Twist2D.idl
// generated code does not contain a copyright notice
#ifndef NAV_2D_MSGS__MSG__DETAIL__TWIST2_D__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define NAV_2D_MSGS__MSG__DETAIL__TWIST2_D__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "nav_2d_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "nav_2d_msgs/msg/detail/twist2_d__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_nav_2d_msgs
bool cdr_serialize_nav_2d_msgs__msg__Twist2D(
  const nav_2d_msgs__msg__Twist2D * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_nav_2d_msgs
bool cdr_deserialize_nav_2d_msgs__msg__Twist2D(
  eprosima::fastcdr::Cdr &,
  nav_2d_msgs__msg__Twist2D * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_nav_2d_msgs
size_t get_serialized_size_nav_2d_msgs__msg__Twist2D(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_nav_2d_msgs
size_t max_serialized_size_nav_2d_msgs__msg__Twist2D(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_nav_2d_msgs
bool cdr_serialize_key_nav_2d_msgs__msg__Twist2D(
  const nav_2d_msgs__msg__Twist2D * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_nav_2d_msgs
size_t get_serialized_size_key_nav_2d_msgs__msg__Twist2D(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_nav_2d_msgs
size_t max_serialized_size_key_nav_2d_msgs__msg__Twist2D(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_nav_2d_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, nav_2d_msgs, msg, Twist2D)();

#ifdef __cplusplus
}
#endif

#endif  // NAV_2D_MSGS__MSG__DETAIL__TWIST2_D__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_

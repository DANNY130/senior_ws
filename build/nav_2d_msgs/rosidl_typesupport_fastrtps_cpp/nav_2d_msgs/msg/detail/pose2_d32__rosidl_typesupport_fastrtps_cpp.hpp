// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from nav_2d_msgs:msg/Pose2D32.idl
// generated code does not contain a copyright notice

#ifndef NAV_2D_MSGS__MSG__DETAIL__POSE2_D32__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define NAV_2D_MSGS__MSG__DETAIL__POSE2_D32__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include <cstddef>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "nav_2d_msgs/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "nav_2d_msgs/msg/detail/pose2_d32__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace nav_2d_msgs
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_nav_2d_msgs
cdr_serialize(
  const nav_2d_msgs::msg::Pose2D32 & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_nav_2d_msgs
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  nav_2d_msgs::msg::Pose2D32 & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_nav_2d_msgs
get_serialized_size(
  const nav_2d_msgs::msg::Pose2D32 & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_nav_2d_msgs
max_serialized_size_Pose2D32(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_nav_2d_msgs
cdr_serialize_key(
  const nav_2d_msgs::msg::Pose2D32 & ros_message,
  eprosima::fastcdr::Cdr &);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_nav_2d_msgs
get_serialized_size_key(
  const nav_2d_msgs::msg::Pose2D32 & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_nav_2d_msgs
max_serialized_size_key_Pose2D32(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace nav_2d_msgs

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_nav_2d_msgs
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, nav_2d_msgs, msg, Pose2D32)();

#ifdef __cplusplus
}
#endif

#endif  // NAV_2D_MSGS__MSG__DETAIL__POSE2_D32__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

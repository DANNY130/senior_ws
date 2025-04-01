// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from nav_2d_msgs:msg/Pose2D32.idl
// generated code does not contain a copyright notice

#include "nav_2d_msgs/msg/detail/pose2_d32__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_nav_2d_msgs
const rosidl_type_hash_t *
nav_2d_msgs__msg__Pose2D32__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x83, 0xe7, 0x6a, 0xdd, 0xcc, 0xcb, 0x7a, 0x3a,
      0xd7, 0x80, 0x1f, 0xe0, 0x67, 0x25, 0x2e, 0x38,
      0xa9, 0x0d, 0x54, 0xf5, 0x40, 0xad, 0x44, 0x74,
      0xa9, 0x6d, 0x5b, 0xac, 0xd5, 0x69, 0xfd, 0xf3,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char nav_2d_msgs__msg__Pose2D32__TYPE_NAME[] = "nav_2d_msgs/msg/Pose2D32";

// Define type names, field names, and default values
static char nav_2d_msgs__msg__Pose2D32__FIELD_NAME__x[] = "x";
static char nav_2d_msgs__msg__Pose2D32__FIELD_NAME__y[] = "y";
static char nav_2d_msgs__msg__Pose2D32__FIELD_NAME__theta[] = "theta";

static rosidl_runtime_c__type_description__Field nav_2d_msgs__msg__Pose2D32__FIELDS[] = {
  {
    {nav_2d_msgs__msg__Pose2D32__FIELD_NAME__x, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {nav_2d_msgs__msg__Pose2D32__FIELD_NAME__y, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {nav_2d_msgs__msg__Pose2D32__FIELD_NAME__theta, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
nav_2d_msgs__msg__Pose2D32__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {nav_2d_msgs__msg__Pose2D32__TYPE_NAME, 24, 24},
      {nav_2d_msgs__msg__Pose2D32__FIELDS, 3, 3},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "float32 x\n"
  "float32 y\n"
  "float32 theta";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
nav_2d_msgs__msg__Pose2D32__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {nav_2d_msgs__msg__Pose2D32__TYPE_NAME, 24, 24},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 34, 34},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
nav_2d_msgs__msg__Pose2D32__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *nav_2d_msgs__msg__Pose2D32__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

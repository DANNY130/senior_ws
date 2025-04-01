// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from nav_2d_msgs:msg/Twist2D.idl
// generated code does not contain a copyright notice

#include "nav_2d_msgs/msg/detail/twist2_d__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_nav_2d_msgs
const rosidl_type_hash_t *
nav_2d_msgs__msg__Twist2D__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x33, 0xa3, 0xa4, 0x7d, 0x7b, 0x3a, 0xaa, 0xd5,
      0x37, 0x6a, 0x48, 0x25, 0x05, 0x97, 0x09, 0x3f,
      0xeb, 0x4b, 0x92, 0xab, 0x87, 0x06, 0xc9, 0x6d,
      0xca, 0x69, 0xf4, 0x7d, 0x9a, 0x98, 0x07, 0xd0,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char nav_2d_msgs__msg__Twist2D__TYPE_NAME[] = "nav_2d_msgs/msg/Twist2D";

// Define type names, field names, and default values
static char nav_2d_msgs__msg__Twist2D__FIELD_NAME__x[] = "x";
static char nav_2d_msgs__msg__Twist2D__FIELD_NAME__y[] = "y";
static char nav_2d_msgs__msg__Twist2D__FIELD_NAME__theta[] = "theta";

static rosidl_runtime_c__type_description__Field nav_2d_msgs__msg__Twist2D__FIELDS[] = {
  {
    {nav_2d_msgs__msg__Twist2D__FIELD_NAME__x, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {nav_2d_msgs__msg__Twist2D__FIELD_NAME__y, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {nav_2d_msgs__msg__Twist2D__FIELD_NAME__theta, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
nav_2d_msgs__msg__Twist2D__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {nav_2d_msgs__msg__Twist2D__TYPE_NAME, 23, 23},
      {nav_2d_msgs__msg__Twist2D__FIELDS, 3, 3},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "float64 x\n"
  "float64 y\n"
  "float64 theta";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
nav_2d_msgs__msg__Twist2D__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {nav_2d_msgs__msg__Twist2D__TYPE_NAME, 23, 23},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 34, 34},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
nav_2d_msgs__msg__Twist2D__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *nav_2d_msgs__msg__Twist2D__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

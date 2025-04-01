// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from nav_2d_msgs:msg/Twist2D32.idl
// generated code does not contain a copyright notice

#include "nav_2d_msgs/msg/detail/twist2_d32__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_nav_2d_msgs
const rosidl_type_hash_t *
nav_2d_msgs__msg__Twist2D32__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x01, 0x27, 0xcc, 0xf5, 0x28, 0x93, 0xe4, 0x68,
      0xfc, 0x73, 0x54, 0x1e, 0x6e, 0xd2, 0xcc, 0x2f,
      0x9f, 0x98, 0x92, 0x0b, 0xac, 0x98, 0x8a, 0x27,
      0x35, 0xa4, 0x5b, 0x8f, 0xa7, 0x53, 0xdc, 0x64,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char nav_2d_msgs__msg__Twist2D32__TYPE_NAME[] = "nav_2d_msgs/msg/Twist2D32";

// Define type names, field names, and default values
static char nav_2d_msgs__msg__Twist2D32__FIELD_NAME__x[] = "x";
static char nav_2d_msgs__msg__Twist2D32__FIELD_NAME__y[] = "y";
static char nav_2d_msgs__msg__Twist2D32__FIELD_NAME__theta[] = "theta";

static rosidl_runtime_c__type_description__Field nav_2d_msgs__msg__Twist2D32__FIELDS[] = {
  {
    {nav_2d_msgs__msg__Twist2D32__FIELD_NAME__x, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {nav_2d_msgs__msg__Twist2D32__FIELD_NAME__y, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {nav_2d_msgs__msg__Twist2D32__FIELD_NAME__theta, 5, 5},
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
nav_2d_msgs__msg__Twist2D32__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {nav_2d_msgs__msg__Twist2D32__TYPE_NAME, 25, 25},
      {nav_2d_msgs__msg__Twist2D32__FIELDS, 3, 3},
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
nav_2d_msgs__msg__Twist2D32__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {nav_2d_msgs__msg__Twist2D32__TYPE_NAME, 25, 25},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 34, 34},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
nav_2d_msgs__msg__Twist2D32__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *nav_2d_msgs__msg__Twist2D32__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

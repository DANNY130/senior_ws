// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from serial_motor_demo_msgs:msg/MotorVels.idl
// generated code does not contain a copyright notice

#include "serial_motor_demo_msgs/msg/detail/motor_vels__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_serial_motor_demo_msgs
const rosidl_type_hash_t *
serial_motor_demo_msgs__msg__MotorVels__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xe0, 0x76, 0x38, 0x28, 0x54, 0xf7, 0xda, 0x60,
      0x6a, 0x18, 0xdd, 0x8e, 0x6c, 0x83, 0xe9, 0xc4,
      0x7b, 0xc7, 0xf0, 0x8e, 0x3b, 0xaf, 0x70, 0x31,
      0x76, 0x83, 0xec, 0x0b, 0x62, 0x22, 0xb1, 0x0d,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char serial_motor_demo_msgs__msg__MotorVels__TYPE_NAME[] = "serial_motor_demo_msgs/msg/MotorVels";

// Define type names, field names, and default values
static char serial_motor_demo_msgs__msg__MotorVels__FIELD_NAME__mot_1_rad_sec[] = "mot_1_rad_sec";
static char serial_motor_demo_msgs__msg__MotorVels__FIELD_NAME__mot_2_rad_sec[] = "mot_2_rad_sec";

static rosidl_runtime_c__type_description__Field serial_motor_demo_msgs__msg__MotorVels__FIELDS[] = {
  {
    {serial_motor_demo_msgs__msg__MotorVels__FIELD_NAME__mot_1_rad_sec, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {serial_motor_demo_msgs__msg__MotorVels__FIELD_NAME__mot_2_rad_sec, 13, 13},
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
serial_motor_demo_msgs__msg__MotorVels__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {serial_motor_demo_msgs__msg__MotorVels__TYPE_NAME, 36, 36},
      {serial_motor_demo_msgs__msg__MotorVels__FIELDS, 2, 2},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "float32 mot_1_rad_sec\n"
  "float32 mot_2_rad_sec";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
serial_motor_demo_msgs__msg__MotorVels__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {serial_motor_demo_msgs__msg__MotorVels__TYPE_NAME, 36, 36},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 43, 43},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
serial_motor_demo_msgs__msg__MotorVels__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *serial_motor_demo_msgs__msg__MotorVels__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

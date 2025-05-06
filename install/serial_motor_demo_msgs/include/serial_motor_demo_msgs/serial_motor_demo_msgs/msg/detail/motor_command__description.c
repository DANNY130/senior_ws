// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from serial_motor_demo_msgs:msg/MotorCommand.idl
// generated code does not contain a copyright notice

#include "serial_motor_demo_msgs/msg/detail/motor_command__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_serial_motor_demo_msgs
const rosidl_type_hash_t *
serial_motor_demo_msgs__msg__MotorCommand__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xd9, 0xcd, 0x64, 0xa3, 0xdc, 0xef, 0x53, 0x42,
      0x88, 0xda, 0x46, 0xcd, 0x31, 0x37, 0x69, 0xcf,
      0xf3, 0xd9, 0xb9, 0x04, 0x35, 0x47, 0x7c, 0x40,
      0xd7, 0xe7, 0xaf, 0x0a, 0xd4, 0xea, 0x24, 0xa2,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char serial_motor_demo_msgs__msg__MotorCommand__TYPE_NAME[] = "serial_motor_demo_msgs/msg/MotorCommand";

// Define type names, field names, and default values
static char serial_motor_demo_msgs__msg__MotorCommand__FIELD_NAME__is_pwm[] = "is_pwm";
static char serial_motor_demo_msgs__msg__MotorCommand__FIELD_NAME__mot_1_req_rad_sec[] = "mot_1_req_rad_sec";
static char serial_motor_demo_msgs__msg__MotorCommand__FIELD_NAME__mot_2_req_rad_sec[] = "mot_2_req_rad_sec";

static rosidl_runtime_c__type_description__Field serial_motor_demo_msgs__msg__MotorCommand__FIELDS[] = {
  {
    {serial_motor_demo_msgs__msg__MotorCommand__FIELD_NAME__is_pwm, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {serial_motor_demo_msgs__msg__MotorCommand__FIELD_NAME__mot_1_req_rad_sec, 17, 17},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {serial_motor_demo_msgs__msg__MotorCommand__FIELD_NAME__mot_2_req_rad_sec, 17, 17},
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
serial_motor_demo_msgs__msg__MotorCommand__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {serial_motor_demo_msgs__msg__MotorCommand__TYPE_NAME, 39, 39},
      {serial_motor_demo_msgs__msg__MotorCommand__FIELDS, 3, 3},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "bool is_pwm\n"
  "float32 mot_1_req_rad_sec #in pwm mode this is cast to int and is pwm value\n"
  "float32 mot_2_req_rad_sec #in pwm mode this is cast to int and is pwm value";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
serial_motor_demo_msgs__msg__MotorCommand__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {serial_motor_demo_msgs__msg__MotorCommand__TYPE_NAME, 39, 39},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 163, 163},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
serial_motor_demo_msgs__msg__MotorCommand__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *serial_motor_demo_msgs__msg__MotorCommand__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from serial_motor_demo_msgs:msg/EncoderVals.idl
// generated code does not contain a copyright notice

#include "serial_motor_demo_msgs/msg/detail/encoder_vals__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_serial_motor_demo_msgs
const rosidl_type_hash_t *
serial_motor_demo_msgs__msg__EncoderVals__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x54, 0x35, 0x36, 0xf2, 0x91, 0xd8, 0x87, 0xd7,
      0x2a, 0x22, 0x18, 0x21, 0x4f, 0x21, 0x61, 0x74,
      0x81, 0xdb, 0x8f, 0xa1, 0xbd, 0xe7, 0x9c, 0x80,
      0xd6, 0xab, 0x64, 0x11, 0x44, 0x25, 0x31, 0xf8,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char serial_motor_demo_msgs__msg__EncoderVals__TYPE_NAME[] = "serial_motor_demo_msgs/msg/EncoderVals";

// Define type names, field names, and default values
static char serial_motor_demo_msgs__msg__EncoderVals__FIELD_NAME__mot_1_enc_val[] = "mot_1_enc_val";
static char serial_motor_demo_msgs__msg__EncoderVals__FIELD_NAME__mot_2_enc_val[] = "mot_2_enc_val";

static rosidl_runtime_c__type_description__Field serial_motor_demo_msgs__msg__EncoderVals__FIELDS[] = {
  {
    {serial_motor_demo_msgs__msg__EncoderVals__FIELD_NAME__mot_1_enc_val, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {serial_motor_demo_msgs__msg__EncoderVals__FIELD_NAME__mot_2_enc_val, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
serial_motor_demo_msgs__msg__EncoderVals__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {serial_motor_demo_msgs__msg__EncoderVals__TYPE_NAME, 38, 38},
      {serial_motor_demo_msgs__msg__EncoderVals__FIELDS, 2, 2},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "int32 mot_1_enc_val\n"
  "int32 mot_2_enc_val";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
serial_motor_demo_msgs__msg__EncoderVals__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {serial_motor_demo_msgs__msg__EncoderVals__TYPE_NAME, 38, 38},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 39, 39},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
serial_motor_demo_msgs__msg__EncoderVals__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *serial_motor_demo_msgs__msg__EncoderVals__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

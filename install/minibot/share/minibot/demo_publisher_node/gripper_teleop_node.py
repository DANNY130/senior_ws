#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Joy
from std_msgs.msg import Float64MultiArray

class GripperTeleopNode(Node):
    def __init__(self):
        super().__init__('gripper_teleop_node')
        self.declare_parameter('topic', '/gripper_controller/commands')
        self.declare_parameter('axis_left', 5)
        self.declare_parameter('axis_right', 4)
        self.declare_parameter('scale', 1.57)
        self.declare_parameter('enable_button', 3)

        self.topic = self.get_parameter('topic').get_parameter_value().string_value
        self.axis_left = self.get_parameter('axis_left').get_parameter_value().integer_value
        self.axis_right = self.get_parameter('axis_right').get_parameter_value().integer_value
        self.scale = self.get_parameter('scale').get_parameter_value().double_value
        self.enable_button = self.get_parameter('enable_button').get_parameter_value().integer_value

        self.publisher_ = self.create_publisher(Float64MultiArray, self.topic, 10)
        self.subscription = self.create_subscription(Joy, 'joy', self.joy_callback, 10)

    def joy_callback(self, msg):
        if msg.buttons[self.enable_button]:
            command = Float64MultiArray()
            command.data = [
                msg.axes[self.axis_left] * self.scale,  # Command for gripper_left_joint
                (1.57 - msg.axes[self.axis_right] * self.scale)/2  # Command for gripper_right_joint, inverted
            ]
            self.publisher_.publish(command)

def main(args=None):
    rclpy.init(args=args)
    node = GripperTeleopNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
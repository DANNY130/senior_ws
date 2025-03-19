#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Joy
from std_msgs.msg import Float64MultiArray

class PlatformTeleopNode(Node):
    def __init__(self):
        super().__init__('platform_teleop_node')
        self.declare_parameter('topic', '/platform_controller/commands')
        self.declare_parameter('axis', 7)
        self.declare_parameter('scale', 5.0)
        self.declare_parameter('enable_button', 1)

        self.topic = self.get_parameter('topic').get_parameter_value().string_value
        self.axis = self.get_parameter('axis').get_parameter_value().integer_value
        self.scale = self.get_parameter('scale').get_parameter_value().double_value
        self.enable_button = self.get_parameter('enable_button').get_parameter_value().integer_value

        self.publisher_ = self.create_publisher(Float64MultiArray, self.topic, 10)
        self.subscription = self.create_subscription(Joy, 'joy', self.joy_callback, 10)

    def joy_callback(self, msg):
        if msg.buttons[self.enable_button]:
            command = Float64MultiArray()
            command.data = [msg.axes[self.axis] * self.scale]
            self.publisher_.publish(command)

def main(args=None):
    rclpy.init(args=args)
    node = PlatformTeleopNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
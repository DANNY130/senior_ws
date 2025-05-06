#!/usr/bin/env python3
import os  # Import the os module to execute system commands
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Joy

class EmergentShutdownNode(Node):
    def __init__(self):
        super().__init__('emergent_shutdown_node')
        #Declare the parameters
        self.declare_parameter('enable_button', 7)
        self.enable_button = self.get_parameter('enable_button').get_parameter_value().integer_value

        self.subscription = self.create_subscription(Joy, 'joy', self.joy_callback, 10)

    def joy_callback(self, msg):
        if msg.buttons[self.enable_button]:
            if self.enable_button == 7:  # Assuming button 7 is mapped to axis 7
                self.get_logger().info("Shutdown button pressed. Shutting down the system...")
                os.system("sudo shutdown now")  # Shutdown the system
            elif self.enable_button == 8:  # Example: Restart if button 8 is pressed
                self.get_logger().info("Restart button pressed. Restarting the system...")
                os.system("sudo reboot")

def main(args=None):
    rclpy.init(args=args)
    node = EmergentShutdownNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()


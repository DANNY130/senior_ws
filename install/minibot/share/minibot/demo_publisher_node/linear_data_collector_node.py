#!/usr/bin/env python3
# filepath: /home/olympusolutions/senior_ws/src/minibot/demo_publisher_node/linear_data_collector_node.py

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import TwistStamped
from nav_msgs.msg import Odometry
import csv
import os

class LinearDataCollectorNode(Node):
    def __init__(self):
        super().__init__('linear_data_collector_node')
        self.cmd_vel_subscription = self.create_subscription(
            TwistStamped,
            '/diff_drive_controller/cmd_vel',
            self.cmd_vel_callback,
            10)
        self.odom_subscription = self.create_subscription(
            Odometry,
            '/diff_drive_controller/odom',
            self.odom_callback,
            10)
        self.linear_data = []
        self.cmd_vel_setpoint = None

    def cmd_vel_callback(self, msg):
        self.cmd_vel_setpoint = msg.twist.linear.x
        self.get_logger().info(f'Received cmd_vel: {self.cmd_vel_setpoint}')
        self.record_data()

    def odom_callback(self, msg):
        odom_feedback = msg.twist.twist.linear.x
        self.get_logger().info(f'Received odom: {odom_feedback}')
        self.record_data(odom_feedback)

    def record_data(self, odom_feedback=None):
        if self.cmd_vel_setpoint is not None and odom_feedback is not None:
            timestamp = self.get_clock().now().to_msg()
            self.linear_data.append((timestamp.sec, timestamp.nanosec, self.cmd_vel_setpoint, odom_feedback))
            self.get_logger().info(f'Recorded data: {timestamp.sec}, {timestamp.nanosec}, {self.cmd_vel_setpoint}, {odom_feedback}')

    def save_to_file(self):
        documents_path = os.path.expanduser('~/Documents')
        file_path = os.path.join(documents_path, 'linear_data.csv')
        with open(file_path, 'w', newline='') as csvfile:
            writer = csv.writer(csvfile)
            writer.writerow(['timestamp_sec', 'timestamp_nanosec', 'cmd_vel_setpoint', 'odom_feedback'])
            writer.writerows(self.linear_data)
        self.get_logger().info(f'Data saved to {file_path}')

    def destroy_node(self):
        self.save_to_file()
        super().destroy_node()

def main(args=None):
    rclpy.init(args=args)
    node = LinearDataCollectorNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
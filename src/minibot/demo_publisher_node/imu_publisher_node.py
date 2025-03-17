#!/usr/bin/env python3
import rclpy
import serial
from rclpy.node import Node
from sensor_msgs.msg import Imu
import math

class ImuPublisher(Node):
    def __init__(self):
        super().__init__('imu_publisher')
        self.publisher_ = self.create_publisher(Imu, 'imu/data_raw', 10)
        self.serial_port = serial.Serial('/dev/ttyACM2', 115200, timeout=1)  # Change port if needed

    def read_imu_data(self):
        if self.serial_port.in_waiting > 0:
            try:
                line = self.serial_port.readline().decode('utf-8').strip()
                values = [float(x) for x in line.split(',')]

                if len(values) == 9:
                    imu_msg = Imu()
                    imu_msg.header.stamp = self.get_clock().now().to_msg()
                    imu_msg.header.frame_id = "imu_link"

                    roll, pitch, yaw = values[:3]
                    gx, gy, gz = values[3:6]
                    ax, ay, az = values[6:9]

                    # Convert roll, pitch, yaw to quaternion
                    cy, sy = math.cos(yaw * 0.5), math.sin(yaw * 0.5)
                    cp, sp = math.cos(pitch * 0.5), math.sin(pitch * 0.5)
                    cr, sr = math.cos(roll * 0.5), math.sin(roll * 0.5)

                    imu_msg.orientation.w = cr * cp * cy + sr * sp * sy
                    imu_msg.orientation.x = sr * cp * cy - cr * sp * sy
                    imu_msg.orientation.y = cr * sp * cy + sr * cp * sy
                    imu_msg.orientation.z = cr * cp * sy - sr * sp * cy

                    imu_msg.angular_velocity.x = gx
                    imu_msg.angular_velocity.y = gy
                    imu_msg.angular_velocity.z = gz

                    imu_msg.linear_acceleration.x = ax
                    imu_msg.linear_acceleration.y = ay
                    imu_msg.linear_acceleration.z = az

                    self.publisher_.publish(imu_msg)
            except Exception as e:
                self.get_logger().error(f"Error parsing IMU data: {str(e)}")

def main(args=None):
    rclpy.init(args=args)
    imu_publisher = ImuPublisher()

    try:
        while rclpy.ok():
            imu_publisher.read_imu_data()
    except KeyboardInterrupt:
        pass
    finally:
        imu_publisher.serial_port.close()
        imu_publisher.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()

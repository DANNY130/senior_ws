# filepath: /home/olympusolutions/senior_ws/src/imu_publisher/imu_publisher/imu_publisher.py
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Imu
import serial

class ImuPublisher(Node):
    def __init__(self):
        super().__init__('imu_publisher')
        self.publisher_ = self.create_publisher(Imu, 'imu/data', 10)
        self.serial_port = serial.Serial('/dev/ttyUSB0', 115200)
        self.timer = self.create_timer(0.1, self.timer_callback)

    def timer_callback(self):
        line = self.serial_port.readline().decode('utf-8').strip()
        imu_msg = Imu()
        imu_msg.header.stamp = self.get_clock().now().to_msg()
        imu_msg.header.frame_id = 'imu_link'

        if line.startswith("A:"):
            parts = line[2:].split(',')
            if len(parts) == 3:
                imu_msg.linear_acceleration.x = float(parts[0])
                imu_msg.linear_acceleration.y = float(parts[1])
                imu_msg.linear_acceleration.z = float(parts[2])

        if line.startswith("G:"):
            parts = line[2:].split(',')
            if len(parts) == 3:
                imu_msg.angular_velocity.x = float(parts[0])
                imu_msg.angular_velocity.y = float(parts[1])
                imu_msg.angular_velocity.z = float(parts[2])

        self.publisher_.publish(imu_msg)

def main(args=None):
    rclpy.init(args=args)
    node = ImuPublisher()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
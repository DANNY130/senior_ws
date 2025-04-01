#!/usr/bin/env python3
# Import necessary libraries and modules
import rclpy  # ROS 2 Python client library
import serial  # For serial communication with IMU
from rclpy.node import Node  # Base class for ROS 2 nodes
from sensor_msgs.msg import Imu  # Message type for IMU data
import math  # For mathematical operations (e.g., trigonometry)

# IMU Publisher Node class
# This node reads IMU data from a serial port and publishes it to the 'imu/data_raw' topic
class ImuPublisher(Node):
    # Initialize the node and set up the publisher
    # The publisher sends IMU data messages to the specified topic
    def __init__(self):
        super().__init__('imu_publisher')
        self.publisher_ = self.create_publisher(Imu, 'imu/data_raw', 10)
        self.serial_port = serial.Serial('/dev/ttyACM2', 115200, timeout=1)  # Change port if needed
    # Set the serial port to read data from the IMU
    # The baud rate is set to 115200, and a timeout of 1 second is specified for reading data

    def read_imu_data(self): # Read data from the IMU
        # Read a line from the serial port and decode it
        if self.serial_port.in_waiting > 0:
            try:
                line = self.serial_port.readline().decode('utf-8').strip() # Decode the line read from the serial port because it is in bytes. Decode it to utf-8 and remove any trailing whitespace characters.
                values = [float(x) for x in line.split(',')] # Split the line by commas and convert each value to a float
                # Check if the number of values is correct (9 values for IMU data)

                if len(values) == 9:
                    imu_msg = Imu() # Create an instance of the Imu message type
                    # Set the header information for the IMU message
                    imu_msg.header.stamp = self.get_clock().now().to_msg()
                    imu_msg.header.frame_id = "imu_link" # Set the frame ID for the IMU data
                    # Set the orientation, angular velocity, and linear acceleration data

                    roll, pitch, yaw = values[:3] 
                    gx, gy, gz = values[3:6] # Gyroscope data
                    # Get the gyroscope data (angular velocity)
                    ax, ay, az = values[6:9] # Accelerometer data
                    # Get the accelerometer data (linear acceleration)

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

                    self.publisher_.publish(imu_msg) # Publish the IMU message to the topic
            except Exception as e: # Handle any exceptions that occur during data reading or parsing
                # Log the error message
                self.get_logger().error(f"Error parsing IMU data: {str(e)}")

# The main function initializes the ROS 2 node and starts the IMU publisher
# It creates an instance of the ImuPublisher class and enters a loop to read and publish IMU data
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

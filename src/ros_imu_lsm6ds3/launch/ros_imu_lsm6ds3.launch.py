from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='ros_imu_lsm6ds3',
            executable='ros_imu_lsm6ds3',
            name='ros_imu_lsm6ds3',
            output='screen'),
    ])
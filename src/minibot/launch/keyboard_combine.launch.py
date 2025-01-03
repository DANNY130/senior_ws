import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource

def generate_launch_description():
    # Get the paths to both launch files
    joystick_teleop_launch = os.path.join(
        get_package_share_directory('minibot'),  # Replace 'minibot' with the correct package name
        'launch',
        'joystick_teleop.launch.py'
    )
    keyboard_launch = os.path.join(
        get_package_share_directory('minibot'),  # Replace 'minibot' with the correct package name
        'launch',
        'keyboard.launch.py'
    )

    # Include both launch files
    joystick_teleop = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(joystick_teleop_launch)
    )
    keyboard_teleop = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(keyboard_launch)
    )

    # Create the launch description and populate
    ld = LaunchDescription()

    # Add both launch files to the launch description
    ld.add_action(joystick_teleop)
    ld.add_action(keyboard_teleop)

    return ld

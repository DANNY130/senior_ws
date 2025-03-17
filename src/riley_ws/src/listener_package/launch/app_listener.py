import os
from launch import LaunchDescription
from launch_ros.actions import Node

# laucn file for the tcp listener node

def generate_launch_description():

    # define the TCP listener Node
    # have a created package that has a hardcoded IP address and port number (can later chhange instead of hardcoding)

    node_tcp_listener = Node(
        package='listener_package',
        executable='phone_listener',
        name='phone_listener',
        output='screen',
        # might need remappings such as /joy_vel. Ask danny?
    )

    ld = LaunchDescription()
    ld.add_action(node_tcp_listener)

    return LaunchDescription([node_tcp_listener])
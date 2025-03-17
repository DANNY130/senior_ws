import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():

    package_name = 'minibot'

    # Declare the path to files
    joy_params_file = os.path.join(
        get_package_share_directory(package_name), 
        'config', 
        'joystick_params.yaml' 
    )

    # joy node
    joy_node = Node(
        package='joy',
        executable='joy_node',
        parameters=[joy_params_file]
    )    

    # teleop node
    teleop_node = Node(
        package='teleop_twist_joy',
        executable='teleop_node',
        name='teleop_node',
        parameters=[joy_params_file],
        remappings=[('/cmd_vel', 'joy_vel')]
    )

    # imu_filter_madgwick node
    imu_filter_node = Node(
        package='imu_filter_madgwick',
        executable='imu_filter_madgwick_node',
        name='imu_filter_madgwick_node',
        parameters=[{'use_mag': False}],
        remappings=[
            ('/imu/data_raw', '/imu/data_raw'),
            ('/imu/data', '/imu/data')
        ]
    )

    # extender teleop node
    extender_teleop_node = Node(
        package='minibot',
        executable='extender_teleop_node.py',
        name='extender_teleop_node',
        parameters=[joy_params_file],
        output='screen'
    )

    # gripper teleop node
    gripper_teleop_node = Node(
        package='minibot',
        executable='gripper_teleop_node.py',
        name='gripper_teleop_node',
        parameters=[joy_params_file],
        output='screen'
    )

    # platform teleop node
    platform_teleop_node = Node(
        package='minibot',
        executable='platform_teleop_node.py',
        name='platform_teleop_node',
        parameters=[joy_params_file],
        output='screen'
    )

    # imu publisher node
    imu_publisher_node = Node(
        package='minibot',
        executable='imu_publisher_node.py',
        name='imu_publisher_node',
        parameters=[joy_params_file],
        output='screen'
    )

    # Create the launch description and populate
    ld = LaunchDescription()

    # Add the nodes to the launch description
    ld.add_action(joy_node)
    ld.add_action(teleop_node)
    ld.add_action(extender_teleop_node)
    ld.add_action(gripper_teleop_node)
    ld.add_action(platform_teleop_node)
    ld.add_action(imu_publisher_node)
    ld.add_action(imu_filter_node)
   
    # Generate the launch description and 
    return ld
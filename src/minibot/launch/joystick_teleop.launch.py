import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():

    package_name= 'minibot'

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
        name= 'teleop_node',
        parameters=[joy_params_file],
        remappings=[('/cmd_vel','joy_vel')]
    )
        
    # Create the launch description and populate
    ld = LaunchDescription()

    # Add the nodes to the launch description
    ld.add_action(joy_node)
    ld.add_action(teleop_node)
   
    # Generate the launch description and 
    return ld

    
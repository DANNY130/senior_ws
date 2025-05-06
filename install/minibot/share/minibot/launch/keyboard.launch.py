from launch import LaunchDescription
from launch.actions import ExecuteProcess
from launch_ros.actions import Node

def generate_launch_description():
    # teleop_twist_keyboard node
    teleop_twist_keyboard = ExecuteProcess(
        cmd=['gnome-terminal', '--', 'ros2', 'run', 'teleop_twist_keyboard', 'teleop_twist_keyboard'],
        output='screen'
    )

    # twist_stamper node
    twist_stamper_node = Node(
        package='twist_stamper',
        executable='twist_stamper',
        name='twist_stamper',
        output='screen',
        remappings=[
            ('cmd_vel_in', 'cmd_vel'),
            ('cmd_vel_out', '/joy_vel')
        ]
    )

    # Create the launch description
    ld = LaunchDescription()

    # Add the nodes to the launch description
    ld.add_action(teleop_twist_keyboard)
    ld.add_action(twist_stamper_node)

    return ld

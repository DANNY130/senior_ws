import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import RegisterEventHandler, DeclareLaunchArgument, IncludeLaunchDescription
from launch.event_handlers import OnProcessStart
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue
from launch.substitutions import LaunchConfiguration, Command


# Image Transport Republishers
# terminal command example: ros2 run image_transport republish raw compressed --ros-args -r in:=/camera/image_raw -r out/compressed:=/camera/image_raw/compressed
def image_transport_republisher(transport, camera_topics):
    base_topic = camera_topics.split('/')[-1]
    
    return Node(
        package='image_transport',
        executable='republish',
        name=f'image_transport_republish_{transport}_{base_topic}',
        arguments=['raw', transport],
        remappings=[
            ('in', f'/camera/{camera_topics}'),
            (f'out/{transport}', f'/camera/{camera_topics}/{transport}'),
        ],
    )

def generate_launch_description():

    package_name= 'minibot'
    package_dir= get_package_share_directory(package_name) 

    use_sim_time = LaunchConfiguration('use_sim_time')
    use_ros2_control = LaunchConfiguration('use_ros2_control')
    lidar_serial_port = LaunchConfiguration('lidar_serial_port')

    declare_use_sim_time= DeclareLaunchArgument(
        'use_sim_time',
        default_value='false',
        description='If true, use simulated clock'
    )
    
    declare_use_ros2_control = DeclareLaunchArgument(
        'use_ros2_control',
        default_value='true',
        description='If true, use ros2_control'
    )

    declare_lidar_serial_port = DeclareLaunchArgument(
        'lidar_serial_port',
        default_value='/dev/ttyUSB0',
        description='Specifying usb port to connected lidar'
    )

    # Declare the path to files
    robot_description_xacro_file = os.path.join(
        package_dir,
        'description',
        'robot.urdf.xacro'
    )

    rviz_config_file_dir = os.path.join(
        package_dir, 
        'config', 
        'sim_config.rviz'
    )

    robot_controllers_file_dir = os.path.join(
        package_dir, 
        'config', 
        'controller.yaml'
    )

    ekf_params_file = os.path.join(
        package_dir,
        'config',
        'controller.yaml'
    )
    
    twist_mux_params_file = os.path.join(
        package_dir, 
        'config', 
        'twist_mux.yaml'
    )

    # robot_state_publisher setup    
    robot_description_config = Command ([
        'xacro ', 
        robot_description_xacro_file, 
        ' use_ros2_control:=', 
        use_ros2_control
        ])
    
    params = {
        'robot_description': ParameterValue(robot_description_config, value_type=str), 
        'use_sim_time': use_sim_time,
        'use_ros2_control': use_ros2_control
    }

    # robot_state_publisher node
    node_robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='screen',
        parameters=[params]
        
    )
 
    # Image Transport Republishers Node
    camera = 'image_raw'
    depth_camera = 'depth/image_raw'
    image_transports = ['compressed','compressedDepth', 'theora', 'zstd' ]  
    node_image_republishers = [image_transport_republisher(transport, camera) 
                          for transport in image_transports]
 
    # controller spawn
    node_ros2_control = Node(
        package="controller_manager",
        executable="ros2_control_node",
        parameters=[params, 
                    robot_controllers_file_dir
                    ],
    )

    joint_state_broadcaster_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["joint_state_broadcaster"],
    )
    
    diff_drive_controller_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["diff_drive_controller", 
                   "--param-file", 
                   robot_controllers_file_dir
        ],
    )

    extender_controller_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["extender_controller", 
                   "--param-file", 
                   robot_controllers_file_dir
        ],
    )

    gripper_controller_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["gripper_controller", 
                   "--param-file", 
                   robot_controllers_file_dir
        ],
    )

    platform_controller_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["platform_controller",
                   "--param-file",
                   robot_controllers_file_dir
        ],
    )

    ekf_filter_node_spawner = Node(
        package='robot_localization',
        executable='ekf_node',
        name='ekf_filter_node',
        output='screen',
        parameters=[ekf_params_file],
    )

    node_twist_mux = Node(
        package="twist_mux",
        executable="twist_mux",
        name='twist_mux',
        output='screen',
        parameters=[
            twist_mux_params_file,
            {'use_stamped': True},
        ],
        remappings=[
            ('cmd_vel_out', 
             'diff_drive_controller/cmd_vel'),
        ],
    )

    node_twist_stamper = Node(
        package="twist_stamper",
        executable="twist_stamper",
        name='twist_stamper',
        output='screen',
        remappings=[
            ('cmd_vel_in', 'cmd_vel_smoothed'),
            ('cmd_vel_out', 'nav_vel'),
        ],
    )

    node_rviz2 = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        arguments=['-d', rviz_config_file_dir],
        parameters=[{'use_sim_time': False}],
        output='both'
    )

    register_node_ros2_control = RegisterEventHandler(
        event_handler=OnProcessStart(
            target_action= node_robot_state_publisher,
            on_start= [node_ros2_control],
        )
    )

    register_joint_state_broadcaster_spawner = RegisterEventHandler(
        event_handler=OnProcessStart(
            target_action= node_ros2_control,
            on_start=[joint_state_broadcaster_spawner],
        )
    )

    register_diff_drive_controller_spawner = RegisterEventHandler(
        event_handler=OnProcessStart(
            target_action= joint_state_broadcaster_spawner,
            on_start=[diff_drive_controller_spawner],
        )
    )

    register_extender_controller_spawner = RegisterEventHandler(
        event_handler=OnProcessStart(
            target_action= joint_state_broadcaster_spawner,
            on_start=[extender_controller_spawner],
        )
    )

    register_gripper_controller_spawner = RegisterEventHandler(
        event_handler=OnProcessStart(
            target_action= joint_state_broadcaster_spawner,
            on_start=[gripper_controller_spawner],
        )
    )

    register_platform_controller_spawner = RegisterEventHandler(
        event_handler=OnProcessStart(
            target_action= joint_state_broadcaster_spawner,
            on_start=[platform_controller_spawner],
        )
    )

    register_ekf_filter_node_spawner = RegisterEventHandler(
        event_handler=OnProcessStart(
            target_action= joint_state_broadcaster_spawner,
            on_start=[ekf_filter_node_spawner],
        )
    )

    

    node_rplidar_drive = IncludeLaunchDescription(
                PythonLaunchDescriptionSource([os.path.join(
                    get_package_share_directory('sllidar_ros2'),
                    'launch',
                    'sllidar_a1_launch.py'
                )]), 
                launch_arguments={
                    'serial_port': lidar_serial_port, 
                    'frame_id': 'lidar_frame'
                    }.items()
    )

    # node_rplidar_start = Node(
    #     package='rplidar_ros',
    #     executable='rplidar_composition',
    #     output='screen',
    #     parameters=[
    #         {'serial_port': '/dev/ttyUSB1', 
    #          'frame_id': 'lidar_frame',
    #          'angle_compensate': True,
    #          'scan_mode': 'Standard'}
    #     ]
    # )

    # Create the launch description and populate
    ld = LaunchDescription()

    # Add the nodes to the launch description
    ld.add_action(declare_use_sim_time)
    ld.add_action(declare_use_ros2_control)
    ld.add_action(declare_lidar_serial_port)

    ld.add_action(register_node_ros2_control)
    ld.add_action(register_joint_state_broadcaster_spawner)
    ld.add_action(register_diff_drive_controller_spawner)
    ld.add_action(register_extender_controller_spawner)
    ld.add_action(register_gripper_controller_spawner)
    ld.add_action(register_platform_controller_spawner)
    ld.add_action(register_ekf_filter_node_spawner)

    ld.add_action(node_robot_state_publisher)
    ld.add_action(node_twist_mux)
    ld.add_action(node_twist_stamper)
    for node_republisher in node_image_republishers:
        ld.add_action(node_republisher)
    # ld.add_action(node_rplidar_start)
    ld.add_action(node_rplidar_drive)
    ld.add_action(node_rviz2)

    # Generate the launch description  
    return ld

    
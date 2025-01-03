import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, GroupAction, RegisterEventHandler, DeclareLaunchArgument
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

    # Add launch configurations
    use_sim_time = LaunchConfiguration('use_sim_time')
    use_ros2_control = LaunchConfiguration('use_ros2_control')
    use_ros2_control_gz_sim = LaunchConfiguration('use_ros2_control_gz_sim')

    # Declare launch arguments
    declare_use_sim_time= DeclareLaunchArgument(
        'use_sim_time',
        default_value='true',
        description='If true, use simulated clock'
    )
    
    declare_use_ros2_control = DeclareLaunchArgument(
        'use_ros2_control',
        default_value='true',
        description='If true, use ros2_control'
    )

    declare_use_ros2_control_gz_sim = DeclareLaunchArgument(
        'use_ros2_control_gz_sim',
        default_value='true',
        description='If true, use ros2_control in gz_sim'
    )

    # Declare the path to files
    robot_description_xacro_file = os.path.join(
        package_dir,
        'description',
        'robot.urdf.xacro'
    )

    world_file_path = os.path.join(
        package_dir, 
        'worlds', 
        'playground.sdf'
    )

    rviz_config_file = os.path.join(
        package_dir, 
        'config', 
        'sim_config.rviz'
    )

    robot_controllers_file = os.path.join(
        package_dir, 
        'config', 
        'controller_gz_sim.yaml'
    )

    gazebo_params_file = os.path.join(
        package_dir, 
        'config', 
        'gz_params.yaml'
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
        use_ros2_control,
        ' use_ros2_control_gz_sim:=',
        use_ros2_control_gz_sim,        
        ])
    
    params = {
        'robot_description': ParameterValue(robot_description_config, value_type=str), 
        'use_sim_time': use_sim_time,        
    }

    # robot_state_publisher node
    node_robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='screen',
        parameters=[params]
    )
    
    # gz_bridge node
    # format: '<topic_name>@/[/]<ros2_topic_type_name>@/[/]<gazebo_topic_type_name>',
    # ros2 topic type <topic_name> to check topi type_name in ros2
    # gz topic -t <topic_name> -i to check topic type_name in gazebo
    node_gz_bridge = Node(
        package='ros_gz_bridge',
        executable='parameter_bridge',
        arguments=[
            
            # General
            '/clock@rosgraph_msgs/msg/Clock[gz.msgs.Clock',

            # Gazebo_Control
            '/cmd_vel@geometry_msgs/msg/Twist]gz.msgs.Twist',
            '/odom@nav_msgs/msg/Odometry[gz.msgs.Odometry',
            '/joint_states@sensor_msgs/msg/JointState[gz.msgs.Model',
            '/tf@tf2_msgs/msg/TFMessage[gz.msgs.Pose_V', 

            # Lidar 
            '/scan@sensor_msgs/msg/LaserScan[gz.msgs.LaserScan',
            '/scan/points@sensor_msgs/msg/PointCloud2[gz.msgs.PointCloudPacked',

            # Camera
            # '/camera/image_raw@sensor_msgs/msg/Image[gz.msgs.Image',
            # '/camera/camera_info@sensor_msgs/msg/CameraInfo[gz.msgs.CameraInfo',

            # RGBD Camera
            '/camera/depth/image_raw/camera_info@sensor_msgs/msg/CameraInfo[gz.msgs.CameraInfo',
            '/camera/depth/image_raw/depth_image@sensor_msgs/msg/Image[gz.msgs.Image',
            '/camera/depth/image_raw/image@sensor_msgs/msg/Image[gz.msgs.Image',
            '/camera/depth/image_raw/points@sensor_msgs/msg/PointCloud2[gz.msgs.PointCloudPacked',
        ],
        output='screen'
    )

    # Image Transport Republishers Node
    camera = 'image_raw'
    depth_camera = 'depth/image_raw'
    image_transports = ['compressed','compressedDepth', 'theora', 'zstd' ]  
    node_image_republishers = [image_transport_republisher(transport, depth_camera) 
                          for transport in image_transports]

    # gz launch world
    gazebo = IncludeLaunchDescription(
                PythonLaunchDescriptionSource([os.path.join(
                    get_package_share_directory('ros_gz_sim'),
                    'launch',
                    'gz_sim.launch.py'
                )]), 
                launch_arguments=
                {'gz_args': f'-r -v 4 {world_file_path}',
                 'extra_gazebo_args': '--ros-args --params-file' + gazebo_params_file}.items()
    )

    # gz spawn robot entity 
    node_gz_spawn_entity = Node(
        package='ros_gz_sim',
        executable='create',
        output='screen',
        arguments=['-topic', 'robot_description', 
                '-name', 'minibot',
                '-allow_renaming', 'true',
                '-z', '0.1'],
    )

    # rviz2 node
    node_rviz2 = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        arguments=['-d', rviz_config_file],
        parameters=[{'use_sim_time': True}],
        output='both'
    )

    # controller spawn 
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
                   robot_controllers_file
        ],
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

    register_joint_state_broadcaster_spawner = RegisterEventHandler(
        event_handler=OnProcessStart(
            target_action= node_gz_spawn_entity,
            on_start= [joint_state_broadcaster_spawner],
        )
    )

    register_diff_drive_controller_spawner = RegisterEventHandler(
        event_handler=OnProcessStart(
            target_action= joint_state_broadcaster_spawner,
            on_start= [diff_drive_controller_spawner],
        )
    )

    group_spawn_gz= GroupAction(
        [gazebo, 
         node_gz_spawn_entity,
        ]
    )


    # Create the launch description and populate
    ld = LaunchDescription()

    # Add the nodes to the launch description
    ld.add_action(declare_use_sim_time)
    ld.add_action(declare_use_ros2_control)
    ld.add_action(declare_use_ros2_control_gz_sim)

    ld.add_action(register_joint_state_broadcaster_spawner)
    ld.add_action(register_diff_drive_controller_spawner)

    ld.add_action(node_robot_state_publisher)
    ld.add_action(node_twist_mux)
    ld.add_action(node_twist_stamper)
    ld.add_action(node_gz_bridge)
    for node_republisher in node_image_republishers:
        ld.add_action(node_republisher)
    ld.add_action(group_spawn_gz)
    ld.add_action(node_rviz2)

    # Generate the launch description  
    return ld

    
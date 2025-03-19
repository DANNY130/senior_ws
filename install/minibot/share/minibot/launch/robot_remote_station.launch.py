import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, DeclareLaunchArgument
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration, PythonExpression
from launch.conditions import IfCondition

def generate_launch_description():

    package_name= 'minibot'
    package_dir= get_package_share_directory(package_name) 

    use_sim_time = LaunchConfiguration('use_sim_time')
    map = LaunchConfiguration('map')
    use_slam_option = LaunchConfiguration('use_slam_option')
    
    declare_use_sim_time= DeclareLaunchArgument(
        'use_sim_time',
        default_value='false',
        description='If true, use simulated clock'
    )  

    declare_map= DeclareLaunchArgument(
        'map',
        default_value='./src/minibot/maps/map_01.yaml',
        description='If true, use simulated clock'
    )

    declare_use_slam_option = DeclareLaunchArgument(
        'use_slam_option',
        default_value='mapper_params_localization',
        description='Choose SLAM option: amcl, mapper_params_localization, or online_async_slam'
    )  

    # Declare the path to files
    joy_params_file = os.path.join(
        get_package_share_directory(package_name), 
        'config', 
        'joystick_params.yaml' 
    )

    rviz_config_file = os.path.join(
        get_package_share_directory(package_name), 
        'config', 
        'minibot_config.rviz' 
    )

    mapper_params_online_async_file = os.path.join(
        package_dir, 
        'config', 
        'mapper_params_online_async.yaml'
    )

    mapper_params_localization_file = os.path.join(
        package_dir, 
        'config', 
        'mapper_params_localization.yaml'
    )

    nav2_params_file = os.path.join(
        package_dir, 
        'config', 
        'nav2_params.yaml'
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
    
    # rviz2 node
    node_rviz2 = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        arguments=['-d', rviz_config_file],
        parameters=[{'use_sim_time': False}],
        output='both'
    )
    
    # online_async_slam launch 
    online_async_slam = IncludeLaunchDescription(
                PythonLaunchDescriptionSource([os.path.join(
                    get_package_share_directory('slam_toolbox'),
                    'launch',
                    'online_async_launch.py'
                )]), 
                launch_arguments={
                    'slam_params_file': mapper_params_online_async_file,
                    'use_sim_time': use_sim_time
                }.items(),
                condition=IfCondition(PythonExpression(["'", use_slam_option, "' == 'online_async_slam'"]))         
    )

    # nav2_nmapper_params_localization launch 
    mapper_params_localization = IncludeLaunchDescription(
                PythonLaunchDescriptionSource([os.path.join(
                    get_package_share_directory('slam_toolbox'),
                    'launch',
                    'localization_launch.py'
                )]), 
                launch_arguments={
                    'slam_params_file': mapper_params_localization_file,
                    'use_sim_time': use_sim_time
                }.items(),
                condition=IfCondition(PythonExpression(["'", use_slam_option, "' == 'mapper_params_localization'"]))         
    )

    # amcl launch 
    amcl = IncludeLaunchDescription(
                PythonLaunchDescriptionSource([os.path.join(
                    get_package_share_directory('nav2_bringup'),
                    'launch',
                    'localization_launch.py'
                )]), 
                launch_arguments={
                    'map': map,
                    'use_sim_time': use_sim_time
                }.items(),
                condition=IfCondition(PythonExpression(["'", use_slam_option, "' == 'amcl'"]))           
    )

    # nav2_navigation launch 
    navigation = IncludeLaunchDescription(
                PythonLaunchDescriptionSource([os.path.join(
                    get_package_share_directory('nav2_bringup'),
                    'launch',
                    'navigation_launch.py'
                )]), 
                launch_arguments={
                    'params_file': nav2_params_file,
                    'use_sim_time': use_sim_time
                }.items()            
    )

    

     # Create the launch description and populate
    ld = LaunchDescription()
    
    # Add the launch arguments
    ld.add_action(declare_use_sim_time)
    ld.add_action(declare_map)
    ld.add_action(declare_use_slam_option)

    # Add the nodes to the launch description
    ld.add_action(joy_node)
    ld.add_action(teleop_node)
    ld.add_action(node_rviz2)

    # Add SLAM options
    ld.add_action(online_async_slam)
    ld.add_action(mapper_params_localization)
    ld.add_action(amcl)

    # # Add navigation
    ld.add_action(navigation)

    # Generate the launch description and 
    return ld

    
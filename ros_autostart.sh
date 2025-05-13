# Go to my workspace
cd /home/olympusolutions/senior_ws

# Source ROS and my workspace
source /opt/ros/jazzy/setup.bash
source install/setup.bash

# Launch both programs in background
ros2 launch minibot robot.launch.py &
sleep 5 # give it some time to start
ros2 launch minibot joystick_teleop.launch.py &
sleep 5
ros2 launch minibot sim_control_station.launch.py use_slam_option:=online_async_slam &
sleep 5
ros2 run listener_package phone_listener &
sleep 5
ros2 run listener_package map_publisher

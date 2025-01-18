# diffdrive_arduino

This node is designed to provide a ros2_control hardware interface for an Arduino running firmware from `ros_arduino_bridge`.
It is designed to be used with a `diff_drive_controller` from `ros2_control`.
It is expected to communicate via serial and to have two motors, each with velocity control and position/velocity feedback.




It is based on the diffbot example from [ros2_control demos](https://github.com/ros-controls/ros2_control_demos/tree/master/example_2).

For a tutorial on how to develop a hardware interface like this, check out the video below:

https://youtu.be/J02jEKawE5U

# RVIZ2 Visualization for IMU

RViz Configuration
In RViz, add the following displays to visualize the robot's position and orientation in 3D:

TF: To visualize the transforms.
RobotModel: To visualize the robot model.
Odometry: To visualize the odometry data.
IMU: To visualize the IMU data.

 - robot_localization is a package in ROS (Robot Operating System) that provides state estimation through sensor fusion. It uses an Extended Kalman Filter (EKF) or Unscented Kalman Filter (UKF) to fuse data from various sensors (e.g., IMU, odometry, GPS) to provide a more accurate estimate of the robot's state (position, orientation, velocity).

Purpose of robot_localization
Sensor Fusion: Combines data from multiple sensors to improve the accuracy of state estimation.
State Estimation: Provides estimates of the robot's position, orientation, and velocity.
Transform Publishing: Publishes transforms between different coordinate frames (e.g., odom, base_link).
Implementing robot_localization in Your Configuration
To implement robot_localization in your configuration, you need to:

Install the robot_localization package.
Configure the EKF node to fuse data from your sensors.
Launch the EKF node with the appropriate parameters.
Step-by-Step Implementation
Install robot_localization Package: Ensure you have the robot_localization package installed in your ROS 2 workspace.

Configure the EKF Node: You have already added the EKF configuration in your YAML file. Ensure it is correctly set up to fuse IMU and odometry data.

Launch the EKF Node: Create a launch file to start the EKF node with the specified parameters.

## To Do

- [ ] Document changes from earlier versions
- [ ] Document usage and parameters
- [ ] Clean up remaining connections to original demo code
- [ ] Add license etc (in the meantime, do whatever you want with it)
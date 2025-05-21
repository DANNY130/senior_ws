import socket
import threading
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import TwistStamped
from nav_msgs.msg import OccupancyGrid
import json
from rclpy.qos import QoSProfile, DurabilityPolicy

# purpose of this script is to listen for a TCP connection and translate the commands into Twist messages
 
# Define command bindings in a dictionary (messages being sent by the app buttons)


command_bindings = {
    'forward': (1, 0, 0, 0),
    'backward': (-1, 0, 0, 0),
    'left': (0, 0, 0, 1),
    'right': (0, 0, 0, -1),
    'stop': (0, 0, 0, 0)
}
 
class TCPListenerNode(Node):

    def __init__(self):

        self.excepting_commands = False
    
        super().__init__('tcp_listener')
        self.publisher_ = self.create_publisher(TwistStamped, '/joy_vel', 10)
 
        # Socket setup
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.bind(('', 65432))
        self.server_socket.listen(5)
 
        self.speed = 0.5
        self.turn = 1.0

        self.latest_map = None

        self.subscription = self.create_subscription(
            OccupancyGrid,
            '/map',
            self.map_callback,
            QoSProfile(
                depth=10,
                durability=DurabilityPolicy.TRANSIENT_LOCAL
            )
        )
        self.get_logger().info("Subscription to /map created")

    def map_callback(self, msg):
        self.get_logger().info("Map received")
        self.latest_map = msg
 
    def start(self):

        """Start listening for TCP connections."""

        threading.Thread(target=rclpy.spin, args = (self,), daemon=True).start()
        self.get_logger().info("Started ROS spin in background")
        
        while True: # while package running
            self.client_socket, address = self.server_socket.accept()
            self.get_logger().info(f"Connection from {address}")
            threading.Thread(target=self.handle_client, args=(self.client_socket,)).start()
 
    def handle_client(self, client_socket):

        """Handle incoming messages from a client."""
        try:
            data = client_socket.recv(1024).decode('utf-8').strip().lower()
            if not data:
                client_socket.close()
                return
            
            self.get_logger().info(f"Received command: {data}")

            self.process_command(data)

            while True:
                data = client_socket.recv(1024).decode('utf-8').strip().lower()
                if not data:
                    break
                self.get_logger().info(f"Received command: {data}")
                #sent to function to process the command and translate it to a Twist message
                self.process_command(data)
        except Exception as e:
            self.get_logger().error(f"Error handling client: {e}")
        finally:
            client_socket.close()
 

    # function to process the command
    # if the command is in the command_bindings dictionary, 
    # then the command is translated into a Twist message (ros2 teleop_twist_keyboard for reference)


    def process_command(self, command):


        self.get_logger().info(f"Processing earlier command: {command}")

        

        if command == 'get_map':
            self.get_logger().info("\033[0;32mSending map data...")
            self.send_map()
            
            return

        if command == 'first message!':
            self.excepting_commands = True
            return
        
        command_data = json.loads(command)
        self.get_logger().info(f"Processing command: {command_data}")
        if 'speed' in command_data and 'angle' in command_data:

            #access speed and angular in the json
            speed = command_data['speed']
            angle = command_data['angle']

            # Log the received values
            self.get_logger().info(f"Received movement command: speed={speed}, angular={angle}")

 
            twist_stamped = TwistStamped()

            twist_stamped.header.stamp = self.get_clock().now().to_msg()  # current timestamp helps create priority
            
            twist_stamped.twist.linear.x = speed
            twist_stamped.twist.angular.z = angle
            
            # old code
            # twist_stamped.twist.linear.x = x * self.speed
            # twist_stamped.twist.linear.y = y * self.speed
            # twist_stamped.twist.linear.z = z * self.speed
            # twist_stamped.twist.angular.z = th * self.turn
 
            self.publisher_.publish(twist_stamped)
        
        # Handle grabber commands
        elif 'heightincrement' in command_data:
            # Extract value instruction
            value = command_data['heightIncrement']

            # Log the received values
            self.get_logger().info(f"Received grabber command: value={value}")

            # Call to whatever function (to be implemented)
            #self.send_lifting(value)

        elif 'grabstatus' in command_data:

            grabber = command_data['grabStatus']

            self.get_logger().info(f"Received grabber command: rabber={grabber}")

            #grabbing to be implemented
            #self.send_grabbing(grabber)

        elif command == 'first message!':
            self.get_logger().info("\033[0;32mConnection established!")

        # also another "command", more of a message/disconnect, will check for the disconnect message and log it and shutdown the robot
        elif command == 'disconnect' and self.excepting_commands:
            self.excepting_commands = False 
            self.get_logger().info("\033[0;32mConnection terminated!")
            # rclpy.shutdown()

        else:
            self.get_logger().error(f"\033[0;33m Invalid command received: {command}")
 
    def send_map(self):
        if self.latest_map is None:
            self.get_logger().warn("No map data yet")
            return

        msg = self.latest_map
        width = msg.info.width
        height = msg.info.height
        resolution = msg.info.resolution
        data = list(msg.data)

        map_json = {
            "width": width,
            "height": height,
            "resolution": resolution,
            "data": data
        }

        try:
            self.client_socket.sendall((json.dumps(map_json) + "\n").encode('utf-8'))
            self.get_logger().info(f"Sent map of size {width}x{height}")
        except Exception as e:
            self.get_logger().error(f"Failed to send map: {e}")

def main(args=None):
    rclpy.init(args=args)
    node = TCPListenerNode()
    try:
        node.start()
    except KeyboardInterrupt:
        pass
    finally:
        node.server_socket.close()
        rclpy.shutdown()
 
if __name__ == '__main__':
    main()
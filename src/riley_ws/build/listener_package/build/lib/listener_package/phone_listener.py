import socket
import threading
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import TwistStamped

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
        self.server_socket.bind(('', ''))
        self.server_socket.listen(5)
 
        self.speed = 0.5
        self.turn = 1.0
 
    def start(self):

        """Start listening for TCP connections."""
        while True: # while package running
            client_socket, address = self.server_socket.accept()
            self.get_logger().info(f"Connection from {address}")
            threading.Thread(target=self.handle_client, args=(client_socket,)).start()
 
    def handle_client(self, client_socket):

        """Handle incoming messages from a client."""
        try:
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

        if command == 'first message!':
            self.excepting_commands = True
        
        """Translate the received command into a Twist message."""
        if command in command_bindings and self.excepting_commands:
            x, y, z, th = command_bindings[command]
 
            twist_stamped = TwistStamped()

            twist_stamped.header.stamp = self.get_clock().now().to_msg()  # current timestamp helps create priority
            twist_stamped.twist.linear.x = x * self.speed
            twist_stamped.twist.linear.y = y * self.speed
            twist_stamped.twist.linear.z = z * self.speed
            twist_stamped.twist.angular.z = th * self.turn
 
            self.publisher_.publish(twist_stamped)

        elif command == 'first message!':
            self.get_logger().info("\033[0;32mConnection established!")

        # also another "command", more of a message/disconnect, will check for the disconnect message and log it and shutdown the robot
        elif command == 'disconnect' and self.excepting_commands:
            self.excepting_commands = False 
            self.get_logger().info("\033[0;32mConnection terminated!")
            # rclpy.shutdown()

        else:
            self.get_logger().error(f"\033[0;33m Invalid command received: {command}")
 


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
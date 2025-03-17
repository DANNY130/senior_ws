# Copyright 2016 Open Source Robotics Foundation, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Working with this script requires opening a port through the ubuntu firewall
# use sudo ufw allow 65432/tcp to open it up
# use sudo ufw delete allow 65432/tcp to close after you're done.

# this script was initial package to learn how to subscribe to a TCP connection

import socket
import rclpy
from rclpy.node import Node

class TCPSubscriber(Node):
    def __init__(self):
        super().__init__('tcp_subscriber')
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.bind(('127.0.0.1', 65432))  # Listen on this IP and port
        self.server_socket.listen(1)  # Allow one connection/queue at a time
        self.get_logger().info('TCP Subscriber listening on port 65432')

        self.client_socket, self.client_address = self.server_socket.accept()
        self.get_logger().info(f'Connection from {self.client_address}')
        self.receive_data()

    def receive_data(self):
        while rclpy.ok():
            data = self.client_socket.recv(1024)  # Receive up to 1024 bytes
            if not data:
                break
            self.get_logger().info(f'heard: "{data.decode()}"')
        self.client_socket.close()
        self.server_socket.close()

def main(args=None):
    rclpy.init(args=args)

    tcp_subscriber = TCPSubscriber()

    rclpy.spin(tcp_subscriber)

    tcp_subscriber.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()

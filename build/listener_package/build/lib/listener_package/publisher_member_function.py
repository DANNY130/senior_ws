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

import socket
import time
import rclpy
from rclpy.node import Node

class TCPPublisher(Node):
    def __init__(self, host, port):
        super().__init__('tcp_publisher')
        self.host = host
        self.port = port
        self.i = 0
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((self.host, self.port))
        self.timer_period = 5  # seconds

    def timer_callback(self):
        msg = 'forward' if self.i % 2 == 0 else 'backward'
        self.sock.sendall(msg.encode())  # Send data over TCP
        self.get_logger().info('Publishing: "%s"' % msg)
        self.i += 1

    def start(self):
        try:
            while rclpy.ok():
                self.timer_callback()
                time.sleep(self.timer_period)  # Delay between message sends
        except KeyboardInterrupt:
            self.get_logger().info("Publisher stopped.")
        finally:
            self.sock.close()  # Clean up the socket

def main(args=None):
    rclpy.init(args=args)

    host = '127.0.0.1'  # Target host
    port = 65432  # Target port

    tcp_publisher = TCPPublisher(host, port)
    tcp_publisher.start()

    rclpy.shutdown()

if __name__ == '__main__':
    main()

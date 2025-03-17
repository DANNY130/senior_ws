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


class MinimalPublisher(Node):

class MinimalPublisher:

    def __init__(self, host, port): # made changes here because we are working with sending messages over a topic
        self.host = host # need network
        self.port = port # need port
        self.i = 0
        # self.af_inet is the to reach the ip address ipv4
        # socket.socket_dgram specifies the socket type. used for user datagram protocol
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.timer_period = 0.5  # seconds

    def timer_callback(self):
        msg = 'Hello World: %d' % self.i
        self.sock.sendto(msg.encode(), (self.host, self.port))
        print('Publishing: "%s"' % msg)
        self.i += 1

    def start(self):
        try:
def main():
    host = '127.0.0.1'  # Replace with the target host
    port = 12345  # Replace with the target port

    minimal_publisher = MinimalPublisher(host, port)
    minimal_publisher.start()
    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    minimal_publisher.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()

# import socket
# import threading
# import json
# import numpy as np
# import rclpy
# from rclpy.node import Node
# from nav_msgs.msg import OccupancyGrid

# class MapServer(Node):
#     def __init__(self, client_socket):
#         super().__init__('map_server')
#         self.client_socket = client_socket
#         self.latest_map = None

#         self.subscription = self.create_subscription(
#             OccupancyGrid,
#             '/map',
#             self.map_callback,
#             10
#         )

#     def map_callback(self, msg):
#         self.get_logger().info("Map received")
#         self.latest_map = msg

#     def listen_for_requests(self):
#         try:
#             while True:
#                 data = self.client_socket.recv(1024).decode('utf-8').strip()
#                 if data == 'GET_MAP':
#                     self.send_map()
#                 elif data == 'disconnect':
#                     self.get_logger().info("Client disconnected")
#                     break
#                 else:
#                     self.get_logger().warn(f"Unknown command: {data}")
#         except Exception as e:
#             self.get_logger().error(f"Error: {e}")
#         finally:
#             self.client_socket.close()

#     def send_map(self):
#         if self.latest_map is None:
#             self.get_logger().warn("No map data yet")
#             return

#         msg = self.latest_map
#         width = msg.info.width
#         height = msg.info.height
#         resolution = msg.info.resolution
#         data = list(msg.data)

#         map_json = {
#             "width": width,
#             "height": height,
#             "resolution": resolution,
#             "data": data
#         }if data == 'get_map':
#                 self.get_log

#         try:
#             self.client_socket.sendall((json.dumps(map_json) + "\n").encode('utf-8'))
#             self.get_logger().info(f"Sent map of size {width}x{height}")
#         except Exception as e:
#             self.get_logger().error(f"Failed to send map: {e}")

# def start_map_server_with_socket(client_socket):
#     rclpy.init()
#     node = MapServer(client_socket)

#     thread = threading.Thread(target=node.listen_for_requests)
#     thread.start()import socket
# import threading
# import json
# import numpy as np
# import rclpy
# from rclpy.node import Node
# from nav_msgs.msg import OccupancyGrid

# class MapServer(Node):
#     def __init__(self, client_socket):
#         super().__init__('map_server')
#         self.client_socket = client_socket
#         self.latest_map = None

#         self.subscription = self.create_subscription(
#             OccupancyGrid,
#             '/map',
#             self.map_callback,
#             10
#         )

#     def map_callback(self, msg):
#         self.get_logger().info("Map received")
#         self.latest_map = msg

#     def listen_for_requests(self):
#         try:
#             while True:
#                 data = self.client_socket.recv(1024).decode('utf-8').strip()
#                 if data == 'GET_MAP':
#                     self.send_map()
#                 elif data == 'disconnect':
#                     self.get_logger().info("Client disconnected")
#                     break
#                 else:
#                     self.get_logger().warn(f"Unknown command: {data}")
#         except Exception as e:
#             self.get_logger().error(f"Error: {e}")
#         finally:
#             self.client_socket.close()

#     def send_map(self):
#         if self.latest_map is None:
#             self.get_logger().warn("No map data yet")
#             return

#         msg = self.latest_map
#         width = msg.info.width
#         height = msg.info.height
#         resolution = msg.info.resolution
#         data = list(msg.data)

#         map_json = {
#             "width": width,
#             "height": height,
#             "resolution": resolution,
#             "data": data
#         }if data == 'get_map':
#                 self.get_log

#         try:
#             self.client_socket.sendall((json.dumps(map_json) + "\n").encode('utf-8'))
#             self.get_logger().info(f"Sent map of size {width}x{height}")
#         except Exception as e:
#             self.get_logger().error(f"Failed to send map: {e}")

# def start_map_server_with_socket(client_socket):
#     rclpy.init()
#     node = MapServer(client_socket)

#     thread = threading.Thread(target=node.listen_for_requests)
#     thread.start()

#     try:
#         rclpy.spin(node)
#     except KeyboardInterrupt:
#         pass
#     finally:
#         node.destroy_node()
#         rclpy.shutdown()

# def main():
#     server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#     server_socket.bind(('localhost', 66789))
#     server_socket.listen(1)

#     print("Waiting for a connection...")
#     client_socket, addr = server_socket.accept()
#     print(f"Connection from {addr}")



#     #start_map_server_with_socket(client_socket)

# if __name__ == '__main__':
#     main()

#     try:
#         rclpy.spin(node)
#     except KeyboardInterrupt:
#         pass
#     finally:
#         node.destroy_node()
#         rclpy.shutdown()

# def main():
#     server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#     server_socket.bind(('localhost', 66789))
#     server_socket.listen(1)

#     print("Waiting for a connection...")
#     client_socket, addr = server_socket.accept()
#     print(f"Connection from {addr}")



#     #start_map_server_with_socket(client_socket)

# if __name__ == '__main__':
#     main()
# filepath: /home/olympusolutions/senior_ws/src/riley_ws/src/listener_package/listener_package/map_publisher.py
import rclpy
from rclpy.node import Node
from nav_msgs.msg import OccupancyGrid
from std_msgs.msg import Header
from geometry_msgs.msg import Pose
from rclpy.qos import QoSProfile, DurabilityPolicy

class MapPublisher(Node):
    def __init__(self):
        super().__init__('map_publisher')
        qos_profile = QoSProfile(
            depth=10,
            durability=DurabilityPolicy.TRANSIENT_LOCAL
        )
        self.publisher_ = self.create_publisher(OccupancyGrid, '/map', qos_profile)
        self.timer = self.create_timer(1.0, self.publish_map)  # Publish every second

    def publish_map(self):
        # Create an OccupancyGrid message
        msg = OccupancyGrid()
        msg.header = Header()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.header.frame_id = "map"

        # Map metadata
        msg.info.resolution = 0.05  # 5 cm per cell
        msg.info.width = 100  # 100 cells wide
        msg.info.height = 100  # 100 cells tall
        msg.info.origin = Pose()
        msg.info.origin.position.x = 0.0
        msg.info.origin.position.y = 0.0
        msg.info.origin.position.z = 0.0
        msg.info.origin.orientation.w = 1.0

        # Map data (100x100 grid filled with zeros)
        msg.data = [0] * (msg.info.width * msg.info.height)

        self.publisher_.publish(msg)
        self.get_logger().info("Published a map")

def main(args=None):
    rclpy.init(args=args)
    node = MapPublisher()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
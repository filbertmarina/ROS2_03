import sys

from tutorial_interfaces.srv import FullNameSumService
import rclpy
from rclpy.node import Node


class MinimalClientAsync(Node):

    def __init__(self):
        super().__init__('minimal_client_async')
        self.cli = self.create_client(FullNameSumService, 'add_two_ints')
        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('service not available, waiting again...')
        self.req = FullNameSumService.Request()

    def send_request(self, a, b, c):
        self.req.a = a
        self.req.b = b
        self.req.b = c
        self.future = self.cli.call_async(self.req)
        rclpy.spin_until_future_complete(self, self.future)
        return self.future.result()


def main():
    rclpy.init()

    minimal_client = MinimalClientAsync()
    response = minimal_client.send_request(string(sys.argv[1]), string(sys.argv[2]), string(sys.argv[3]))
    minimal_client.get_logger().info(
        'Result of add_two_ints: for %d + %d = %d' %
        (string(sys.argv[1]), string(sys.argv[2]),string(sys.argv[3]), response.sum))

    minimal_client.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()

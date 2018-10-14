import rclpy
from std_msgs.msg import String


def main(args=None):
    rclpy.init(args=args)

    node = rclpy.create_node('first_pub_node')
    node2 = rclpy.create_node('first_pub_node2')
    publisher = node.create_publisher(String, 'topic')
    publisher2 = node2.create_publisher(String, 'topic2')

    msg = String()
    msg2 = String()
    i = 0
    j = 0

    def timer_callback():
        nonlocal i
        msg.data = 'Hello! ^^: %d' % i
        i += 1
        node.get_logger().info('Publishing: "%s"' % msg.data)
        publisher.publish(msg)
    def timer_callback2():
        nonlocal j
        msg2.data = 'World! ^^: %d' % j
        j += 1
        node2.get_logger().info('Publishing: "%s"' % msg2.data)
        publisher2.publish(msg2)

    timer_period = 0.5
    timer = node.create_timer(timer_period, timer_callback)
    timer2 = node2.create_timer(timer_period, timer_callback2)
    while True:
        rclpy.spin_once(node)
        rclpy.spin_once(node2)

    node.destroy_timer(timer)
    node.destroy_node()
    node2.destroy_timer(timer2)
    node2.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()

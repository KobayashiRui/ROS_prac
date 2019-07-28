#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses a fancy C++11 lambda
 * function to shorten the callback syntax, at the expense of making the
 * code somewhat more difficult to understand at first glance. */


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto pub_node = rclcpp::Node::make_shared("minimal_publisher");
  auto publisher = pub_node->create_publisher<std_msgs::msg::String>("topic",10);
  //auto message = std::make_shared<std_msgs::msg::String>();
  auto message = std_msgs::msg::String();
  message.data = "Hello, world";
  rclcpp::WallRate rate(20ms);
  
  //通信が確立するまでの何回かは送信失敗(受信されないだけ)するので注意
  //受信側が受け取らない個数はWallRateの時間設定による(早いほど多くなる)
  for(int i=0; i < 100; i++){
    rate.sleep();
    message.data ="Hello, world" + std::to_string(i);
    RCLCPP_INFO(pub_node->get_logger(),"Publishing: %s",message.data.c_str());
    rclcpp::spin_some(pub_node);
    publisher->publish(message);
  }
  rclcpp::shutdown();
  return 0;
}

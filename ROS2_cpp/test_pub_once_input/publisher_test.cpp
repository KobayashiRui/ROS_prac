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
  //rclcpp::init(argc, argv);
  int a=0;
  char** b=NULL;
  rclcpp::init(a, b);
  for(int i=0; i < 100; i++){
  auto pub_node = rclcpp::Node::make_shared("minimal_publisher");
  //std::shared_ptr<rclcpp::Node> pub_node = rclcpp::Node::make_shared("minimal_publisher");

  auto publisher = pub_node->create_publisher<std_msgs::msg::String>("topic2",10);
  //std::shared_ptr<rclcpp::Publisher<std_msgs::msg::String_<std::allocator<void> > > >publisher = pub_node->create_publisher<std_msgs::msg::String>("topic",10);
  auto message = std_msgs::msg::String();
  rclcpp::WallRate rate(200ms);
  
  //通信が確立するまでの何回かは送信失敗(受信されないだけ)するので注意
  //受信側が受け取らない個数はWallRateの時間設定による(早いほど多くなる)
    //rate.sleep();
    std::cout << "入力してください : ";
    std::cin >>  message.data;
    //message.data ="Hello, world" + std::to_string(i);
    RCLCPP_INFO(pub_node->get_logger(),"Publishing: %s",message.data.c_str());
    rclcpp::spin_some(pub_node);
    publisher->publish(message);
  }
  rclcpp::shutdown();
  return 0;
}
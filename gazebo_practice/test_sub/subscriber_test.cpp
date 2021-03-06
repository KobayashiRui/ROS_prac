#include <iostream>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("minimal_subst(criber")
  {

    auto subscription_func = 
        [this](std_msgs::msg::String::UniquePtr msg) {
            RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
        };

    subscription_ = this->create_subscription<std_msgs::msg::String>(
      "topic",
      rclcpp::QoS(rclcpp::KeepLast(1)),
      subscription_func);
  }

private:
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
 // int a =0;
 // char**b = NULL;
 // rclcpp::init(a,b);
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}

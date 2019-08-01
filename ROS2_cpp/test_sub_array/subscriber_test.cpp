#include <iostream>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("minimal_subscriber")
  {

    auto subscription_func = 
        [this](std_msgs::msg::Float32MultiArray::UniquePtr msg) {
            //RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
            std::cout << "data :";
            //std::cout << msg->data << "\n";
            std::for_each(msg->data.begin(), msg->data.end(), [&](float i){ std::cout << i << ",";});
            std::cout << "\n";
        };

    subscription_ = this->create_subscription<std_msgs::msg::Float32MultiArray>(
      "topic",
      10,
      subscription_func);
  }

private:
  rclcpp::Subscription<std_msgs::msg::Float32MultiArray>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}

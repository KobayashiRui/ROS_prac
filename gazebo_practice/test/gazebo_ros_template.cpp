#include <gazebo/physics/Model.hh>
#include "gazebo_ros_template.hpp"
#include <gazebo_ros/node.hpp>
#include <rclcpp/rclcpp.hpp>
#include "std_msgs/msg/string.hpp"

#include <memory>

namespace gazebo_plugins
{
/// Class to hold private data members (PIMPL pattern)
class GazeboRosTemplatePrivate
{
public:
  /// Connection to world update event. Callback is called while this is alive.
  gazebo::event::ConnectionPtr update_connection_;

  /// Node for ROS communication.
  gazebo_ros::Node::SharedPtr ros_node_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber;
  std_msgs::msg::String message;
  std::mutex lock_;
  void OnUpdate();
  //void OnGetsub(const std_msgs::msg::String::UniquePtr _msg);//引数には受け取るメッセージ ポインタでないとエラーがでる!
  void OnGetsub(const std_msgs::msg::String::SharedPtr _msg);//引数には受け取るメッセージ ポインタでないとエラーがでる!



};

GazeboRosTemplate::GazeboRosTemplate()
: impl_(std::make_unique<GazeboRosTemplatePrivate>())
{
}

GazeboRosTemplate::~GazeboRosTemplate()
{
}

void GazeboRosTemplate::Load(gazebo::physics::ModelPtr model, sdf::ElementPtr sdf)
{
  //impl_->ros_node_ = gazebo_ros::Node::Get(sdf);
  //ROS nodeの作成 Get(名前)でネームスペースができ, topic名が/名前/~となる
  impl_->ros_node_ = gazebo_ros::Node::Get();
  impl_->message.data = "Hello, world! ";

  //publisherの作成  
  impl_->publisher = impl_->ros_node_->create_publisher<std_msgs::msg::String>("topic",rclcpp::QoS(rclcpp::KeepLast(1)));
  //上のGetでGet("hoge")となっている場合 => /hoge/topic となる


  impl_->subscriber = impl_->ros_node_->create_subscription<std_msgs::msg::String>(
    "topic2", rclcpp::QoS(rclcpp::KeepLast(1)),
    std::bind(&GazeboRosTemplatePrivate::OnGetsub, impl_.get(), std::placeholders::_1));



  RCLCPP_INFO(impl_->ros_node_->get_logger(), model->GetName().c_str());
  //RCLCPP_INFO(impl_->ros_node_->get_logger(), impl_->publisher->get_topic_name());

  //update_connection_は最後に呼ばないとgazeboの起動が安定しない?
  impl_->update_connection_ = gazebo::event::Events::ConnectWorldUpdateBegin(
    std::bind(&GazeboRosTemplatePrivate::OnUpdate, impl_.get()));
}

//void GazeboRosTemplatePrivate::OnGetsub(const std_msgs::msg::String::UniquePtr _msg)
void GazeboRosTemplatePrivate::OnGetsub(const std_msgs::msg::String::SharedPtr _msg)
{
  std::lock_guard<std::mutex> scoped_lock(lock_);
  RCLCPP_INFO(ros_node_->get_logger(), "I heard: '%s'", _msg->data.c_str());
  message.data=_msg->data;
}

void GazeboRosTemplatePrivate::OnUpdate()
{
  //RCLCPP_INFO(ros_node_->get_logger(), "Publishing: '%s'", message.data.c_str());

  publisher->publish(message);
  // Do something every simulation iteration
}

// Register this plugin with the simulator
GZ_REGISTER_MODEL_PLUGIN(GazeboRosTemplate)
}  // namespace gazebo_plugins
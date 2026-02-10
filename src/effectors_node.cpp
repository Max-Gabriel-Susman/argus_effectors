#include <memory>
#include <rclcpp/rclcpp.hpp>
#include "std_msgs/msg/string.hpp"


class EffectorsNode : public rclcpp::Node
{
public:
  EffectorsNode()
  : Node("argus_effectors")
  {
    sub_ = create_subscription<std_msgs::msg::String>(
      "/argus/effectors/cmd",
      10,
      [this](const std_msgs::msg::String::SharedPtr msg)
      {
        RCLCPP_INFO(get_logger(), "received cmd: %s", msg->data.c_str());
      });

    RCLCPP_INFO(get_logger(), "argus_effectors online");
  }

private:
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<EffectorsNode>());
  rclcpp::shutdown();
  return 0;
}

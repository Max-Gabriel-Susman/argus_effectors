#include <rclcpp/rclcpp.hpp>

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);

  auto node = rclcpp::Node::make_shared("argus_effectors");

  RCLCPP_INFO(node->get_logger(), "argus_effectors online");

  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}

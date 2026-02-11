#include <memory>

#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"


class EffectorsNode : public rclcpp::Node
{
public:
  EffectorsNode()
  : Node("argus_effectors")
  {
    last_log_time_ = now();

    sub_ = create_subscription<geometry_msgs::msg::Twist>(
      "/cmd_vel",
      10,
      [this](const geometry_msgs::msg::Twist::SharedPtr msg)
      {
        const auto t = now();

        if ((t - last_log_time_).seconds() >= 1.0) {
          last_log_time_ = t;

          RCLCPP_INFO(
            get_logger(),
            "cmd_vel: linear.x=%.3f angular.z=%.3f",
            msg->linear.x,
            msg->angular.z);
        }
      });

    RCLCPP_INFO(get_logger(), "argus_effectors online (subscribed to /cmd_vel)");
  }

private:
  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr sub_;

  rclcpp::Time last_log_time_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);

  rclcpp::spin(std::make_shared<EffectorsNode>());

  rclcpp::shutdown();

  return 0;
}

#include "rclcpp/rclcpp.hpp"
//#include "example_interfaces/srv/add_two_ints.hpp"
#include "tutorial_interfaces/srv/FullNameSumService.hpp"
#include <memory>

void add(const std::shared_ptr<tutorial_interfaces::srv::AddTwoStr::Request> request,
          std::shared_ptr<tutorial_interfaces::srv::AddTwoStr::Response>      response)
{
  response->sum = request->a + request->b+request->c;
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\na: %ld" " b: %ld",
                request->a, request->b, request->c);
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%ld]", (long int)response->sum);
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("server_name");

  rclcpp::Service<example_interfaces::srv::AddTwoStr>::SharedPtr service =
    node->create_service<example_interfaces::srv::AddTwoStr>("SummFullName", &add);

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add three strings.");

  rclcpp::spin(node);
  rclcpp::shutdown();
}

#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "interfaces/msg/command.hpp"

using namespace std::chrono_literals;
using namespace std::placeholders;

class Publisher : public rclcpp::Node
{
	rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr sub;
	rclcpp::Publisher<interfaces::msg::Command>::SharedPtr pub;

	void fungsi_subscribe(const sensor_msgs::msg::Joy &msg)
	{
		// TODO: insert logic here

		auto cmd = interfaces::msg::Command();

		pub->publish(cmd);
	}

public:
	Publisher() : Node("node")
	{
		sub = this->create_subscription<sensor_msgs::msg::Joy>("joy", 10, std::bind(&Publisher::fungsi_subscribe, this, _1));
		pub = this->create_publisher<interfaces::msg::Command>("cmd_vel", 10);
	}
};

int main(int argc, char **argv)
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<Publisher>());
	rclcpp::shutdown();
	return 0;
}

// sauce
// http://wiki.ros.org/joy
// http://docs.ros.org/en/noetic/api/sensor_msgs/html/msg/Joy.html
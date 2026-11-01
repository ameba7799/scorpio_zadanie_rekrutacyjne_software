// You can remove or add any includes you need
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <std_msgs/msg/int8.hpp>
#include <std_msgs/msg/u_int16.hpp>

#include "Point.h"

namespace solution {

#define CHAR(a) ((a <= 127 && a >= -128) ? static_cast<char> (a) : (a > 0) ? 127 : -128) //zamiana na char

//magiczne numerki:
#define POW12 4096
#define POW11 2048

//metodą prób i błędów
#define SCALE1 2.2
#define SCALE2 3.0


class Solution final : public rclcpp::Node {
public:
  explicit Solution(const rclcpp::NodeOptions& options = rclcpp::NodeOptions())
  : rclcpp::Node("solution", options) {
    // Short example you can remove it
    const auto preempt = declare_parameter<bool>("preempt", false);
    RCLCPP_INFO(get_logger(), "%s", preempt ? "Preempt" : "Queue");

    control_motor1 = create_publisher<std_msgs::msg::Int8>("motor_1/control", rclcpp::QoS(rclcpp::KeepLast(10)).reliable().transient_local());
    control_motor2 = create_publisher<std_msgs::msg::Int8>("motor_2/control", rclcpp::QoS(rclcpp::KeepLast(10)).reliable().transient_local());

    _target = create_subscription<geometry_msgs::msg::Point>("target", rclcpp::QoS(rclcpp::KeepLast(10)).reliable().transient_local(),
      [this](const geometry_msgs::msg::Point::SharedPtr p) {
        RCLCPP_INFO(get_logger(), "Target: (%g, %g, %g)", p->x, p->y, p->z);
        point.setPoint(p->x, p->y, p->z);

        encoder_motor1 = create_subscription<std_msgs::msg::UInt16>("motor_1/encoder", rclcpp::SensorDataQoS(),
          [this](const std_msgs::msg::UInt16::SharedPtr rad) -> void {
            startMotor(rad->data, point.getRadiusXY(), SCALE1, control_motor1, 1);
        });
        encoder_motor2 = create_subscription<std_msgs::msg::UInt16>("motor_2/encoder", rclcpp::SensorDataQoS(),
          [this](const std_msgs::msg::UInt16::SharedPtr rad) -> void {
            startMotor(rad->data, point.getRadiusXZ(), SCALE2, control_motor2, 2);
        });
      });
  }

private:
  Point point = Point();
  rclcpp::Publisher<std_msgs::msg::Int8>::SharedPtr control_motor1;
  rclcpp::Publisher<std_msgs::msg::Int8>::SharedPtr control_motor2;
  rclcpp::Subscription<std_msgs::msg::UInt16>::SharedPtr encoder_motor1;
  rclcpp::Subscription<std_msgs::msg::UInt16>::SharedPtr encoder_motor2;
  rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr _target;

  void startMotor(
    const int rad1, //kąt aktualny
    const int rad2, //kąt docelowy
    const double scale, //skala dla ruchu motora
    rclcpp::Publisher<std_msgs::msg::Int8>::SharedPtr & control, //kontroler motora
    const int id //żeby widzieć o który motor chodzi w info
    ) {
        const int dif = rad2 - rad1; //różnica kątów
        const int rDif = (dif >= 0) ? -POW12 + dif : POW12 + dif; //odwrócona różnica kątów
        std_msgs::msg::Int8 msg;

        if (dif <= POW11 && dif >= -POW11) {msg.data = CHAR (dif * scale);}
        else {msg.data = CHAR (rDif * scale);}

        control->publish(msg);
        RCLCPP_INFO(get_logger(), "%d t: (%d),\t Pos: (%d),\t Dif: (%d)\t (%d),\t Set: (%d)", id, rad2, rad1, dif, rDif, msg.data);
  }


  void test () {
    RCLCPP_INFO(get_logger(), "point: (%g, %g, %g), radiusXY: (%d), radiusXZ: (%d)", point.getX(), point.getY(), point.getZ(), point.getRadiusXY(), point.getRadiusXZ());
  }
};
}  // namespace solution

RCLCPP_COMPONENTS_REGISTER_NODE(solution::Solution)

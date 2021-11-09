#include "ros/ros.h"
#include "equation_calc_service/calc_equation.h"
#include <string>
#include "std_msgs/Float32MultiArray.h"

using namespace std;

ros::Publisher pub;

bool calculate(equation_calc_service::calc_equation::Request &request,
equation_calc_service::calc_equation::Response &response)
{
  float diskriminant = request.b * request.b - 4 * request.a * request.c;
  /*if (diskriminant < 0)
    response.reply.data = ;*/
  if (diskriminant == 0)
  {
    float root = (- request.b)/(2 * request.a);
    response.reply.push_back(root);
  }
  if (diskriminant > 0)
  {
    double root1 = (- request.b + sqrt(diskriminant))/(2 * request.a);
    double root2 = (- request.b - sqrt(diskriminant))/(2 * request.a);
    response.reply.push_back(root1);
    response.reply.push_back(root2);
  }
  std_msgs::Float32MultiArray topic_reply;
  topic_reply.data = response.reply;
  pub.publish(topic_reply);
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "calculate_equation_server");
  ros::NodeHandle node;
  pub = node.advertise <std_msgs::Float32MultiArray> ("topic_reply", 10);
  
  ros::ServiceServer service = node.advertiseService("calculate_equation", calculate);
  ROS_INFO("Rdy to solve equation");
  ros::spin(); 
}

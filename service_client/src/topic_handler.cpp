#include "ros/ros.h"
#include "equation_calc_service/calc_equation.h"
#include <string>
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Float32.h"
#include <vector>

using namespace std;

void topic_handle (const std_msgs::Float32MultiArray::ConstPtr& topic_array)
{
  int number_of_elements = 0;
  for(std::vector<float>::const_iterator it = topic_array->data.begin();
  it != topic_array->data.end(); ++it)
    number_of_elements++;
  if (number_of_elements == 0)
  {
    ROS_INFO("No real roots");
    return;
  }
  if (number_of_elements == 1)
  {
    ROS_INFO("X = %f", topic_array->data[0]);
    return;
  }
  ROS_INFO ("X1 = %f, X2 = %f",
  topic_array->data[0],
  topic_array->data[1]);
  return;
}


int main(int argc, char **argv)
{
  ROS_INFO ("RDY");
  ros::init(argc, argv, "topic_handler");
  ros::NodeHandle node;
  ros::Subscriber subscriber = node.subscribe("topic_reply", 10, topic_handle);
  ros::spin();
  return 0;
}

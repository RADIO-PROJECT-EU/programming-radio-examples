#include <ros/ros.h>
#include "std_msgs/Float32.h"
#include "radio_services/InstructionWithAnswer.h"

bool running = false;
ros::Subscriber sub;
ros::Publisher pub;
std::string input_topic;
ros::NodeHandle* nptr;

void squareCallback(const std_msgs::Float32 msg){
    std_msgs::Float32 res;
    res.data = msg.data * msg.data;
    pub.publish(res);

}

bool nodeStateCallback(radio_services::InstructionWithAnswer::Request &req, radio_services::InstructionWithAnswer::Response &res){

  if(req.command == 0 and running){
    running = false;
    sub.shutdown();
    ROS_INFO("Stoppped radio_cpp_example!");
  }
  else if(req.command == 1 and !running){
    if(!running){
      sub = nptr->subscribe<std_msgs::Float32>(input_topic, 1, squareCallback);
      running = true;
      ROS_INFO("Started radio_cpp_example!");
    }
  }

  res.answer = running;
  return true;
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "radio_cpp_example");

  ros::NodeHandle n;
  nptr = &n;

  n.param("radio_cpp_example/input_topic", input_topic, std::string("/radio_cpp_example/input"));
  if (running){
    sub = n.subscribe<std_msgs::Float32>(input_topic, 1, squareCallback);
}
  pub = n.advertise<std_msgs::Float32>("/radio_cpp_example/output", 1);

  ros::ServiceServer service = n.advertiseService("/radio_cpp_example/node_state_service", nodeStateCallback);

  while(ros::ok()) {
    ros::spinOnce();
  }

  return 0;
}
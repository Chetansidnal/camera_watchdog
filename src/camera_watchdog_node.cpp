#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/CameraInfo.h"
#include "diagnose/diaglib.hpp"
#include <ctime>
using namespace std;
clock_t begin = clock();
clock_t end;
diaglib prodiag;
/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
void chatterCallback(const sensor_msgs::CameraInfo::ConstPtr &msg)
{
  //sensor_msgs::CameraInfo camera_msg = msg;
 //std::cout << "Msg revcived from -----" <<camera_msg<<"\n";
begin = clock();
prodiag.update("S2-105-003", "Camera_has published some msgs");
  ROS_INFO("I heard: [%s]", msg->header.frame_id.c_str());
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "camera_watchdog_node");

std::string config_json;
 
  ros::NodeHandle n;
  n.getParam("/camera_watchdog_node/config_json", config_json);
  std::cout<<"config_json Path -----------"<<config_json;
  prodiag.start_publishing("Node has Started",config_json);
	prodiag.update("S2-105-002", "Waiting for Camera"); 
  ros::Rate r(10);
  ros::Subscriber sub = n.subscribe("/arm_cam3d/rgb/camera_info", 1000, chatterCallback);

while(ros::ok){
  end = clock();
double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
if (elapsed_secs > 3.0){
prodiag.update("E2-105-003", "Camera is offline");
}
ros::spinOnce();
}
  return 0;
}


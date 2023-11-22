#include <ros/ros.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Bool.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <boost/filesystem.hpp>

#include "ros/console.h"
#include "map_server/image_loader.h"
#include "nav_msgs/MapMetaData.h"
#include "nav_msgs/LoadMap.h"
#include "yaml-cpp/yaml.h"

#include <cstdlib>
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
void goal_lab_Callback(const std_msgs::Bool::ConstPtr& msg)
{
	
	ros::NodeHandle n;
  	ros::ServiceClient client = n.serviceClient<nav_msgs::LoadMap>("change_map");
  	nav_msgs::LoadMap srv;
  	srv.request.map_url = "/home/sohaila/Downloads/ros1_2022_ws/src/jetson_bot/navstack_pub/maps/second_floor2.yaml";
  	
	
	

}



int main(int argc, char **argv)
{
  ros::init(argc, argv, "change_map_client");
  ros::NodeHandle n;
  ros::Subscriber sub1 = n.subscribe("goal_lab_request", 100, goal_lab_Callback);
  return 0;
}



#include <ros/ros.h>
#include <std_msgs/Int8.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/Bool.h>
#include <std_msgs/String.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <unistd.h>
#include <string>
#include <nav_msgs/Odometry.h>

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <boost/filesystem.hpp>

#include "ros/console.h"
#include "map_server/image_loader.h"
#include "nav_msgs/MapMetaData.h"
#include "nav_msgs/LoadMap.h"
#include "yaml-cpp/yaml.h"
#include <geometry_msgs/PoseWithCovarianceStamped.h>

#include <cstdlib>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
//Angelo
bool free_angelo = 0; //0 free, 1 not free
bool flag_angelo = 0;
bool state_angelo = 0;
float angelo_pose_x = 0.0;
float angelo_pose_y = 0.0;
float distance_angelo = 0.0;

//Coordinates
//Lab
float lab_x = 1.0;
float lab_y = -18.515785217285156;
float lab_z = 0.752250863692;
float lab_w = 0.658876800376;



float room_x_t = 1.0081628561019897;
float room_y_t = -3.705681324005127;
float room_z_t = -0.6995388497103544;
float room_w_t = 0.7145945687912231;

//Elevator
float elev_x = 11.2131923676;
float elev_y = -0.963505625725;
float elev_z = 0.7071;
float elev_w = 0.7071;

//Elevator middle goal

float elev_x_mg = 11.2131923676;
float elev_y_mg = -0.963505625725;
float elev_z_mg = 0.0;
float elev_w_mg = 1.0;


float front_elev_x = 12.1491613388;
float front_elev_y = 0.288098156452;
float front_elev_z = 0.7071;
float front_elev_w = 0.7071;

bool second_floor = 0;

void changemap_secondflooor(const std_msgs::Bool::ConstPtr& msg)
{
 ros::NodeHandle n;
 ros::ServiceClient client = n.serviceClient<nav_msgs::LoadMap>("change_map");
 nav_msgs::LoadMap srv;
 srv.request.map_url= "/home/ahmed/Downloads/ros_sim/src/hurba_navigation/maps/safia.yaml" ;// secondfloor map
 client.call(srv);
	
 flag_angelo = 0;	
}	
void front_elev(const std_msgs::Int8::ConstPtr& msg)
{
	if(msg->data == 1){
	MoveBaseClient ac("/move_base", true);

	//wait for the action server to come up
	while (!ac.waitForServer(ros::Duration(5.0))) {
	}

	move_base_msgs::MoveBaseGoal goal;
	ros::NodeHandle n;
	ros::Publisher wait = n.advertise<std_msgs::Bool>("/wait",1, 1000);
	std_msgs::Bool msg1;
     	msg1.data = true ; 

	//Move to the middle goal

	goal.target_pose.header.frame_id = "map";
	goal.target_pose.header.stamp = ros::Time::now();

	goal.target_pose.pose.position.x = elev_x_mg ;
	goal.target_pose.pose.position.y = elev_y_mg ;

	goal.target_pose.pose.orientation.z = elev_z_mg ;
	goal.target_pose.pose.orientation.w = elev_w_mg;

	ac.sendGoal(goal);
	ac.waitForResult(ros::Duration(20.0));

	//Move to the Elevator

	goal.target_pose.header.frame_id = "map";
	goal.target_pose.header.stamp = ros::Time::now();

	goal.target_pose.pose.position.x = front_elev_x ;
	goal.target_pose.pose.position.y = front_elev_y ;

	goal.target_pose.pose.orientation.z = front_elev_z ;
	goal.target_pose.pose.orientation.w = front_elev_w;

	ac.sendGoal(goal);
	ac.waitForResult();
	wait.publish(msg1);
	
	}	
}	

//go to lab to take samples
void goal_lab_Callback(const std_msgs::Bool::ConstPtr& msg)
{
	if(msg->data)
	{
	MoveBaseClient ac("/move_base", true);

	//wait for the action server to come up
	while (!ac.waitForServer(ros::Duration(5.0))) {
	}

	move_base_msgs::MoveBaseGoal goal;

	//Move to the First Lab
	goal.target_pose.header.frame_id = "map";
	goal.target_pose.header.stamp = ros::Time::now();

	goal.target_pose.pose.position.x = lab_x;
	goal.target_pose.pose.position.y = lab_y;

	goal.target_pose.pose.orientation.z = lab_z;
	goal.target_pose.pose.orientation.w = lab_w;

	ac.sendGoal(goal);
	}
}


//Elevator Callback
void goal_elev_Callback(const std_msgs::Bool::ConstPtr& msg)
{

	//if (msg->data && flag_angelo == 1)
	if (msg->data)
	{
	MoveBaseClient ac("/move_base", true);


	//wait for the action server to come up
	while (!ac.waitForServer(ros::Duration(5.0))) {
		//ROS_INFO("Waiting for the move_base action server to come up");
	}
	ros::NodeHandle n;
	ros::Publisher elev_reached = n.advertise<std_msgs::Bool>("/elev_reached",1, 1000);
	std_msgs::Bool msg1;
     	msg1.data = true ; 

	move_base_msgs::MoveBaseGoal goal;

	//Move to the First Lab
	goal.target_pose.header.frame_id = "map";
	goal.target_pose.header.stamp = ros::Time::now();

	goal.target_pose.pose.position.x = elev_x;
	goal.target_pose.pose.position.y = elev_y;

	goal.target_pose.pose.orientation.z = elev_z;
	goal.target_pose.pose.orientation.w = elev_w;

	ac.sendGoal(goal);
	ac.waitForResult();
   	elev_reached.publish(msg1);
	
	}
}

int main(int argc, char **argv)
{

    ros::init(argc, argv, "simple_navigation_goals");
    ros::NodeHandle n;

	ros::Subscriber sub1 = n.subscribe("goal_elev_request", 1000, goal_elev_Callback);
	ros::Subscriber sub2 = n.subscribe("goal_lab_request", 1000, goal_lab_Callback);
	ros::Subscriber second_floor = n.subscribe( "second_floor", 1000, changemap_secondflooor);
	ros::Subscriber status_pub = n.subscribe("front_elev", 1000, front_elev);
	ros::spin();
	return 0;
}


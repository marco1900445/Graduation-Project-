
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

//Robots Variables
//Donatello
bool free_donatello = 0; //0 free, 1 not free
bool flag_donatello = 0; 
bool state_donatello = 0;
float donatello_pose_x = 0.0;
float donatello_pose_y = 0.0;
float distance_donatello = 0.0;

//Angelo
bool free_angelo = 0; //0 free, 1 not free
bool flag_angelo = 0;
bool state_angelo = 0;
float angelo_pose_x = 0.0;
float angelo_pose_y = 0.0;
float distance_angelo = 0.0;

//Coordinates
//Lab
float lab_x = 1.4941892623901367;
float lab_y = -18.515785217285156;
float lab_z = 0.752250863692;
float lab_w = 0.658876800376;

//Elevator
float elev_x = 10.22254467010498;
float elev_y = -1.047184944152832;
float elev_z = -0.764862650669;
float elev_w = 0.644193391469;


//All Callback Functions
//Receving Position of Donatello 
void donatello_pose_callback(const nav_msgs::Odometry::ConstPtr& msg)
{
	donatello_pose_x = msg->pose.pose.position.x;
	donatello_pose_y = msg->pose.pose.position.y;
	ROS_INFO("Donatello Pose Done");
}

//Receving Position of Angelo
void angelo_pose_callback(const nav_msgs::Odometry::ConstPtr& msg)
{
	angelo_pose_x = msg->pose.pose.position.x;
	angelo_pose_y = msg->pose.pose.position.y;
	ROS_INFO("Angelo Pose Done");
}

//Move Functions
//Move Donatello to Goal
void move_donatello_to_goal(float x, float y, float z, float w)
{
	MoveBaseClient ac("/donatello/move_base", true);

	ROS_INFO("First we are in state ", ac.getState());
	ROS_INFO("Donatello Called");

	//wait for the action server to come up
	while (!ac.waitForServer(ros::Duration(5.0))) {
		ROS_INFO("Waiting for the move_base action server to come up");
	}

	move_base_msgs::MoveBaseGoal goal;

	free_donatello = 1;

	//Move to the First Lab
	goal.target_pose.header.frame_id = "map";
	goal.target_pose.header.stamp = ros::Time::now();

	goal.target_pose.pose.position.x = x;
	goal.target_pose.pose.position.y = y;

	goal.target_pose.pose.orientation.z = z;
	goal.target_pose.pose.orientation.w = w;

	ac.sendGoal(goal);
	
	while (ac.getState()!=actionlib::SimpleClientGoalState::SUCCEEDED)
	{ }
	free_donatello = 0;
}

//Move Angelo to Goal
void move_angelo_to_goal(float x, float y, float z, float w)
{
	MoveBaseClient ac("/move_base", true);

	ROS_INFO("First we are in state ", ac.getState());
	ROS_INFO("Angelo Called");

	//wait for the action server to come up
	while (!ac.waitForServer(ros::Duration(5.0))) {
		ROS_INFO("Waiting for the move_base action server to come up");
	}

	move_base_msgs::MoveBaseGoal goal;

	free_angelo = 1;

	//Move to the First Lab
	goal.target_pose.header.frame_id = "map";
	goal.target_pose.header.stamp = ros::Time::now();

	goal.target_pose.pose.position.x = x;
	goal.target_pose.pose.position.y = y;

	goal.target_pose.pose.orientation.z = z;
	goal.target_pose.pose.orientation.w = w;

	ac.sendGoal(goal);
	ROS_INFO("Now in state ", ac.getState());

	while (ac.getState()!=actionlib::SimpleClientGoalState::SUCCEEDED)
	{}
	free_donatello = 0;
	
}


//Deciding State of Robot
void state()
{
	//Donatello
	if (free_donatello == 0 && flag_donatello == 0)
	{
		state_donatello = 0;
	}
	else
	{
		state_donatello = 1;
	}
	
	//Angelo
	if (free_angelo == 0 && flag_angelo == 0)
	{
		state_angelo = 0;
	}
	else
	{
		state_angelo = 1;
	}
}

//Lab Callbak
void goal_lab_Callback(const std_msgs::Bool::ConstPtr& msg)
{
	if(msg->data)
	{
		ROS_INFO("Sending Lab Goal");
		if (state_donatello == 0 && state_angelo == 0)
		{
			//Calculate Distances for Both Robots
			distance_donatello = abs(donatello_pose_x - lab_x) + abs(donatello_pose_y - lab_y);
			distance_angelo = abs(angelo_pose_x - lab_x) + abs(angelo_pose_y - lab_y);
		
			//Compare Distance to decide on Robot
			if(distance_donatello<distance_angelo)
			{
				move_donatello_to_goal(lab_x, lab_y, lab_z, lab_w);
				flag_donatello = 1;
			}
			
			else
			{
				move_angelo_to_goal(lab_x, lab_y, lab_z, lab_w);
				flag_angelo = 1;
			}

		}
		else if (state_donatello == 0 && state_angelo == 1)
		{
			move_donatello_to_goal(lab_x, lab_y, lab_z, lab_w);
			flag_donatello = 1;
		}
		else if (state_donatello == 1 && state_angelo == 0)
		{
			move_angelo_to_goal(lab_x, lab_y, lab_z, lab_w);
			flag_angelo = 1;
		}
	
	}
}

//Elevator Callback
void goal_elev_Callback(const std_msgs::Bool::ConstPtr& msg)
{
	if (msg->data)
	{
		ROS_INFO("Sending Elevator Goal");
		if (flag_donatello == 1)
		{
			move_donatello_to_goal(elev_x, elev_y, elev_z, elev_w);
			flag_donatello = 0;
		}
		else if (flag_angelo == 1)
		{
			move_angelo_to_goal(elev_x, elev_y, elev_z, elev_w);
			flag_angelo = 0;
		}
		else
		{
			ROS_INFO("None of the Robots is Free or Has Speciemns Inside");
		}
	}
}



int main(int argc, char **argv)
{

    ros::init(argc, argv, "simple_navigation_goals");
    ros::NodeHandle n;

	ros::Subscriber sub1 = n.subscribe("goal_elev_request", 1000, goal_elev_Callback);
	ros::Subscriber sub2 = n.subscribe("goal_lab_request", 1000, goal_lab_Callback);
	ros::Subscriber sub3 = n.subscribe("donatello/odom", 1000, donatello_pose_callback);
	ros::Subscriber sub4 = n.subscribe("odom", 1000, angelo_pose_callback);
	state();
	
	//Create an object of class SubscribeAndPublish that will take care of everythingx`
	ROS_INFO("hello, I am running");

	ros::spin();
	return 0;
}



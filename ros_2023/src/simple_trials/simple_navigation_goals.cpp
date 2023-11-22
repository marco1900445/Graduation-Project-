//safia
/*
#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <unistd.h>
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;



class SubscribeAndPublish
{
public:
  SubscribeAndPublish()
  {
    //Topic you want to publish
    pub_uv = n_node.advertise<std_msgs::Bool>("/uv", 1);

    //Topic you want to subscribe
    sub_goal = n_node.subscribe("/goal_uv", 1, &SubscribeAndPublish::callback, this);
  }

  void callback(const std_msgs::Bool::ConstPtr& msg)
  {
    std_msgs::Bool msg1;
    msg1.data = true;
    pub_uv.publish(msg1);
	ros::spinOnce();
   if(msg->data)
	{
	MoveBaseClient ac("/move_base", true);
	ROS_INFO("Sending UV Goal");
	while(!ac.waitForServer(ros::Duration(5.0))){
		ROS_INFO("Waiting for the move_base action server to come up");
	}
	move_base_msgs::MoveBaseGoal goal;
	goal.target_pose.header.frame_id = "map";
	goal.target_pose.header.stamp = ros::Time::now();


	goal.target_pose.pose.position.x = 1.84524345398;
	goal.target_pose.pose.position.y = -4.20071315765;
	goal.target_pose.pose.orientation.z = -0.111011513506;
	goal.target_pose.pose.orientation.w = -0.124348705873;
	ROS_INFO("Sending uv goal");
	ac.sendGoal(goal);
	ac.waitForResult(ros::Duration(15.0));

	
	goal.target_pose.pose.position.x = 3.28619527817;
	goal.target_pose.pose.position.y = -0.222037628293;
	goal.target_pose.pose.orientation.z = 0.992238579853;
	goal.target_pose.pose.orientation.w = 0.0;
	ROS_INFO("Sending uv goal");
	ac.sendGoal(goal);
	ac.waitForResult(ros::Duration(15.0));
	
	goal.target_pose.pose.position.x =  -1.35547637939;
	goal.target_pose.pose.position.y = -3.11318922043;
	goal.target_pose.pose.orientation.z = -0.043913342484;
	goal.target_pose.pose.orientation.w = 0.999035343895;
	ROS_INFO("Sending uv goal");
	ac.sendGoal(goal);
	ac.waitForResult(ros::Duration(15.0));
	}

  }

private:
  ros::NodeHandle n_node; 
  ros::Publisher pub_uv;
  ros::Subscriber sub_goal;

};//End of class SubscribeAndPublish

int main(int argc, char **argv)
{
  //Initiate ROS
  ros::init(argc, argv, "simple_navigation_goals");
  ros::NodeHandle n ;


  //Create an object of class SubscribeAndPublish that will take care of everything
  SubscribeAndPublish SAPObject;
  ROS_INFO("hello, I am running");
  ros::spin();

  return 0;
}

*/
/*
//sohaila
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
*/


//working
#include <ros/ros.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Bool.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <unistd.h>


typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

#define goal_lab 1
#define goal_elev 2

int request = 0;
bool req_donatello_status = 0;

void goal_elev_Callback(const std_msgs::Bool::ConstPtr& msg)
{
	if(msg->data)
	{
	MoveBaseClient ac("/move_base", true);
	ROS_INFO("Sending Elevator Goal");
	while(!ac.waitForServer(ros::Duration(5.0))){
		ROS_INFO("Waiting for the move_base action server to come up");
	}
	move_base_msgs::MoveBaseGoal goal;
	goal.target_pose.header.frame_id = "map";
	goal.target_pose.header.stamp = ros::Time::now();
	
	goal.target_pose.pose.position.x = 11.4068216705;  
	goal.target_pose.pose.position.y = 0.0105342166498;
	goal.target_pose.pose.orientation.z = 0.688647175699; //-0.705284809338
	goal.target_pose.pose.orientation.w = 0.708924070488;
	ROS_INFO("Sending goalB1");
	ac.sendGoal(goal);
	
	}
}

void goal_lab_Callback(const std_msgs::Bool::ConstPtr& msg)
{
	if(msg->data)
	{
	MoveBaseClient ac("/move_base", true);
	ROS_INFO("Sending Elevator Goal");
	while(!ac.waitForServer(ros::Duration(5.0))){
		ROS_INFO("Waiting for the move_base action server to come up");
	}
	move_base_msgs::MoveBaseGoal goal;
	goal.target_pose.header.frame_id = "map";
	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x =  1.4941892623901367; 
	goal.target_pose.pose.position.y = -18.515785217285156;
	goal.target_pose.pose.orientation.z = 0.752250863692;
	goal.target_pose.pose.orientation.w = 0.711000492124;
	ROS_INFO("Sending goalA");
	ac.sendGoal(goal);
	}

}



int main(int argc, char** argv){

	ros::init(argc, argv, "simple_navigation_goals");
	
        // MoveBaseClient ac("/move_base", true);
        // ROS_INFO("First we are in state ", ac.getState());

    //     while(!ac.waitForServer(ros::Duration(5.0))){
	// 	ROS_INFO("Waiting for the move_base action server to come up");
	// }

    ros::NodeHandle n ;
	ros::Subscriber sub1 = n.subscribe("goal_elev_request", 1000, goal_elev_Callback);
	ros::Subscriber sub2 = n.subscribe("goal_lab_request", 1000, goal_lab_Callback);

	// move_base_msgs::MoveBaseGoal goal;

	// goal.target_pose.header.frame_id = "map";
	// goal.target_pose.header.stamp = ros::Time::now();

	// ros::Duration(20.0).sleep();
	// goal.target_pose.pose.position.x =  1.4941892623901367; 
	// goal.target_pose.pose.position.y = -18.515785217285156;
	// goal.target_pose.pose.orientation.z = 0.752250863692;
	// goal.target_pose.pose.orientation.w = 0.658876800376;
	// ROS_INFO("Sending goalA");
  	// ac.sendGoal(goal);
	// if (request == goal_lab) {
	// 	goal.target_pose.pose.position.x =  1.4941892623901367; 
	// 	goal.target_pose.pose.position.y = -18.515785217285156;
	// 	goal.target_pose.pose.orientation.z = 0.752250863692;
	// 	goal.target_pose.pose.orientation.w = 0.658876800376;
	// 	ROS_INFO("Sending goalA");
	//   	ac.sendGoal(goal);
	// }

	// if (request == goal_elev) {
	// 	goal.target_pose.pose.position.x = 10.22254467010498;
	// 	goal.target_pose.pose.position.y = -1.047184944152832;
	// 	goal.target_pose.pose.orientation.z = -0.764862650669;
	// 	goal.target_pose.pose.orientation.w = 0.644193391469;
	// 	ROS_INFO("Sending goalB");
	//   	ac.sendGoal(goal);
	// }


  // ros::Publisher state = n.advertise<std_msgs::Int8>("goal", 1000);

  //std_msgs::Int8 state_msg;
	ROS_INFO("hello, I am running");
  ros::spin();
  return 0;
}

/*
#include <ros/ros.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Bool.h>
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

void goal_lab_Callback(const std_msgs::Bool::ConstPtr& msg)
{
	if(msg->data){
		ROS_INFO("change map");
		ros::NodeHandle n;
	  	ros::ServiceClient client = n.serviceClient<nav_msgs::LoadMap>("change_map");
	  	nav_msgs::LoadMap srv;
	  	srv.request.map_url = "/home/gradproject/ros1_2022_ws/src/jetson_bot/navstack_pub/maps/elevator.yaml";
	  	client.call(srv);
  	}
}



int main(int argc, char **argv)
{
  ros::init(argc, argv, "simple_navigation_goals");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("goal_lab_request", 100, goal_lab_Callback);
  ros::spin();
  return 0;
}*/

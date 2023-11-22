#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <unistd.h>

#include <std_msgs/Int8.h>

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


//Disinfect Room
float room_x_t = 7.93577528;   //1.8062875270843506
float room_y_t =3.86568522453 ;   //-1.302328109741211
float room_z_t = 0.00216388702393 ;    //-0.018061937165693626
float room_w_t = 0.9998368699071977;

float room_x = -1.759;
float room_y = -38.476;
float room_z = 0.9749;
float room_w = -0.22255;



//Disinfect Point 1
float point_1_x = 8.83137321472;
float point_1_y = 0.683637976646;
float point_1_z = -0.0189586452529;
float point_1_w = 0.999820268733;


//Disinfect Point 2
float point_2_x = 11.0881280899;
float point_2_y = 2.22047758102;
float point_2_z = 0.71474435417;
float point_2_w = 0.699385807822;

//Disinfect Point 3
float point_3_x = 9.60510540009;
float point_3_y = 3.87534856796;
float point_3_z = 0.999254991204;
float point_3_w = -0.0385935558594;
//bool person_detected=0;



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
	
	//Go to the Room Position
	goal.target_pose.pose.position.x = room_x_t;
	goal.target_pose.pose.position.y = room_y_t;
	goal.target_pose.pose.orientation.z = room_z_t;
	goal.target_pose.pose.orientation.w = room_w_t;
	ROS_INFO("Going to Room");
	ac.sendGoal(goal);

		
	ac.waitForResult();
	pub_uv.publish(msg1);



	goal.target_pose.pose.position.x =point_1_x; //0.14748072624206543     1.14748072624206543;
	goal.target_pose.pose.position.y =point_1_y ;    //-1.7218003273010254     -4.7218003273010254
	goal.target_pose.pose.orientation.z = point_1_z ;   //0.5830772413238414    0.5830772413238414
	goal.target_pose.pose.orientation.w = point_1_w ;    // 0.8124167222861546    0.8124167222861546
	ROS_INFO("Sending uv goal A");
	ac.sendGoal(goal);
	ac.waitForResult(ros::Duration(15.0));
	
	goal.target_pose.pose.position.x = point_2_x;   //-0.7133312225341797    0.3133312225341797
	goal.target_pose.pose.position.y = point_2_y;   //0.2538013458251953    -3.2538013458251953
	goal.target_pose.pose.orientation.z = point_2_z;   // 0.5843468298431963  0.5843468298431963
	goal.target_pose.pose.orientation.w =point_2_w ;   //0.8115040249143602
	ROS_INFO("Sending uv goal B");
	ac.sendGoal(goal);
	ac.waitForResult(ros::Duration(15.0));
		
	goal.target_pose.pose.position.x = point_3_x;   //1.1981731653213501
	goal.target_pose.pose.position.y =point_3_y ;  //-2.5535690784454346
	goal.target_pose.pose.orientation.z = point_3_z;   //0.32864012701609224
	goal.target_pose.pose.orientation.w =point_3_w ;  //0.9444552222921141
	ROS_INFO("Sending uv goal C");
	ac.sendGoal(goal);
	ac.waitForResult(ros::Duration(15.0));

	msg1.data = false;
	pub_uv.publish(msg1);


	
	goal.target_pose.pose.position.x = 0.0;   
	goal.target_pose.pose.position.y =0.0 ;  
	goal.target_pose.pose.orientation.z = 0.0;   
	goal.target_pose.pose.orientation.w =0.99760471426 ;  
	ROS_INFO("Disinfection Done Returning To Home");
	ac.sendGoal(goal);
	
	
	}

  }

private:
  ros::NodeHandle n_node; 
  //InitialPosePublisher::InitialPosePublisher() : private_nh_("~"), wait_for_publish_(false)
  ros::Publisher pub_uv;
  ros::Subscriber sub_goal;
  ros::Subscriber sub_uv;
  //ros::Publisher initial;

};//End of class SubscribeAndPublish

int main(int argc, char **argv)
{
  //Initiate ROS
  ros::init(argc, argv, "disinfection_goals");

  //Create an object of class SubscribeAndPublish that will take care of everything
  SubscribeAndPublish SAPObject;
  

  

  ros::spin();

  return 0;
}


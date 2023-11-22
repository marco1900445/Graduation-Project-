/*#include <ros/ros.h>
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
	
	goal.target_pose.pose.position.x = 0.14748072624206543;
	goal.target_pose.pose.position.y = -1.7218003273010254;
	goal.target_pose.pose.orientation.z = 0.5830772413238414;
	goal.target_pose.pose.orientation.w = 0.8124167222861546;
	ROS_INFO("Sending goalB1");
	ac.sendGoal(goal);
	ac.waitForResult(ros::Duration(3.0));

	goal.target_pose.pose.position.x = -0.7133312225341797;
	goal.target_pose.pose.position.y = 0.2538013458251953;
	goal.target_pose.pose.orientation.z = 0.5843468298431963;
	goal.target_pose.pose.orientation.w = 0.8115040249143602;
	ROS_INFO("Sending goalB2");
	ac.sendGoal(goal);
	ac.waitForResult(ros::Duration(3.0));
	
	goal.target_pose.pose.position.x = 0.1981731653213501;
	goal.target_pose.pose.position.y = 1.5535690784454346;
	goal.target_pose.pose.orientation.z = 0.32864012701609224;
	goal.target_pose.pose.orientation.w = 0.9444552222921141;
	ROS_INFO("Sending goalB3");
	ac.sendGoal(goal);
	ac.waitForResult(ros::Duration(3.0));
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
	goal.target_pose.pose.orientation.w = 0.658876800376;
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
ROS_INFO("Running...");
  ros::spin();
  return 0;
}
*/
#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <unistd.h>
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
	
	goal.target_pose.pose.position.x = 1.5523006916;
	goal.target_pose.pose.position.y = -1.7218003273010254;
	goal.target_pose.pose.orientation.z = 1.49523866177;
	goal.target_pose.pose.orientation.w = 0.0;
	ROS_INFO("Sending uv goal");
	ac.sendGoal(goal);
	ac.waitForResult(ros::Duration(1.0));

	goal.target_pose.pose.position.x = -0.353085905313;
	goal.target_pose.pose.position.y = 4.37793970108;
	goal.target_pose.pose.orientation.z = 4.37793970108;
	goal.target_pose.pose.orientation.w = 0.0;
	ROS_INFO("Sending uv goal");
	ac.sendGoal(goal);
	ac.waitForResult(ros::Duration(1.0));
	
	goal.target_pose.pose.position.x = -1.4552667141;
	goal.target_pose.pose.position.y = 2.39813756943;
	goal.target_pose.pose.orientation.z = -1.25617861748;
	goal.target_pose.pose.orientation.w = 0.0;
	ROS_INFO("Sending uv goal");
	ac.sendGoal(goal);
	ac.waitForResult(ros::Duration(1.0));
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
  ros::init(argc, argv, "subscribe_and_publish");

  //Create an object of class SubscribeAndPublish that will take care of everything
  SubscribeAndPublish SAPObject;

  ros::spin();

  return 0;
}


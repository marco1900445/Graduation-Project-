#!/usr/bin/env python
import  rospy
from geometry_msgs.msg import PoseWithCovarianceStamped


rospy.init_node('initial_pos', anonymous=True)

pub = rospy.Publisher('/initialpose', PoseWithCovarianceStamped, queue_size=1)
initialpose_msg = PoseWithCovarianceStamped()
initialpose_msg.header.frame_id="map"
initialpose_msg.pose.pose.position.x = -0.215371981263
initialpose_msg.pose.pose.position.y = -0.193855464458
initialpose_msg.pose.pose.orientation.z =  0.677292616856
initialpose_msg.pose.pose.orientation.w =  0.0	
#rate = rospy.Rate(1)


while pub.get_num_connections()<1:
    pass
pub.publish(initialpose_msg)
     #rate.sleep()
   

#!/usr/bin/env python
'''
import  rospy
from geometry_msgs.msg import PoseWithCovarianceStamped


rospy.init_node('initial_pos', anonymous=True)

pub = rospy.Publisher('/initialpose', PoseWithCovarianceStamped, queue_size=1)
initialpose_msg = PoseWithCovarianceStamped()
initialpose_msg.header.frame_id="map"
initialpose_msg.pose.pose.position.x = -1.2311122417449951
initialpose_msg.pose.pose.position.y = -2.8990800380706787
initialpose_msg.pose.pose.orientation.w = 0.9341714285765141	
#rate = rospy.Rate(1)


while pub.get_num_connections()<1:
    pass
pub.publish(initialpose_msg)
     #rate.sleep()
   '''

import  rospy
from geometry_msgs.msg import PoseWithCovarianceStamped


rospy.init_node('initial_pose', anonymous=True)

pub = rospy.Publisher('/initialpose', PoseWithCovarianceStamped, queue_size=1)
initialpose_msg = PoseWithCovarianceStamped()
initialpose_msg.header.frame_id="map"
initialpose_msg.pose.pose.position.x = -6.99492931366
initialpose_msg.pose.pose.position.y = -4.17286157608
initialpose_msg.pose.pose.orientation.z =-0.227261952102
initialpose_msg.pose.pose.orientation.w = 0.973833663993
#rate = rospy.Rate(1)


while pub.get_num_connections()<1:
    pass
pub.publish(initialpose_msg)
     #rate.sleep()

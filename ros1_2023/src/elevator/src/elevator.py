#! /usr/bin/env python
from time import sleep
import rospy
from geometry_msgs.msg import PoseWithCovarianceStamped
import actionlib
from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal
from sensor_msgs.msg import LaserScan
from geometry_msgs.msg import Twist
import math
from std_msgs.msg import Int8,Int16,Int32,Bool


def euler_from_quaternion(x, y, z, w):
        """
        Convert a quaternion into euler angles (roll, pitch, yaw)
        roll is rotation around x in radians (counterclockwise)
            pitch is rotation around y in radians (counterclockwise)
            yaw is rotation around z in radians (counterclockwise)
            """
        t0 = +2.0 * (w * x + y * z)
        t1 = +1.0 - 2.0 * (x * x + y * y)
        roll_x = math.atan2(t0, t1)
        
        t2 = +2.0 * (w * y - z * x)
        t2 = +1.0 if t2 > +1.0 else t2
        t2 = -1.0 if t2 < -1.0 else t2
        pitch_y = math.asin(t2)
    
        t3 = +2.0 * (w * z + x * y)
        t4 = +1.0 - 2.0 * (y * y + z * z)
        yaw_z = math.atan2(t3, t4)
        
        return roll_x, pitch_y, yaw_z # in radians






#flags

move_back=0

press_flag=0

wait_flag=0

move_w_odom=0

start_count=1

imu_rotate=0

start_rotate=1

rotated=0

check_flag=0

inelev=0

#distances

press_dist =4.1

odom_start=0.0

door_is_open =2.0

odomdis=1.7

#ANGLE

imu_initial=0

imu_previous=0

#others

ticksPmetre=2920.0

direc=1

odom_start=0

counter=0






def callback(msg):
    global c_position
    global yaw
    c_position=msg
    _,_,yaw=euler_from_quaternion(c_position.pose.pose.orientation.x,c_position.pose.pose.orientation.y,\
                                c_position.pose.pose.orientation.z,c_position.pose.pose.orientation.w)
    rotate()

def movebase_client(distance):
   

    client = actionlib.SimpleActionClient('move_base',MoveBaseAction)
    print("waiting for server")
    client.wait_for_server()
    print("Goal sent")
    goal = MoveBaseGoal()
    goal.target_pose.header.frame_id = "map"
    goal.target_pose.header.stamp = rospy.Time.now()
    _,_,theta=euler_from_quaternion(c_position.pose.pose.orientation.x,\
                                    c_position.pose.pose.orientation.y,c_position.pose.pose.orientation.z,\
                                        c_position.pose.pose.orientation.w)
    goal.target_pose.pose.position.x = c_position.pose.pose.position.x+distance*math.sin(theta)
    goal.target_pose.pose.position.y = c_position.pose.pose.position.y-distance*math.cos(theta)
    goal.target_pose.pose.orientation.x = c_position.pose.pose.orientation.x
    goal.target_pose.pose.orientation.y = c_position.pose.pose.orientation.y
    goal.target_pose.pose.orientation.z = c_position.pose.pose.orientation.z
    goal.target_pose.pose.orientation.w = c_position.pose.pose.orientation.w

    client.send_goal(goal)
    wait = client.wait_for_result()
    print("Goal sent")
    if not wait:
        rospy.logerr("Action server not available!")
        rospy.signal_shutdown("Action server not available!")
    else:
        return client.get_result()


def Status_callback(msg):
    global press_flag
    global inelev
    global imu_rotate
    data=msg.data
    if data ==0:
        press_flag=1
    if data ==1 and inelev==1:
        imu_rotate=1
    if data ==1 and inelev!=1:
        num.data=1
        felev.publish(num)





def press (msg):
    global press_flag
    global move_back
    global check_flag
    if press_flag==1:
        print (msg.ranges[540])
        if move_back==0:
            move.linear.x=-0.1
            #print("right distance = ", msg.ranges[550])
            #print("left distance = ", msg.ranges[560])

            if msg.ranges[540] > press_dist and msg.ranges[540] != float('inf'):
                move.linear.x =0
                print("stop moving forward")
                sleep(2)
                move_back=1
        if move_back ==1:
            move.linear.x=0.1
            if msg.ranges[540] < press_dist-0.1 :
                move.linear.x =0
                move_back=0
                print("stop moving backwards")
                sleep(2)
                press_flag=0
                num.data=1
                pos_snd.publish(num)
        vel_pub.publish(move)



    if check_flag ==1:
        move.linear.x=-0.1
        if msg.ranges[540] > press_dist-0.1 and msg.ranges[540] != float('inf'):
                move.linear.x =0
                print("stop moving forward")
                sleep(2)
                check_flag=0
                num.data=0
                pos_snd.publish(num)
        vel_pub.publish(move)




def door(msg):
    #print(msg.ranges[540])
    global wait_flag
    global move_w_odom
    global odomdis
    if wait_flag==1:
        print("waiting for door to open")
        print(msg.ranges[0])
        if msg.ranges[0] > door_is_open:
            odomdis=1.0
            move_w_odom=1
            wait_flag=0
            move.linear.x=-0.1
            vel_pub.publish(move)


        
def odom(msg):
    global move_w_odom
    global start_count
    global imu_rotate
    global odomdis
    global nav_flag
    global odom_start
    global inelev
    global press_dist
    if move_w_odom==1:
        
        if start_count==1:
            odom_start=msg.data
            start_count=0
            print("moving with odom")
        else:
            if msg.data < odom_start + odomdis*ticksPmetre:
                move.linear.x=-0.1
                print(msg.data - odom_start)
            else:
                move.linear.x=0
                start_count=1
                move_w_odom=0
                imu_rotate=1
                if inelev==1:
                    num.data=3
                    pos_snd.publish(num)
                    press_dist =4.0
                    inelev=0
                else:
                    press_dist =0.85

            vel_pub.publish(move)

def wait(msg):
    global wait_flag
    global press_flag
    wait_flag=1
    press_flag=0

def setting(msg):
    global check_flag
    check_flag=1


def rotate():
    global imu_rotate
    global imu_initial
    global yaw
    global start_rotate
    global imu_previous
    global counter
    global inelev
    global wait_flag

    if imu_rotate ==1:
        if start_rotate ==1:
            imu_initial = yaw
            start_rotate=0
            imu_previous=yaw
            print("start rotating")
        else:
            if abs(yaw-imu_previous)>3.0:
                counter=1
            if yaw +2*math.pi*counter - imu_initial< (math.pi/2):
                move.angular.z=0.5
                imu_previous=yaw
                print(yaw +2*math.pi*counter - imu_initial)
            else:
                move.angular.z=0
                start_rotate=1
                imu_rotate=0
                counter=0
                num.data=2
                if inelev ==0:
                    pos_snd.publish(num)
                if inelev ==1:
                    wait_flag=1
                inelev=1

            vel_pub.publish(move)
            
def edit(msg):
    global press_dist
    press_dist=(msg.data)/100.0
    print(press_dist)






if __name__ == '__main__':

    rospy.init_node('elevator')
    distance_sub=rospy.Subscriber("/robot_pose_ekf/odom_combined", PoseWithCovarianceStamped, callback)
    laser_sub1 = rospy.Subscriber("/scan",LaserScan,press)
    dista = rospy.Subscriber("/distance",Int32,edit)
    laser_sub2 = rospy.Subscriber("/scan",LaserScan,door)
    #slide_sub=rospy.Subscriber('req_goal',PoseWithCovarianceStamped,get_trgt)
    status_get=rospy.Subscriber("status_pub",Int8,Status_callback)
    odometer=rospy.Subscriber("rwheel",Int16,odom)
    waiting_sub=rospy.Subscriber("wait",Bool,wait)
    elevator_reached_sub=rospy.Subscriber("elev_reached",Bool,setting)
    

    vel_pub = rospy.Publisher("cmd_vel", Twist, queue_size=10)
    flr_snd=rospy.Publisher("floor_req_sub",Int8, queue_size=10)
    pos_snd=rospy.Publisher("pose_sub",Int8,queue_size=10)
    felev = rospy.Publisher("front_elev", Int8, queue_size=10)


    num=Int8()
    move = Twist()
    c_position=PoseWithCovarianceStamped()
   # result=movebase_client(0.5)
    rospy.spin()



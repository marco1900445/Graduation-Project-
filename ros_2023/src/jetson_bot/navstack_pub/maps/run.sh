source devel/setup.bash

xterm -e "roslaunch navstack_pub lidar_new.launch" &
sleep 5.

xterm -e "roslaunch navstack_pub fido.launch" &
sleep 5

xterm -e "roslaunch navstack_pub move_base_Don.launch" 



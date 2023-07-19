#! /bin/bash


# cd $root_path/ORB_SLAM3_detailed_comments/Examples/ROS/ORB_SLAM3
# export ROS_PACKAGE_PATH=${ROS_PACKAGE_PATH}:$HOME/orb-slam3_install/orb_slam/ORB_SLAM3_detailed_comments/Examples/ROS/ORB_SLAM3/src


echo "--------------------tar----------------"
sudo apt install python-rosdep  
tar -zxvf rosdistro.tar.gz -C ~


echo "--------------------sed----------------"
sudo sed -i "s#https://raw.githubusercontent.com#file://$HOME#g" 20-default.list
sudo sed -i "s#https://raw.githubusercontent.com#file://$HOME#g" /usr/lib/python2.7/dist-packages/rosdep2/gbpdistro_support.py
sudo sed -i "s#https://raw.githubusercontent.com#file://$HOME#g" /usr/lib/python2.7/dist-packages/rosdep2/rep3.py
sudo sed -i "s#https://raw.githubusercontent.com#file://$HOME#g" /usr/lib/python2.7/dist-packages/rosdistro/__init__.py
sudo mkdir -p /etc/ros/rosdep/sources.list.d
sudo cp 20-default.list /etc/ros/rosdep/sources.list.d/20-default.list

# sudo rosdep init  
# rosdep update 


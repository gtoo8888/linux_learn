#! /bin/bash

set -e
old_path=$(pwd)
mkdir -p $HOME/slam_learn/ttt_ws2/src
cd $HOME/slam_learn/ttt_ws2/src
catkin_init_workspace
catkin_create_pkg imu_realsense roscpp rosmsg

echo ${old_path}/launch
cp -r ${old_path}/launch imu_realsense/
cd ..
catkin_make

# source devel/setup.bash
# roslaunch imu_realsense imu_realsense.launch

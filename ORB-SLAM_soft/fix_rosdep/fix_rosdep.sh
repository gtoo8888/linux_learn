#! /bin/bash
set -e
set -u # 不能使用未定义的变量
# set -x # 每一行执行后显示
# set -o pipefail # 管道中的每个错误都会显示

# chmod 777 fix_rosdep.sh && ./fix_rosdep.sh
# cd $root_path/ORB_SLAM3_detailed_comments/Examples/ROS/ORB_SLAM3
# export ROS_PACKAGE_PATH=${ROS_PACKAGE_PATH}:$HOME/orb-slam3_install/orb_slam/ORB_SLAM3_detailed_comments/Examples/ROS/ORB_SLAM3/src


echo "--------------------tar----------------"
tar -zxvf rosdistro.tar.gz -C $HOME
sudo apt install python-rosdep  


# yaml https://raw.githubusercontent.com/ros/rosdistro/master/rosdep/base.yaml  # 替换前
# yaml file:///$HOME/rosdistro/rosdep/base.yaml # 替换后

# 修改前
# FUERTE_GBPDISTRO_URL = 'https://raw.githubusercontent.com/ros/rosdistro/' \
#     'master/releases/fuerte.yaml'
# REP3_TARGETS_URL = 'https://raw.githubusercontent.com/ros/rosdistro/master/releases/targets.yaml'
# DEFAULT_INDEX_URL = 'https://raw.githubusercontent.com/ros/rosdistro/master/index-v4.yaml'

# 修改后
# FUERTE_GBPDISTRO_URL = 'file://$HOME/rosdistro/' \
#   						  'releases/fuerte.yaml'
# REP3_TARGETS_URL = 'file://$HOME/rosdistro/releases/targets.yaml'
# DEFAULT_INDEX_URL = 'file://$HOME/rosdistro/index-v4.yaml'

echo "--------------------sed----------------"
sed -i "s#https://raw.githubusercontent.com/ros/rosdistro/master#file://$HOME/rosdistro#g" 20-default.list
sudo sed -i "s#https://raw.githubusercontent.com/ros#file://$HOME#g" /usr/lib/python2.7/dist-packages/rosdep2/gbpdistro_support.py
sudo sed -i "s#master/releases#releases#g" /usr/lib/python2.7/dist-packages/rosdep2/gbpdistro_support.py
sudo sed -i "s#https://raw.githubusercontent.com/ros/rosdistro/master#file://$HOME/rosdistro#g" /usr/lib/python2.7/dist-packages/rosdep2/rep3.py
sudo sed -i "s#https://raw.githubusercontent.com/ros/rosdistro/master#file://$HOME/rosdistro#g" /usr/lib/python2.7/dist-packages/rosdistro/__init__.py
sudo mkdir -p /etc/ros/rosdep/sources.list.d
sudo cp 20-default.list /etc/ros/rosdep/sources.list.d/20-default.list

# sudo rosdep init  
# rosdep update 

echo "####################################################################################################"
echo "#####################################   fix rosdeb OK !!  ##########################################"
echo "####################################################################################################"
echo "test: rosdep update"



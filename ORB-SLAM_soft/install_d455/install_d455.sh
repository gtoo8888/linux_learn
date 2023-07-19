#! /bin/bash
set -e
# sudo apt-get install vim

if [ ! -d $HOME/tools ]; then
    mkdir $HOME/tools
fi

root_path=$HOME/install_d455
mkdir -p $HOME/catkin_realsense_ws/src
tar -zxvf realsense-ros-2.XX.tar.gz -C $HOME/catkin_realsense_ws/src
tar -zxvf librealsense.tar.gz -C $HOME/tools
# rm -rf realsense-ros-2.XX.tar.gz librealsense.tar.gz


echo "---------------------------install librealsense----------------------------"
cd $HOME/tools/librealsense
sudo apt-get install libudev-dev pkg-config libgtk-3-dev libusb-1.0-0-dev libglfw3-dev libssl-dev -y
mkdir build && cd build
cmake ../ -DBUILD_EXAMPLES=true
make -j 8 # 需要保证git clone https是通的
sudo make install

echo "####################################################################################################"
echo "#####################################   install librealsense OK !!      ############################"
echo "####################################################################################################"


# librealsene/Cmake/external_libcurl.cmake
# GIT_REPOSITORY "https://github.com/curl/curl.git"         
# GIT_REPOSITORY "git@github.com:curl/curl.git" # 需要配置一下git拉取
# $HOME/librealsense/build/examples/capture/rs-capture
# $HOME/librealsense/build/tools/realsense-viewer/realsense-viewer


echo "---------------------------install realsense-ros ----------------------------"
sudo apt-get install ros-melodic-ddynamic-reconfigure -y
sudo apt-get install ros-melodic-rgbd-launch -y
cd $HOME/catkin_realsense_ws/src
catkin_init_workspace
cd ..
catkin_make clean
catkin_make -DCATKIN_ENABLE_TESTING=False -DCMAKE_BUILD_TYPE=Release
catkin_make install
echo "source $HOME/catkin_realsense_ws/devel/setup.bash" >> $HOME/.bashrc
source $HOME/.bashrc

# roslaunch realsense2_camera rs_camera.launch
# roslaunch realsense2_camera rs_rgbd.launch


echo "####################################################################################################"
echo "#####################################   install realsense-ros OK !!      ############################"
echo "####################################################################################################"

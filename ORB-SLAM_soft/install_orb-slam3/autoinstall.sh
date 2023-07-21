#! /bin/bash
set -e

# wget http://fishros.com/install -O fishros && . fishros  


root_pah=orb_slam
tar -zxvf orb_slam.tar.gz -C ~
# rm -rf orb_slam.tar.gz
cd ~/orb_slam
root_path=$(pwd)

echo "---------------------------install pangolin----------------------------"
sudo apt install libglew-dev -y
cd $root_path/Pangolin
mkdir build && cd build
cmake ..
sudo make -j all
sudo make install

echo "---------------------------install orb-slam3----------------------------"
cd $root_path/ORB_SLAM3_detailed_comments

echo "---------------------------Configuring and building Thirdparty/DBoW2----------------------------"

cd Thirdparty/DBoW2
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j all

cd ../../g2o

echo "---------------------------Configuring and building Thirdparty/g2o---------------------------"

mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j all

cd ../../Sophus

echo "---------------------------Configuring and building Thirdparty/Sophus---------------------------"

mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j all
sudo make install

cd ../../../

echo "---------------------------Uncompress vocabulary ---------------------------"

cd Vocabulary
tar -xf ORBvoc.txt.tar.gz
cd ..

echo "---------------------------Configuring and building ORB_SLAM3---------------------------"

mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j all

cd $root_path/ORB_SLAM3_detailed_comments

echo "####################################################################################################"
echo "#####################################   install ORB_SLAM3 OK !!         ############################"
echo "####################################################################################################"






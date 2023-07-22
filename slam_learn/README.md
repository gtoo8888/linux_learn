# ROS学习

## 创建功能包步骤

### 1.创建工作空间
```bash
mkdir -p $HOME/mylaunch/src
cd $HOME/mylaunch/src
catkin_init_workspace # 初始化工作空间
```
### 2.创建功能包
```bash
cd $HOME/mylaunch/src
catkin_create_pkg imu_realsense roscpp rosmsg
```
### 3.编译功能包
```bash
cd $HOME/mylaunch
catkin_make
```
### 4.添加环境变量
```bash
cd $HOME/mylaunch
source devel/setup.bash

```

##

roslaunch imu_realsense imu_realsense.launch


























































#! /bin/bash

sudo apt-get install vim openssh-server openssh-client net-tools git -y
sudo apt-get install terminator iotop -y
# sudo apt-get install sysstat -y
sudo sed -i "s##PermitRootLogin prohibit-password#PermitRootLogin yes#g" /etc/ssh/sshd_config
# sudo sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config
# sudo vi /etc/ssh/sshd_config
# PermitRootLogin yes 
/etc/init.d/ssh restart
# ssh <name>@127.0.0.1
#! /bin/bash

sudo apt-get install vim openssh-server openssh-client net-tools git tree -y
sudo apt-get install terminator iotop -y
# sudo apt-get install sysstat -y
sudo sed -i "s##PermitRootLogin prohibit-password#PermitRootLogin yes#g" /etc/ssh/sshd_config
# sudo vi /etc/ssh/sshd_config
# PermitRootLogin yes 
/etc/init.d/ssh restart
# ssh <name>@127.0.0.1

# ifconfig -a | grep inet | grep -v 127.0.0.1 | grep -v inet6 | awk {'print $2'}

echo 'HISTTIMEFORMAT="%F %T "' >> ~/.bashrc
echo 'alias sds='\''source devel/setup.bash'\'' ' >> ~/.bashrc
echo 'local_ip=`ifconfig -a | grep inet | grep -v 127.0.0.1 | grep -v inet6 | awk {'\''print $2'\''}` ' >> ~/.bashrc
echo 'echo "local_ip: $local_ip"' >> ~/.bashrc

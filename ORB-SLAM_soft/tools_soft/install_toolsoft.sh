#! /bin/bash
set -e

sudo dpkg -i baidunetdisk_4.17.7_amd64.deb
sudo dpkg -i code_1.80.1-1689183569_amd64.deb
# sudo dpkg -i sogoupinyin_4.2.1.145_amd64.deb
sudo tar -zxvf CLion-2023.1.5.tar.gz -C /opt
sudo tar -zxvf pycharm-community-2023.1.4.tar.gz -C /opt

echo "alias clion='sh /opt/clion-2023.1.5/bin/clion.sh'" >> ~/.bashrc
echo "alias pycharm='sh /opt/pycharm-community-2023.1.4/bin/pycharm.sh'" >> ~/.bashrc
source ~/.bashrc
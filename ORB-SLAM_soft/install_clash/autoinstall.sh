#! /bin/bash

su
clash_dir=$1
sub_url=$2

mkdir clash && cd clash
mv $clash_dir .
gzip -d clash-linux-amd64-v1.14.0.gz
chmod +x clash-linux-amd64-v1.14.0
mv clash-linux-amd64-v1.14.0 /usr/local/bin/clash
wget -O ~/.config/clash/config.yaml $sub_url


# sudo vim /etc/environment  
# # 在 /etc/environment 中加入如下内容
# http_proxy=127.0.0.1:7890
# https_proxy=127.0.0.1:7890
# socks_proxy=127.0.0.1:7891

# 手动
# 127.0.0.1 7890
# 127.0.0.1 7890
# 127.0.0.1 7890
# 127.0.0.1 7891
# localhost, 127.0.0.0/8, ::1
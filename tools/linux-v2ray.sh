#!/bin/bash

if [[ -d "/etc/v2ray" ]];then
	echo "v2ray is already installed, please check."
	exit
fi

if [[ -f "/etc/proxychains.conf" ]];then
	echo "proxychains-ng is already installed, please check."
	exit
fi

check_os(){
	if [[ -f /etc/redhat-release ]];then
		release="centos"
	elif cat /etc/issue | grep -q -E -i "debian";then
		release="debian"
	elif cat /etc/issue | grep -q -E -i "ubuntu";then
		release="ubuntu"
	elif cat /etc/issue | grep -q -E -i "centos|red hat|redhat";then
		release="centos"
	elif cat /proc/version | grep -q -E -i "debian";then
		release="debian"
	elif cat /proc/version | grep -q -E -i "ubuntu";then
		release="ubuntu"
	elif cat /proc/version | grep -q -E -i "centos|red hat|redhat";then
		release="centos"
	fi
}

sudo check_os
case "${release}" in
	centos)
		sudo yum -y update
		sudo yum -y build-essential wget curl unzip;;
	debian|ubuntu)
		sudo apt-get -y update
		sudo apt-get -y install build-essential wget curl unzip;;
esac

wget https://file2.neworld.date/go.sh
sudo bash go.sh
rm -rf go.sh

wget https://file2.neworld.date/v4.14.zip
unzip v4.14.zip
cd proxychains-ng-4.14
./configure
make && sudo make install
sudo cp ./src/proxychains.conf /etc/proxychains.conf
cd ../
sudo rm -rf v4.14.zip proxychains-ng-4.14

sudo sed -i 's#socks4#socks5#g' /etc/proxychains.conf
sudo sed -i 's#9050#1081#g' /etc/proxychains.conf

sudo rm -rf /etc/v2ray/config.json
sudo wget -P /etc/v2ray https://file2.neworld.date/config.json

clear
read -p "Please enter the address of the v2ray node you want to connect to:" node_address
read -p "Please enter your uuid:" uuid

sudo sed -i "s#this_is_the_remote_server_address#$node_address#g" /etc/v2ray/config.json
sudo sed -i "s#this_is_user_uuid#$uuid#g" /etc/v2ray/config.json

sudo systemctl restart v2ray

clear
echo "Please check proxy performance:"
curl myip.ipip.net
proxychains4 curl myip.ipip.net

#END 2020-03-02

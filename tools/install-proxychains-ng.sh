#!/bin/bash
wget https://file2.neworld.date/v4.14.zip
unzip v4.14.zip
cd proxychains-ng-4.14
./configure
make && sudo make install
sudo cp ./src/proxychains.conf /etc/proxychains.conf
cd ../
sudo rm -rf v4.14.zip proxychains-ng-4.14

dpkg --list | grep "^rc" | cut -d " " -f 3 | xargs sudo dpkg --purge
sudo apt-get clean
sudo apt-get autoclean
sudo apt-get autoremove

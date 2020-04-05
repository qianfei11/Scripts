# update
sudo apt-get update
# remove useless software
sudo apt-get remove libreoffice-common unity-webapps-common thunderbird totem rhythmbox simple-scan gnome-mahjongg aisleriot gnome-mines cheese transmission-common gnome-orca webbrowser-app deja-dup
sudo apt-get autoremove
# install pip
sudo apt-get install python-pip
# install vim
sudo apt-get install vim
# install ipython
sudo apt-get install ipython
# install gef
wget -O ~/.gdbinit-gef.py -q https://github.com/hugsy/gef/raw/master/gef.py
echo source ~/.gdbinit-gef.py >> ~/.gdbinit
# install pwntools
sudo apt-get install python2.7 python-pip python-dev git libssl-dev libffi-dev build-essential
sudo pip install --upgrade pwntools
# install zsh
sudo apt-get install zsh
sudo apt-get install git
sudo wget https://github.com/robbyrussell/oh-my-zsh/raw/master/tools/install.sh -O - | sh
chsh -s /usr/bin/zsh
# install x86 environment
sudo apt-get install gcc-multilib
sudo dpkg --add-architecture i386
sudo apt-get update
sudo apt-get install libc6:i386 libstdc++6:i386 open-vm-tools open-vm-tools-desktop
# install qemu
sudo apt-get install qemu
# install tmux
sudo apt-get install tmux
# install and run edb-debugger
sudo apt-get install cmake build-essential libboost-dev libqt5xmlpatterns5-dev qtbase5-dev qt5-default libqt5svg5-dev libgraphviz-dev libcapstone-dev pkg-config
git clone --recursive https://github.com/eteran/edb-debugger.git
cd edb-debugger
mkdir build
cd build
cmake ..
make
./edb
# install pwndbg
git clone https://github.com/pwndbg/pwndbg
cd pwndbg
./setup.sh
# install peda
git clone https://github.com/longld/peda.git ~/peda
echo "source ~/peda/peda.py" >> ~/.gdbinit
# install zsh plugins
git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting
git clone git://github.com/zsh-users/zsh-autosuggestions $ZSH_CUSTOM/plugins/zsh-autosuggestions

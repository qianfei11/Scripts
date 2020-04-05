# Based on Ubuntu-16.04
# update
sudo apt-get update
# install vim
sudo apt-get install vim
# install ipython
sudo apt-get install ipython
# install pwntools
sudo apt-get install python2.7 python-pip python-dev git libssl-dev libffi-dev build-essential
sudo pip install --upgrade pip
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
# install tmux
sudo apt-get install tmux
# install peda
git clone https://github.com/scwuaptx/peda.git ~/peda
echo "source ~/peda/peda.py" >> ~/.gdbinit
# install Pwngdb
git clone https://github.com/scwuaptx/Pwngdb.git ~/Pwngdb
cp ~/Pwngdb/.gdbinit ~/
# install zsh plugins
git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting
git clone git://github.com/zsh-users/zsh-autosuggestions $ZSH_CUSTOM/plugins/zsh-autosuggestions
# install LibcSearcher
git clone https://github.com/lieanu/libc.git
cd libc
git submodule update --init --recursive
sudo python setup.py develop
# install one_gadget
sudo apt install ruby
sudo gem install one_gadget

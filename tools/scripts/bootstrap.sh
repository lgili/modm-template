# /bin/bash

sudo apt-get update -y
sudo apt-get upgrade -y
sudo apt-get install build-essential -y
sudo apt install -y python3 python3-pip scons git libncursesw5 
pip3 install modm 

wget -O- https://github.com/xpack-dev-tools/arm-none-eabi-gcc-xpack/releases/download/v12.2.1-1.2/xpack-arm-none-eabi-gcc-12.2.1-1.2-linux-x64.tar.gz | sudo tar xz -C /opt/
sudo echo  export PATH="/opt/xpack-arm-none-eabi-gcc-12.2.1-1.2/bin:$PATH" >> $HOME/.bashrc

sudo apt install openocd -y


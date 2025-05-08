#!/usr/bin/sh

sudo apt update && sudo apt upgrade

sudo apt-get install build-essential autoconf libtool pkg-config -y

git clone https://github.com/stephane/libmodbus.git

cd libmodbus

./autogen.sh

./configure

make

sudo make install

sudo ldconfig

# Temporary add
#export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH

# Permanently add 
#echo "/usr/local/lib" | sudo tee /etc/ld.so.conf.d/libmodbus.conf
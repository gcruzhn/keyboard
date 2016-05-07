#!/bin/bash
#Teensy setup script. Configures your Ubuntu linux machine for developing on the Teensy.
#By: Brandon Foltz
#September 18, 2012
#Released under MIT license:

#Copyright (c) 2012 Brandon Foltz

#Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including #without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to #the following conditions:

#The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
#NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
#SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#Enjoy!

OSIS64=0
INSTALLPATH="$HOME/teensy"
BIT64LOADERURL="http://www.pjrc.com/teensy/teensy.64bit.gz"
BIT32LOADERURL="http://www.pjrc.com/teensy/teensy.gz"
UDEVRULESURL="http://www.pjrc.com/teensy/49-teensy.rules"
TMPRULESPATH="/tmp/49-teensy.rules"
RULESPATH="/etc/udev/rules.d"
TMPLOADERPATH="/tmp/teensy_loader.gz"
UNZIPPEDPATH="/tmp/teensy_loader"
SYSTEMBINPATH="/usr/local/bin"
UNZIPPEDFILENAME="teensy_loader"
DOWNLOADGCCAVR=0

echo "Welcome to the Teensy setup utility!"
echo "This will configure your system for development on the Teensy."
echo "Please note that an internet connection is required to use this script."

# Make sure only root can run our script
if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root" 1>&2
   exit 1
fi

#check if we're running a 32-bit or 64-bit OS
if [ `uname -m` == "x86_64" ]; then
	echo "64-bit OS detected."
	OSIS64=1
else
	echo "32-bit OS detected."
	OSIS64=0
fi

#TODO: need a way to check which distro we're running, and use the appropriate package manager
#check if user wants to install the C compiler from their package manager
INVALIDINPUT=1
while [ $INVALIDINPUT == 1 ]; do
echo "Download and install the gcc-avr C compiler and libraries? y/n"
read -e CHOICE
if [ $CHOICE == "y" ]; then
	echo "gcc-avr will be installed."
	DOWNLOADGCCAVR=1
	INVALIDINPUT=0
elif [ $CHOICE == "n" ]; then
	echo "gcc-avr will not be installed."
	DOWNLOADGCCAVR=0
	INVALIDINPUT=0
else
	echo "Invalid input. Please try again."
fi
done;

echo "Your selections will now be installed. Continue? y/n"
read -e CHOICE
if [ $CHOICE == "y" ]; then
	continue
else
	exit 1
fi

#and now we start the actual installing!
#first, install gcc-avr (if requested)
#assuming we're on ubuntu/debian, apt-get is the name of the game
if [ $DOWNLOADGCCAVR == 1 ]; then
	echo "Installing gcc-avr..."
	apt-get install gcc-avr binutils-avr avr-libc
fi

#download the udev rules....
wget -O $TMPRULESPATH $UDEVRULESURL

#install udev rules...
cp $TMPRULESPATH $RULESPATH

#next, download the teensy loader...
echo "Downloading and installing the Teensy loader..."
if [ $OSIS64 == 1 ]; then
	wget -O $TMPLOADERPATH $BIT64LOADERURL
else
	wget -O $TMPLOADERPATH $BIT32LOADERURL
fi 

#install teensy loader...
gzip -dv $TMPLOADERPATH
cp $UNZIPPEDPATH $SYSTEMBINPATH
chmod +x $SYSTEMBINPATH/$UNZIPPEDFILENAME

#finished!
echo "Your system is now setup for developing on the Teensy."
echo "To run the Teensy loader, type \"teensy_loader\" in your favorite terminal."
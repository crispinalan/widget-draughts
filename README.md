# Widget Draughts

Widget Draughts is a computer draughts game for Linux written using C++ and wxWidgets.

![](widget-draughts.png)

## Getting Started

Draughts (also known as checkers) is a  strategy board game for two players which involves moving pieces diagonally on an 8×8 (64 cell) checkerboard. Each player has their own colour and begins the game with 12 pieces which can only move and capture in a diagonally forwards direction. If an opponents piece is in the next square, the player can jump over it and capture it, removing the piece from the board. If a player can jump, it must and if after making a jump another jump is possible it must jump again. To win the game you must stop the opponent (computer) from moving when it comes to their turn which can be done by taking all of their pieces or by blocking their pieces so that there is nowhere to move. A piece which reaches the other end of the board is "crowned" a king. Kings are allowed to move and capture diagonally forwards and backwards and so are more powerful and valuable than ordinary pieces. For more information follow this [link](https://en.wikipedia.org/wiki/Draughts).

With Widget Draughts you play against the computer. The human player is white and the computer is black.


## Install Using Deb Package

You can install Widget Draughts by using the appropriate deb package located at [deb-packages](https://github.com/crispinalan/widget-draughts/tree/master/deb-packages/) 

Use the _wwxdraughts_1.0.3_amd64.deb_  package for 64-bit Debian and Debian based distributions (e.g. Linux Mint, Ubuntu and it derivatives). 

Use the _wxdraughts_1.0.3_armhf.deb_  package for the Raspberry Pi.

Right click on the deb package and select "Save Link As" to download.

Further details below:

### Verify Deb Package

You can verify the deb package by checking the md5sum of the deb package with the appropriate file provided. So for the 64-bit operating system deb package (amd64) it can be checked by running:

```
cat wxdraughts_1.0.3_amd64.md5
md5sum wxdraughts_1.0.3_amd64.deb
```
Both sums (numbers) should be the same.

### Linux Mint Debian Edition 4 (Debbie)

Download the _wxdraughts_1.0.3_amd64.deb_ package into the Downloads directory. Open a terminal and install widgetdraughts using:
```
cd Downloads
sudo dpkg -i wxdraughts_1.0.3_amd64.deb 
```
Enter your sudo (user) password when prompted.

*Don't like the terminal command line:*  You can right click on the deb package file and select "Open with GDebi Package Installer". Then click the "Install Package" button.
 
### Debian

Download the _wxdraughts_1.0.3_amd64.deb_ package into the Downloads directory. Open a terminal and install Widget Draughts using the commands below (don't forget the "-" with su):

```
user@debian:su -
Password: 
root@debian:~# cd /home/user/Downloads/
root@debian:/home/user/Downloads# dpkg -i wxdraughts_1.0.3_amd64.deb
```

### Raspberry Pi

Download the _wxdraughts_1.0.3_armhf.deb_ package (not the amd64 package) into the Downloads directory. Open a terminal and install Widget Draughts using:

```
sudo dpkg -i wxdraughts_1.0.3_armhf.deb
```

Widget Draughts should be in: menu -> other

Note: The Raspberry Pi deb package is 32-bit, not 64-bit, and so should not be used with 64-bit operating systems.

### Missing Dependencies

If Widget Draughts fails to install due to missing dependencies then run

```
sudo apt-get install -f
```
Then use dpkg again to reinstall the Widget Draughts deb package. 

The _sudo apt-get install -f_  attempts to fix (-f) the problem by installing the missing dependencies. dpkg will install widgetdraughts once the all dependencies are present. 

So for for the Raspberry Pi you would run

```
sudo apt-get install -f
sudo dpkg -i wxdraughts_1.0.3_armhf.deb
```
You may have to logout and login for changes to take effect. Widget Draughts should be in: menu -> other.

### Remove Widget Draughts

To remove widget draughts run:

```
sudo dpkg -r  widgetdraughts 
```

## Build From Source

For other distributions you can build Widget Draughts from source 

```
mkdir build  
cd build  
cmake ..
make
sudo make install 
```
Widget Draughts (wxdraughts) is installed to /usr/local/bin

### Build From Source Prerequisites

To build from source you need to install the following packages (dependencies)

```
sudo apt install build-essential
sudo apt install cmake
sudo apt install libwxgtk3.0-dev
sudo apt install git 
```

## Versioning

[SemVer](http://semver.org/) is used for versioning. The version number has the form 0.0.0 representing major, minor and bug fix changes. Currently at 1.0.3.

## Authors

* **Alan Crispin** [(crispina)](https://github.com/crispinalan)


## License

This project is licensed under the Apache 2.0 License.

[Apache 2.0 License](https://www.apache.org/licenses/LICENSE-2.0)

## Roadmap

Future updates:
```
check for blocking wins
strengthen draughts-play minimax engine
check pieces threatened with capture 
check pieces endangered when making a move
introduce triple kings 
improve end game 
provide additional options
``` 



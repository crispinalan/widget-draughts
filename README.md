# Widget Draughts

Widget Draughts is a computer draughts game for Linux written using C++ and wxWidgets.

![](widget-draughts.png)

## Getting Started

Draughts (also known as checkers) is a  strategy board game for two players which involves moving pieces diagonally on an 8×8 (64 cell) checkerboard. Each player has their own colour and begins the game with 12 pieces which can only move and capture in a diagonally forwards direction. If an opponents piece is in the next square, the player can jump over it and capture it, removing the piece from the board. If a player can jump, it must and if after making a jump another jump is possible it must jump again. To win the game you must stop the opponent (computer) from moving when it comes to their turn which can be done by taking all of their pieces or by blocking their pieces so that there is nowhere to move. A piece which reaches the other end of the board is "crowned" a king. Kings are allowed to move and capture diagonally forwards and backwards and so are more powerful and valuable than ordinary pieces. For more information follow this [link](https://en.wikipedia.org/wiki/Draughts).

With Widget Draughts you play against the computer. The human player is black and the computer is white.

### Prerequisites

To build and install Widget Draughts on Ubuntu and derivatives you need to install the following packages (if not already installed) 

```
sudo apt install build-essential
sudo apt install cmake
sudo apt install libwxgtk3.0-dev
sudo apt install git 
```

### Build From Source

To build Widget Draughts from source 

```
mkdir build  
cd build  
cmake ..
make
su (Debian)
make install
or
sudo make install (Ubuntu)
```
Widget Draughts is installed to /usr/local/wxdraughts

Use a menu editor such as [Alacarte](https://en.wikipedia.org/wiki/Alacarte) on GNOME to add Widget Draughts to the system menu.

### Binaries

![](snapstore.png)

A Widget Draughts snap package is available at 

[Widget Draughts Package](https://snapcraft.io/widget-draughts)

To install use ..
```
sudo snap install --edge widget-draughts
```
To remove use ..
```
sudo snap remove widget-draughts
```

The snap package has been developed to learn about snapcraft packaging but it is recommended to install "Widget Draughts" from source to get the latest version. With a snap package the application is distributed (sandboxed) inside a minimal virtual machine. 

## Versioning

[SemVer](http://semver.org/) is used for versioning. 

## Authors

* **Alan Crispin** [(crispina)](https://github.com/crispinalan)


## License

This project is licensed under the GPL License.

## Roadmap

Future updates:
```
check for blocking wins
strengthen draughts-play minimax engine
check pieces threatened with capture 
check pieces endangered when making a move
introduce triple kings 
provide an option to set skill level
improve end game 
``` 

## History

Widget Draughts was orginally developed in 2011 as a C++ wxWidgets application using Code::Blocks. This code was directly translated into the [Qt Draughts](https://bitbucket.org/crispinalan/qt-5-draughts/src/master/) application in 2013. With the current release wxWidgets has again been used for developing the graphical user interface. The version number has been reset to 1.0.0 representing major, minor and bug fix changes. The [wxWidgets](https://www.wxwidgets.org/) library licence is L-GPL (Library General Public Licence) with an exception stating that derived works in binary form may be distributed on the user’s own terms. The [CodeLite](https://codelite.org/) IDE has been used for code development. CodeLite is distributed under the terms of the GPLv2 license, with an exception for plugins. 

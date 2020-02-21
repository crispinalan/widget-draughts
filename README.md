# Widget Draughts

Widget Draughts is a computer draughts game for Linux written using C++ and wxWidgets.

![](widget-draughts.png)

## Getting Started

Draughts (also known as checkers) is a  strategy board games for two players which involve diagonal moves played on an 8×8 (64 cell) checkerboard. Each player has their own colour and begins the game with 12 pieces. If an opponents piece is in the next square, the player can jump over it and capture it, removing the piece from the board. To win the game you must stop the opponent (computer) from moving when it comes to their turn which can be done by taking all of their pieces or by blocking their pieces so that there is nowhere to move. For more information follow this [link](https://en.wikipedia.org/wiki/Draughts).

With Widget Draughts you play against the computer. The human player is  black and the computer is white.

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
cd src
mkdir build  
cd build  
cmake ..
make
su (or sudo)
make install
```
Widget Draughts is installed to /usr/local/wxdraughts

Use a menu editor such as [Alacarte](https://en.wikipedia.org/wiki/Alacarte) on GNOME to add Widget Draughts to the system menu.

### Binaries



## Versioning

[SemVer](http://semver.org/) is used for versioning. 

## Authors

* **Alan Crispin** [crispina](https://github.com/crispinalan)


## License

This project is licensed under the GPL License. 

## History

Widget Draughts was orginally developed in 2011 as a C++ wxWidgets application developed using Code::Blocks and the build-in wxSmith graphical user interface (GUI) editor. This code was directly translated into the [Qt Draughts](https://bitbucket.org/crispinalan/qt-5-draughts/src/master/) application in 2013. With the recent Qt license [changes](https://www.qt.io/blog/qt-offering-changes-2020) wxWidgets has again been used for developing the graphical user interface and the original draughts code has been updated with the current 2020 release. The version number has been reset to 1.0. The [wxWidgets](https://www.wxwidgets.org/) library licence is L-GPL (Library General Public Licence) with an exception stating that derived works in binary form may be distributed on the user’s own terms. The [CodeLite](https://codelite.org/) IDE has been used for code development. It is distributed under the terms of the GPLv2 license, with an exception for plugins. 

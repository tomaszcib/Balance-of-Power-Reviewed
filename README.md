# Balance of Power: Reviewed

Current version: beta 1.0

The game takes place in 1980s, a period of geopolitical rivalry between the USA and the USSR. In the Balance of Power, the player takes the role of the American President or General Secretary of the Soviet Union. The goal is to improve the player's country's standing in the world relative to the other superpower, while maintaining the peace and avoiding a nuclear war. A variety of possible means one can use, either military, economic or political, make the gameplay complex and challenging. 

![In-game screenshot](https://github.com/tomaszcib/Balance-of-Power-Reviewed/blob/master/thumbnail.png)

The game manual can be found [here](http://www.atarimania.com/game-atari-st-balance-of-power-the-1990-edition_8658.html).

## Disclaimer
The game is a port of [Chris Crawford's](http://www.erasmatazz.com/) work called "Balance of Power: 1990 edition" from 1988. I did not write core and AI routines. 

## Known bugs
* Loading the game: there are issues with loading the SaveGame.dat file atthe startup causing country leaders' names strings not to be read correctly. In general, loading functions are not 100% sure to be working and some bugs may occur as well.

## Running the game - Windows
The Windows package with no installation requirements has been placed in the "bin" folder. The .zip contains game binary file, shared libraries and data files, the only thing to do is to unpack it and run the main .exe.

## Running the game - GNU/Linux
### Requirements
You should have the following packages/dependencies installed on your system:

* libQt5Widgets5
* libQt5Gui5
* libQt5Core5
* libGL1
* libstdc++6
* glibc
* libgcc_s1

As well as the newest possible version of *g++* compiler. 

### Downloading and running
Download the bin/gnulinux-build folder from the repository and unpack it, for example to /home/your-name/BoPReviewed folder.

Execute in the shell script:

`$ cd /home/your-name/BoPReviewed`

`$ ./BoPReviewed`

if somehow the application does not show up, try recompiling it with

`$ make`

command.

## Building the game with Qt Creator (any operating system)
### Requirements
* Qt 5.0 or newer (5.7.0 in my case)
* C++ compiler with C++11 standard compatibility (g++ for GNU/Linux and MinGW for Windows in my case)

### Loading the project file
If you want to compile the source manually, download the *src* folder from this repository and open *bopreviewed.pro* file inside your Qt Creator IDE. Simply press "Build" button.

**Important:** before running the app, remember to copy .txt and .dat files from src/data subfolder to your destination build directory.

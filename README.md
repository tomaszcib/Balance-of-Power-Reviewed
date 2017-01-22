# Balance of Power: Reviewed

Current version: beta 1.1

The game takes place in 1980s, a period of geopolitical rivalry between the USA and the USSR. In the Balance of Power, the player takes the role of the American President or General Secretary of the Soviet Union. The goal is to improve the player's country's standing in the world relative to the other superpower, while maintaining the peace and avoiding a nuclear war. A variety of possible means one can use, either military, economic or political, makes the gameplay complex and challenging. 

![In-game screenshot](https://github.com/tomaszcib/Balance-of-Power-Reviewed/blob/master/thumbnail.png)

The game manual can be found [here](http://www.atarimania.com/game-atari-st-balance-of-power-the-1990-edition_8658.html).

## Disclaimer
The game is an adaptation of [Chris Crawford's](http://www.erasmatazz.com/) work called "Balance of Power: 1990 edition" from 1988.

## Known bugs
* Loading the game: it is not possible to play the game just right after the startup of the program. Set a new game every time you run the app and the game should be working.

## Running the game - Windows
The Windows package with no installation requirements has been placed in the [bin](bin/) folder. The .zip contains game binary file, shared libraries and data files, the only thing to do is to unpack it and run the main .exe.

## Building the game with Qt Creator (any operating system)
### Requirements
* Qt 5.0 or newer (5.7.0 in my case)
* C++ compiler with C++11 standard compatibility (g++ for GNU/Linux and MinGW for Windows in my case)

### Loading the project file
If you want to compile the source manually, download the [src](src/) folder from this repository and open *bopreviewed.pro* file inside your Qt Creator IDE. Simply press "Build" button.

**Important:** before running the app, remember to copy **.dat** files from [src/data](src/data/) subfolder to your Qt working directory.

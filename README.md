# Pong
The game Pong with coop mode in its original arcade look.
For single player experience, it comes with an A.I. as opponent which consists of a neural network and is trained with up to 2 full days of experience.

## Features
* Coop mode with arrow keys and W/S keys
* A.I. vs. A.I.
* Player vs. A.I. (Easy, Medium, Hard)
* Full screen mode

## Dependencies
* [SFML 2.5](https://github.com/SFML/sfml)
* [Boost Math](https://www.boost.org)  
* [SFMLApp](https://github.com/wagnrd/SFMLApp) (included in source code)
* [SFMLMath](https://github.com/wagnrd/SFMLMath) (included in source code)
* [OpenNN](https://github.com/Artelnics/OpenNN) (included in source code)
* C++11 (C++17 is recommended)

To satisfy the dependencies you need the following packages:

```shell
$ sudo apt install libsfml-dev libboost-math-dev
```

## Build

```shell
$ mkdir build
$ cd build
$ cmake ..
$ make
```
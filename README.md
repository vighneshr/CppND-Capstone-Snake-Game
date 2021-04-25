# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## Basic game instructions

1. User can choose to play from the available levels
2. User input is required within 5 seconds or game exits

## Addressing Rubic points
1. Loops, Functions, I/O:
   The project demonstrates an understanding of C++ functions and control structures : Demonstrated throughtout the project
   The project reads data from a file and process the data, or the program writes data to a file : Demonstrated in layout.cpp line#46,14
   The project accepts user input and processes the input : Demonstrated in pregame.h line# 18 - 62

2. Object Oriented Programming
   The project uses Object Oriented Programming techniques :  Demostrated throughtout the project
   Classes use appropriate access specifiers for class members : Demonstrated throughtout the project classes
   Class constructors utilize member initialization lists : Demonstrated in snake.h line#11
   Classes abstract implementation details from their interfaces : Demostrated throughtout the project
   Classes encapsulate behavior : Demonstrated in bonuspoints.cpp line#21, 54
   Classes follow an appropriate inheritance hierarchy : Demonstrated in game.h pregame.h layout.h
   Overloaded functions allow the same function to operate on different parameters : Demonstrated in renderer.cpp line# 48, 96
   Derived class functions override virtual base class functions : Demonstrated in game.h line#102, pregame line#37, layout.h#22
   Templates generalize functions in the project : Demonstrated in bonuspoints.h line#30
 
3. Memory Management
   The project makes use of references in function declarations : Demostrated throughtout the project functions wherever appropriate
   The project uses destructors appropriately : Demonstrated in bonuspoints.cpp line#31
   The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate : Demonstrated in game.cpp
   The project follows the Rule of 5 : Demonstrated in game.h line#17 - 68 and game.cpp line# 31, 53
   The project uses move semantics to move data, instead of copying it, where possible : Demonstrated in renderer.cpp line#44
   The project uses smart pointers instead of raw pointers :  Demonstrated in game.h line#87
   
4. Concurrency
   The project uses multithreading : Demonstrated in game.h line#88 and bonuspoints.cpp
   A promise and future is used in the project : Demonstrated in pregame.h
   A mutex or lock is used in the project : Demonstrated in bonuspoints.h line#40
   A condition variable is used in the project : Demonstrated in bonuspoints.h line#39

## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg

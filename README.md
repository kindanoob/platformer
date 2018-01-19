# platformer
Basic platformer game engine implemented in C++ using SFML

Requirements: 
    1) C++11 
    2) SFML 2.3.2
    
The program was tested on Ubuntu 16.04 LTS Xenial, gcc 5.4.0.

Instructions:
1) For an out-of-place build: create a build directory (mkdir build)
2) Change directory to the created build directory (cd build)
3) Create build files with CMake in the build directory (cmake ..)
4) Build the project (e.g. for Unix makefiles it is achieved by using "make" command in the terminal)
5) Launch the executable file "platformer"
6) Mouse controls. Use mouse to navigate the main menu. Click on the menu buttons with left mouse click.
7) Keyboard controls. Use Left/Right arrow keys to move your character left/right. 
    Use Up arrow button to jump. Use Z button to shoot (only with weapon equipped).
8) Currently there is only one sandbox level without any goal. Collect apples (green squares), avoid obstacles (red squares), kill enemies (by jumping over them or by shooting them), pick-up weapons (yellow squares).


The project is very early in the development stage and there are a lot of things to be implemented.

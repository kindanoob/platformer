# platformer
Basic platformer game engine implemented in C++ using SFML

Requirements: 
    1) C++14
    2) SFML 2.6.1
    
The program was tested on Ubuntu 22.04 LTS Jammy, gcc 11.4.0.

Instructions for an out-or-place build:
1) Go to the directory containing the CMakeLists.txt file.
2) Run `cmake -S . -B build`. This will create a `build` directory and put CMake files there.
3) Go to the `build` directory.
4) Build the project (e.g. for Unix makefiles it is achieved by running `make` command in the terminal).
5) Launch the executable file "platformer"
6) Mouse controls. Use mouse to navigate the main menu. Click on the menu buttons with left mouse click.
7) Keyboard controls. Use Left/Right arrow keys to move your character left/right. 
    Use Up arrow button to jump. Use Z button to shoot (only with weapon equipped).
8) Currently there is only one sandbox level without any goal. Collect apples (green squares), avoid obstacles (red squares), kill enemies (by jumping over them or by shooting them), pick-up weapons (yellow squares).


The project is very early in the development stage and there are a lot of things to be implemented.

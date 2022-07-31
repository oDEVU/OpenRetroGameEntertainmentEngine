# OpenRetroGameYngine

Retro doom like engine with modern liblares. O.R.G.Y uses raylib and c++.

**Thanks to 3DSage for great tutorial.**

his chanel : https://www.youtube.com/c/3DSage

Engine presentation : https://youtu.be/PSlYORvC2ks

Editor presentation : https://youtu.be/DXZNMwoE_4E

# Dependencies
* raylib
* boost
* g++

[uses c++20]

# How to compile?

### **Arch linux:**

1. Download zip or use git clone command.

2. Download raylib:
```sh
sudo pacman -Sy raylib
```
3. Go to editor folder

4. Compile editor:
```sh
g++ -lstdc++fs -std=c++20 -o editor editor.cpp pathhandler.cpp -lstdc++fs -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```
(This compile command works only for x11, Later you can compile game from editor)

### **OpenSUSE:**

1. Download zip or use git clone command.

2. Download raylib:
```sh
zypper in raylib-devel
```

3. Go to editor folder

4. Compile editor:
```sh
g++ -lstdc++fs -std=c++20 -o editor editor.cpp pathhandler.cpp -lstdc++fs -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```
(This compile command works only for x11, Later you can compile game from editor)

### **Other OS:**

1. Download zip or use git clone command.

2. Download and install raylib and other dependences (You can find many tutorials for other platforms)

3. Compile it with your c++ compiler.

(i will add other OS later)

# Controlls

* WASD - moving (xy)
* left shift/left control - up/down (z)
* Arrows = Camera
* F1 - Toggle debug info
* F2 - Toggle VSYNC
* TAB - Take screenshots








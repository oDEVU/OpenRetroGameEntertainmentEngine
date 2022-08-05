# OpenRetroGameYngine

Retro doom like engine with modern liblares. O.R.G.Y uses raylib and c++.

**Thanks to 3DSage for great tutorial.**

His chanel : https://www.youtube.com/c/3DSage

Presentation : https://youtu.be/iw_VdbiWB5A

Documentation will be created when any usable version will be released.

# Dependencies
* [raylib](https://www.raylib.com/)+[raygui](https://github.com/raysan5/raygui)  -for editor
* [SFML](https://www.sfml-dev.org/)
* [Selba Ward](https://github.com/Hapaxia/SelbaWard)
* boost
* g++

[uses c++20]

# How to compile?

### **Arch linux:**

1. Download zip or use git clone command.

2. Download dependences.

For example:
```sh
sudo pacman -Sy raylib
```
3. Go to editor folder

4. Compile editor:
```sh
g++ -lstdc++fs -std=c++20 -o editor editor.cpp -lstdc++fs -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```
(From here you will be able to compile game with 1 button)

### **OpenSUSE:**

1. Download zip or use git clone command.

2. Download dependences.

For example:
```sh
zypper in raylib-devel
```

3. Go to editor folder

4. Compile editor:
```sh
g++ -lstdc++fs -std=c++20 -o editor editor.cpp -lstdc++fs -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```
(From here you will be able to compile game with 1 button)

### **Other OS:**

1. Download zip or use git clone command.

2. Download and install dependences (You can find many tutorials for other platforms)

3. Compile it with your c++ compiler.

(i will add other OS later)

# Controlls

* WASD - moving (xy)
* left shift/left control - up/down (z)
* Arrows = Camera
* F1 - Toggle debug info
* F2 - Toggle VSYNC
* F3 - Show normal buffer
* F4 - Change lighting mode
* F5 - Show light only scene

(screenshot function temporarily removed)









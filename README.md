# OpenRetroGameYngine

Retro doom like engine with modern liblares. O.R.G.Y uses raylib and c++.

**Thanks to 3DSage for great tutorial.**

his chanel : https://www.youtube.com/c/3DSage

Engine presentation : https://youtu.be/PSlYORvC2ks

# How to compile?

### **Arch linux:**

1. Download zip or use git clone command.

2. Download raylib:
```sh
sudo pacman -Sy raylib
```

3. Compile:
```sh
cc main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```
(This compile command works only for x11)

### **OpenSUSE:**

1. Download zip or use git clone command.

2. Download raylib:
```sh
zypper in raylib-devel
```

3. Compile:
```sh
cc main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```
(This compile command works only for x11)

### **Other OS:**

1. Download zip or use git clone command.

2. Download and install raylib (You can find many tutorials for other platforms)

3. Compile it with your c++ compiler.

(i will add other OS later)

# Controlls

* WASD - moving (xy)
* left shift/left control - up/down (z)
* Arrows = Camera
* F1 - Toggle debug info
* F2 - Toggle VSYNC








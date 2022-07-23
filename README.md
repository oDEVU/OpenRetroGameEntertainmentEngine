# OpenRetroGameYngine

Retro doom like engine with modern liblares. O.R.G.Y uses raylib and c++.

**Thanks to 3DSage for great tutorial.**

his chanel : https://www.youtube.com/c/3DSage

#How to compile?

**Arch linux:**

Download zip or use git clone command.

Download raylib:
```sh
sudo pacman -Sy raylib
```

Compile:
```sh
cc main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```
(This compile command works only for x11)

**OpenSUSE:**

Download zip or use git clone command.

Download raylib:
```sh
zypper in raylib-devel
```

Compile:
```sh
cc main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```
(This compile command works only for x11)

**Other OS:**

Download zip or use git clone command.

Download and install raylib (You can find many tutorials for other platforms)

Compile it with your c++ compiler.

(i will add other OS later)





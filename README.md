# Digital Clock

A digital clock built with C and raylib, displaying the current local time using 7-segment display style rendering.

## Dependencies
- [raylib](https://github.com/raysan5/raylib)
- X11 (on Linux)

## Building

```bash
gcc clock.c -lraylib -lX11 -lm -o clock
```

## Running

```bash
./clock
```

## Installation (raylib)

```bash
git clone https://github.com/raysan5/raylib
cd raylib
cmake -B build .
cd build
sudo make
sudo make install
```

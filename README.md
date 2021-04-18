# Computer Animation and Special Effects HW1

## Prerequisite

- [Cmake](https://cmake.org) (version >= 3.16)
- git
- git-lfs
- Compiler (e.g. GCC)

## Instruction

- Run:
```bash=
git clone https://github.com/TheLurkingCat/soft-body-simulation.git
git submodule init
git submodule update --remote
cmake -S . -B build
cmake --build build --config Release --parallel 8
```
- Executable will be in ./bin

## If you are building on Linux, you need one of these dependencies, usually `xorg-dev`

- `xorg-dev` (For X11)
- `libwayland-dev wayland-protocols extra-cmake-modules libxkbcommon-dev` (For Wayland)
- `libosmesa6-dev` (For OSMesa)

# Lodge - A fast multithreaded logging library 

Small concurrent logging library with capability for multiple writer threads. Makes use of various c++20 features including:
  - std::jthread
  - std::stop_token/stop_source
  - constraining templates via concepts
  - + more

## Dependencies
fmt - A modern formatting library: https://github.com/fmtlib/fmt  
gtest - A testing framework provided by Google: https://github.com/google/googletest

## Building  
This repository contains both Meson and CMake build scripts to allow for easy attachment to projects utilizing one or the other.  

### Getting the source
To download this repository and get ready for build process:
1. git clone https://github.com/Rasmus20B/lodge
2. cd lodge
3. mkdir build && cd build
### Meson
To build with Meson:
1. meson ..
2. meson compile
### CMake
To build with CMake:
1. cmake ..
2. cmake --build .

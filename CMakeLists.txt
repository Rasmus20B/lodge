cmake_minimum_required(VERSION 3.13)  # CMake version check
project(lodge)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 20 )            # Enable c++14 standard
set(CXX_STANDARD_REQUIRED YES)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES src/lodge.h src/levels.h src/log_item.h src/queue.h
  src/sinks.h src/lodge.cc src/sinks.cc)

# Add executable target with source files listed in SOURCE_FILES variable
include(FetchContent)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  )
set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(fmt)

add_library(lodge ${SOURCE_FILES})
target_link_libraries(lodge fmt)

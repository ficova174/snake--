cmake_minimum_required(VERSION 3.16)
project(snake++ LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the include directory for header files
include_directories(include)

set(SOURCES src/main.cpp src/constants.h)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

add_executable(snake++ ${SOURCES})

target_link_libraries(snake++ PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)

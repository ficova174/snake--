cmake_minimum_required(VERSION 3.16)
project(Snake++ LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic -Wshadow -g -O2")

# Add the include directory for header files
include_directories(include)

set(SOURCES src/main.cpp src/game.cpp src/viewport.cpp src/snake.cpp)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

add_executable(Snake++ ${SOURCES})

target_link_libraries(Snake++ PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)

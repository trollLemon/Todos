
cmake_minimum_required(VERSION 3.10)

# set the project name
project(tdl VERSION 1.0)



set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(tdl src/main.cpp src/file.cpp src/run.cpp src/taskwindow.cpp)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(tdl ${CURSES_LIBRARIES})

find_package(yaml-cpp REQUIRED)
include_directories(${YAML_INCLUDE_DIR})
target_link_libraries(tdl ${YAML_CPP_LIBRARIES})

install(TARGETS tdl )

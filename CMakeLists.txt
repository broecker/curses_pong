cmake_minimum_required(VERSION 2.8.9) project(salvo_curses)

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIRS})

add_executable(salvo_curses main.cpp)
target_link_libraries(salvo_curses ${CURSES_LIBRARIES})
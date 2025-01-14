cmake_minimum_required(VERSION 3.14)

project(GraphicsStudy)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.c*)


add_executable(game ${SOURCES})
target_include_directories(game PRIVATE ${SDL2_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(game ${SDL2_LIBRARIES})
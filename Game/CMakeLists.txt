cmake_minimum_required(VERSION 3.14)

project(Game)

set(CMAKE_CXX_STANDARD 17)

file(GLOB GAME_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c*)

add_executable(Game ${GAME_SOURCES})

target_include_directories(Game PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/Engine/src
)

target_link_libraries(Game PRIVATE Engine)

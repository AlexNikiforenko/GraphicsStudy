cmake_minimum_required(VERSION 3.14)

project(GraphicsStudy)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_IMAGE_INCLUDE_DIRS "/Library/Frameworks/SDL2_image.framework/Headers")
set(SDL2_IMAGE_LIBRARIES "/Library/Frameworks/SDL2_image.framework/SDL2_image")

find_package(SDL2 REQUIRED)
# find_package(SDL2_image REQUIRED) # doesn't work, I need to fiqure it out

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.c*)

add_executable(game ${SOURCES})

target_include_directories(game PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(game ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
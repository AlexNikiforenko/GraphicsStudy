project(ZombieGame)

set(CMAKE_CXX_STANDARD 17)

file(GLOB GAME_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c*)

add_executable(ZombieGame ${GAME_SOURCES})

target_include_directories(ZombieGame PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/Engine/src
)

target_link_libraries(ZombieGame PRIVATE Engine)
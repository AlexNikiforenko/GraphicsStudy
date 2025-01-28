project(Engine)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_IMAGE_INCLUDE_DIRS "/Library/Frameworks/SDL2_image.framework/Headers")
set(SDL2_IMAGE_LIBRARIES "/Library/Frameworks/SDL2_image.framework/SDL2_image")

find_package(SDL2 REQUIRED)

file(GLOB ENGINE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/Engine/*.c*)

add_library(Engine STATIC ${ENGINE_SOURCES})

target_include_directories(Engine PUBLIC
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Engine PUBLIC ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

cmake_minimum_required(VERSION 3.9)
project(magic_music_memory C)

set(RAYLIB_INSTALL_DIR "Raylib install dir not found!" CACHE STRING "Install directory of raylib")
list(APPEND CMAKE_PREFIX_PATH "${RAYLIB_INSTALL_DIR}")

find_package(raylib 4.0 REQUIRED)

add_executable(music
    src/main.c
    src/music.c
    src/card.c
    src/game.c
    src/background.c
)

target_include_directories(music PRIVATE src)
target_link_libraries(music raylib)
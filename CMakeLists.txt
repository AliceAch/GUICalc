cmake_minimum_required(VERSION 3.18)

project(calc
    LANGUAGES CXX
    VERSION 1.0
    )

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(USE_SYSTEM_SDL "Build using system SDL library" OFF)

if(USE_SYSTEM_SDL)
    # try to find sdl in system libraries
    find_package(SDL REQUIRED)
    find_package(SDL_ttf REQUIRED)
    find_package(SDL_image REQUIRED)
else()
    add_subdirectory(deps)
endif()


add_subdirectory(src)
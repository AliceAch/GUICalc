add_library(calc STATIC)

set(SDL2_INCLUDE_DIRS   "${CMAKE_CURRENT_SOURCE_DIR}/deps/SDL/include")

set(SDL2_IMAGE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/deps/SDL_image/include")

target_include_directories(calc
    PUBLIC
        ${calc_SOURCE_DIR}/src/include
)

target_link_libraries(calc 
    PUBLIC 
        SDL2::SDL2main
    PUBLIC
        SDL2::SDL2
    PUBLIC
        SDL2_image::SDL2_image
    PUBLIC 
        SDL2_ttf::SDL2_ttf
)

target_sources(calc
    PUBLIC
        Texture.cpp    
        Scanner.cpp
        Parser.cpp
        Interpreter.cpp
        Token.cpp
        GUI.cpp
        Button.cpp
        Screen.cpp
)

add_executable(calc_main)
set_target_properties(calc_main PROPERTIES OUTPUT_NAME "calculator")

target_sources(calc_main
    PRIVATE
        main.cpp
)
target_link_libraries(calc_main PRIVATE calc)

message("build directory: ${CMAKE_BINARY_DIR}")
if (MSVC)
    add_custom_command(TARGET calc POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_BINARY_DIR}/deps/SDL/SDL2.dll"
            $<TARGET_FILE_DIR:calc>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_BINARY_DIR}/deps/SDL_image/SDL2_image.dll"
            $<TARGET_FILE_DIR:calc>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_BINARY_DIR}/deps/SDL_ttf/SDL2_ttf.dll"
            $<TARGET_FILE_DIR:calc>
        )
endif()
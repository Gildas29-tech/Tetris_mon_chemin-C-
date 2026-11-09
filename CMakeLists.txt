cmake_minimum_required(VERSION 3.16)
project(Tetris VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    find_package(SFML 2.6 COMPONENTS graphics window system audio REQUIRED
        PATHS "C:/SFML" "C:/vcpkg/installed/x64-windows"
        NO_DEFAULT_PATH
    )
else()
    find_package(SFML 2.6 COMPONENTS graphics window system audio REQUIRED)
endif()

add_executable(Tetris
    src/main.cpp
    src/Jeu.cpp
    src/Grille.cpp
    src/Tetromino.cpp
    src/GestionnaireEntrees.cpp
    src/Rendu.cpp
    src/GestionnaireScore.cpp
    src/GestionnaireSon.cpp
)

target_link_libraries(Tetris PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)

target_include_directories(Tetris PRIVATE src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(Tetris PRIVATE -Wall -Wextra -Wpedantic)
elseif(MSVC)
    target_compile_options(Tetris PRIVATE /W4 /permissive-)
endif()
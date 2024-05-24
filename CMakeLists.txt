cmake_minimum_required(VERSION 3.16)

project(font_checker
        VERSION 0.1
        LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_subdirectory("../flint_gui" flint_gui)

add_executable(font_checker "src/main.cpp")

target_include_directories(font_checker PUBLIC "../flint_gui/src")

target_link_libraries(font_checker PUBLIC flint_gui)

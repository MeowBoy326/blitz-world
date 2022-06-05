
cmake_minimum_required(VERSION 3.8)

project(glwindow)

add_library(glwindow
	gamepad.cpp
	gamepad.h
	gamepadmapping.cpp
	gamepadmapping.h
    glwindow.cpp
    glwindow.h
    imguiex.cpp
    imguiex.h
    keyboard.cpp
    keyboard.h
    uidevice.cpp
    uidevice.h
    gamepadmappings.inc
)

target_link_libraries(glwindow imgui glfw gles geom core)

add_executable(helloworld tests/helloworld.cpp)

target_link_libraries(helloworld glwindow)

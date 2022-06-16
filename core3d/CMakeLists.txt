
cmake_minimum_required(VERSION 3.8)

##### core3d module #####

project(core3d)

add_library(core3d
        core3d.cpp
        core3d.hh
        types.cpp
        types.h
        glgraphicsdevice.cpp
        glgraphicsdevice.h
        gltypes.cpp
        gltypes.h
        graphicsdevice.cpp
        graphicsdevice.h
        )

target_link_libraries(core3d stb geom core)

##### core3d tests #####

add_executable(helloquad
        tests/hellotriangle.cpp)

target_link_libraries(helloquad core3d glwindow)

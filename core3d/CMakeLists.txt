
cmake_minimum_required(VERSION 3.8)

project(core3d)

add_library(core3d
	core3d.cpp
	core3d.hh
    formats.cpp
    formats.h
    framebuffer.cpp
    framebuffer.h
    glgraphicsdevice.cpp
    glgraphicsdevice.h
    glutils.cpp
    glutils.h
	graphicsdevice.cpp
	graphicsdevice.h
    indexbuffer.cpp
    indexbuffer.h
	shader.cpp
	shader.h
	texture.cpp
	texture.h
    vertexbuffer.cpp
    vertexbuffer.h
)

target_link_libraries(core3d geom stb core)

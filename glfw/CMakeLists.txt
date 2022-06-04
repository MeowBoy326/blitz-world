cmake_minimum_required(VERSION 3.8)

##### glfw #####

project(glfw)

add_library(glfw INTERFACE
    glfw-checkout/include/GLFW/glfw3.h
    glfw-checkout/src/internal.h
    )

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Emscripten")

    target_link_options(glfw INTERFACE "SHELL:-s MIN_WEBGL_VERSION=2")
    target_link_options(glfw INTERFACE "SHELL:-s MAX_WEBGL_VERSION=2")
    target_link_options(glfw INTERFACE "SHELL:-s USE_WEBGL2=1")
    target_link_options(glfw INTERFACE "SHELL:-s USE_GLFW=3")
    
else()

    find_package(OpenGLES REQUIRED)

    target_include_directories(glfw INTERFACE
        "${PROJECT_SOURCE_DIR}/glfw-checkout/include"
    )

    target_link_libraries(glfw INTERFACE
        "${PROJECT_SOURCE_DIR}/glfw-build/release/src/libglfw3.a"
		${OPENGLES_LIBRARY}
        X11
    )

endif()


cmake_minimum_required(VERSION 3.8)

##### glfw #####

project(glfw)

add_library(glfw INTERFACE
    glfw-checkout/include/GLFW/glfw3.h
    glfw-checkout/src/internal.h
    )

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Emscripten")

    target_link_options(glfw INTERFACE "SHELL:-s USE_GLFW=3")

    target_link_libraries(glfw INTERFACE gles)
    
else()

    target_include_directories(glfw INTERFACE
        "${PROJECT_SOURCE_DIR}/glfw-checkout/include"
    )

    if(WIN32)
        target_link_libraries(glfw INTERFACE
            "${PROJECT_SOURCE_DIR}/glfw-build/release/src/Release/glfw3.lib"
            gles
        )
    else()
        target_link_libraries(glfw INTERFACE
            "${PROJECT_SOURCE_DIR}/glfw-build/release/src/libglfw3.a"
            gles
        )
    endif()

endif()

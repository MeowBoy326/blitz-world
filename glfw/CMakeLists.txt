cmake_minimum_required(VERSION 3.8)

##### glfw module #####

project(glfw)

add_library(glfw INTERFACE
)

target_compile_definitions(glfw INTERFACE GLFW_INCLUDE_NONE)

if(EMSCRIPTEN)

    target_link_options(glfw INTERFACE "SHELL:-s USE_GLFW=3")

    target_link_libraries(glfw INTERFACE opengl)

elseif(WINDOWS)

    target_include_directories(glfw INTERFACE
		"${PROJECT_SOURCE_DIR}/libglfw/include"
	)
    target_link_libraries(glfw INTERFACE
		"${PROJECT_SOURCE_DIR}/libglfw/windows_x64/lib/glfw3.lib"
		opengl
	)
else()

    find_package(GLFW3 REQUIRED)

    target_include_directories(glfw INTERFACE
        "${GLFW3_INCLUDE_DIR}"
    )
    target_link_libraries(glfw INTERFACE
        "${GLFW3_LIBRARY}"
		opengl
        X11
    )

endif()

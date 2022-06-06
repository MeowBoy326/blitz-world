cmake_minimum_required(VERSION 3.8)

##### glfw module #####

project(glfw)

add_library(glfw INTERFACE
)

if(EMSCRIPTEN)

    target_link_options(glfw INTERFACE "SHELL:-s USE_GLFW=3")

    target_link_libraries(glfw INTERFACE gles)
    
elseif(WINDOWS)

    target_include_directories(glfw INTERFACE
		"${PROJECT_SOURCE_DIR}/libglfw3/include"
	)
    target_link_libraries(glfw INTERFACE
		"${PROJECT_SOURCE_DIR}/libglfw3/windows_x64/lib/glfw3.lib"
		gles
	)
	
elseif(LINUX)

    find_package(GLFW3 REQUIRED)

    target_include_directories(glfw INTERFACE
        "${GLFW3_INCLUDE_DIR}"
    )
    target_link_libraries(glfw INTERFACE
        "${GLFW3_LIBRARY}"
        X11
    )

endif()

cmake_minimum_required(VERSION 3.8)

##### glfw #####

project(glfw)

add_library(glfw INTERFACE
)

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Emscripten")

    target_link_options(glfw INTERFACE "SHELL:-s USE_GLFW=3")

    target_link_libraries(glfw INTERFACE gles)
    
elseif(WIN32)

	target_include_directories(glfw INTERFACE
		"${PROJECT_SOURCE_DIR}/libglfw3/include"
	)
	target_link_libraries(glfw INTERFACE
		"${PROJECT_SOURCE_DIR}/libglfw3/windows_x64/lib/glfw3.lib"
		gles
	)
	
else()

	find_package(glfw3 REQUIRED)

	target_include_directories(glfw INTERFACE
		"${GLFW3_INCLUDE_DIR}"
	)
	target_link_libraries(glfw INTERFACE
		"${GLFW3_LIBRARY}"
		gles
	)
endif()

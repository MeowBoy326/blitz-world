cmake_minimum_required(VERSION 3.8)

##### gles #####

project(gles)

add_library(gles INTERFACE)

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Emscripten")

    target_link_options(gles INTERFACE "SHELL:-s MIN_WEBGL_VERSION=2")
    target_link_options(gles INTERFACE "SHELL:-s MAX_WEBGL_VERSION=2")
    target_link_options(gles INTERFACE "SHELL:-s USE_WEBGL2=1")
    
elseif(WIN32)

	target_include_directories(gles INTERFACE
		"${PROJECT_SOURCE_DIR}/include"
	)
	target_link_libraries(gles INTERFACE
		"${PROJECT_SOURCE_DIR}/angle/lib/x64/libEGL.dll.lib"
		"${PROJECT_SOURCE_DIR}/angle/lib/x64/libGLESv2.dll.lib"
	)
	
else()

	find_package(OpenGLES REQUIRED)

	target_link_libraries(gles INTERFACE
		${OPENGLES_LIBRARY}
		X11
	)
endif()

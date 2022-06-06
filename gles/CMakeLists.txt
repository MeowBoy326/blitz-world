cmake_minimum_required(VERSION 3.8)

##### gles module #####

project(gles)

add_library(gles INTERFACE)

if(EMSCRIPTEN)

    target_link_options(gles INTERFACE "SHELL:-s MIN_WEBGL_VERSION=2")
    target_link_options(gles INTERFACE "SHELL:-s MAX_WEBGL_VERSION=2")
    target_link_options(gles INTERFACE "SHELL:-s USE_WEBGL2=1")
    
elseif(WINDOWS)

	target_include_directories(gles INTERFACE
		"${PROJECT_SOURCE_DIR}/libangle/include"
	)
	target_link_libraries(gles INTERFACE
		"${PROJECT_SOURCE_DIR}/libangle/windows_x64/lib/libEGL.dll.lib"
		"${PROJECT_SOURCE_DIR}/libangle/windows_x64/lib/libGLESv2.dll.lib"
	)
	
elseif(LINUX)

	find_package(OpenGLES REQUIRED)

    target_include_directories(gles INTERFACE
        "${OPENGLES_INCLUDE_DIR}"
    )
    target_link_libraries(gles INTERFACE
        "${OPENGLES_LIBRARY}"
        X11
    )

endif()

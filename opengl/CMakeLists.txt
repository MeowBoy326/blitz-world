cmake_minimum_required(VERSION 3.8)

##### opengl module #####

project(opengl)

if(EMSCRIPTEN AND NOT USE_OPENGLES)
	message(FATAL_ERROR "Emscripten builds must use OpenGLES")
endif()

set(SOURCES opengl.cpp opengl.hh)

if(WINDOWS AND NOT USE_OPENGLES)
	set(SOURCES ${SOURCES} "libglew/src/glew.c")
endif()

add_library(opengl ${SOURCES})

if(EMSCRIPTEN)

    target_link_options(opengl PUBLIC "SHELL:-s MIN_WEBGL_VERSION=2")
    target_link_options(opengl PUBLIC "SHELL:-s MAX_WEBGL_VERSION=2")
    target_link_options(opengl PUBLIC "SHELL:-s USE_WEBGL2=1")
	
elseif(WINDOWS AND USE_OPENGLES)

	target_include_directories(opengl INTERFACE
		"${PROJECT_SOURCE_DIR}/libangle/include"
	)
	target_link_libraries(opengl INTERFACE
		"${PROJECT_SOURCE_DIR}/libangle/windows_x64/lib/libEGL.dll.lib"
		"${PROJECT_SOURCE_DIR}/libangle/windows_x64/lib/libGLESv2.dll.lib"
	)

elseif(WINDOWS)

	target_compile_definitions(opengl PUBLIC GLEW_STATIC)

	target_include_directories(opengl PUBLIC
		"${PROJECT_SOURCE_DIR}/libglew/include"
	)

	target_link_libraries(opengl PUBLIC opengl32)

elseif(USE_OPENGLES)

	find_package(OpenGLES REQUIRED)

    target_include_directories(opengl INTERFACE
        "${OPENGLES_INCLUDE_DIR}"
    )
    target_link_libraries(opengl INTERFACE
        "${OPENGLES_LIBRARY}"
    )

else()

	find_package(OpenGL REQUIRED)

	target_include_directories(opengl INTERFACE
        "${OPENGL_INCLUDE_DIR}"
    )
    target_link_libraries(opengl INTERFACE
        "${OPENGL_LIBRARY}"
    )

endif()

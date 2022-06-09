cmake_minimum_required(VERSION 3.8)

##### openxr module #####

project(openxr)

add_library(openxr INTERFACE)

if(EMSCRIPTEN)

	message(FATAL_ERROR "OpenXR not supported on emscripten yet")
    
elseif(WINDOWS)

    target_include_directories(openxr INTERFACE
		"${PROJECT_SOURCE_DIR}/libopenxr/include"
	)
    target_link_libraries(openxr INTERFACE
		"${PROJECT_SOURCE_DIR}/libopenxr/windows_x64/lib/openxr_loader.lib"
	)
	
else()

    find_package(OpenXR REQUIRED)

    target_include_directories(openxr INTERFACE
        "${OpenXR_INCLUDE_DIR}"
    )
    target_link_libraries(openxr INTERFACE
        "${OpenXR_LIBRARY}"
    )

endif()

##### openxr tests #####

add_executable(compiletest
	tests/compiletest.cpp
)
target_link_libraries(compiletest openxr)

add_executable(createinstance
	"tests/createinstance.cpp"
)
target_link_libraries(createinstance openxr core)

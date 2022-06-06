
cmake_minimum_required(VERSION 3.8)

project(audio)

add_library(audio
        audio.cpp
        audio.h
        dr_wav.h
)

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Emscripten")

    target_link_libraries(audio PUBLIC -lopenal)

elseif(WIN32)

	target_include_directories(audio PUBLIC
		"${PROJECT_SOURCE_DIR}/libopenal/include"
	)
    target_link_libraries(audio PUBLIC
        "${PROJECT_SOURCE_DIR}/libopenal/windows_x64/lib/OpenAL32.lib"
    )
	
else()

	find_package(OpenAL REQUIRED)
	
	target_include_directories(audio PUBLIC
		"${OPENAL_INCLUDE_DIR}"
	)
	target_link_libraries(audio PUBLIC
		"${OPENAL_LIBRARY}"
		core
	)
endif()

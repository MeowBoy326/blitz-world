# To configure for WebAssembly in a build subdir:
#
# cmake -DCMAKE_TOOLCHAIN_FILE=CMake/Emscripten.cmake -DCMAKE_BUILD_TYPE=Release -GNinja ..
#
# Note: EMSCRIPTEN env var must be set to eg: $HOME/dev/emsdk/upstream/emscripten for toolchain file to work.
#
# To build in build subdir:
#
# cmake --build .

cmake_minimum_required(VERSION 3.8)

project(blitz-world)

#set(CMAKE_VERBOSE_MAKEFILE ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

message("Configuring cmake for CMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME} and CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake ${CMAKE_MODULE_PATH})

set(CMAKE_CXX_STANDARD 17)
    add_compile_options()

if(WIN32)

    add_compile_options(/GR- /EHs- /EHc- /D_HAS_EXCEPTIONS=0)
else()
    add_compile_options(-fno-rtti -fno-exceptions)
    add_link_options(-fno-rtti -fno-exceptions)
endif()

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Emscripten")
#	add_compile_options(-Os)
#	add_link_options(-Os)
    add_compile_options(-g3)
    add_link_options(-g3)
endif()

# Enable sanitizers for debug builds only.
# Not supported in "RelWithDebInfo" mode as it seems to break the profiler.
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    if(WIN32)
    else()
        set(SANITIZER_OPTIONS -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer)
        message("SANITIZER_OPTIONS=${SANITIZER_OPTIONS}")
        add_compile_options(${SANITIZER_OPTIONS})
        add_link_options(${SANITIZER_OPTIONS})
     endif()
endif()

include_directories(${CMAKE_SOURCE_DIR})

# Al-pha-be-tic-ally!
add_subdirectory(audio)
add_subdirectory(core)
add_subdirectory(geom)
add_subdirectory(gles)
add_subdirectory(glfw)
add_subdirectory(glwindow)
add_subdirectory(image)
add_subdirectory(imgui)

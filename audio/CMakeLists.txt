
cmake_minimum_required(VERSION 3.8)

project(audio)

add_library(audio
        audio.cpp
        audio.h
        dr_wav.h
)

target_link_libraries(audio core)

find_package(OpenAL REQUIRED)
target_link_libraries(audio ${OPENAL_LIBRARY})

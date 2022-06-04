
cmake_minimum_required(VERSION 3.8)

project(core)

add_library(core
    appevent.cpp
    appevent.h
	core.cpp
	core.h
	debug.cpp
	debug.h
    function.cpp
    function.h
    object.cpp
    object.h
    podvector.cpp
    podvector.h
    property.cpp
    property.h
    shared.cpp
	shared.h
    sharedptr.cpp
    sharedptr.h
	signal.cpp
	signal.h
    signal_impl.inl
	std.cpp
	std.h
    weakptr.cpp
    weakptr.h
)

add_executable(core_tests
    tests/signal.cpp
)

target_link_libraries(core_tests PRIVATE core)

add_test(NAME core_tests COMMAND core_tests)

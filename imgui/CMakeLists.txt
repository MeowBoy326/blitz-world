
cmake_minimum_required(VERSION 3.8)

project(imgui)

set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/imgui-checkout")

add_library(imgui
    "${SOURCE_DIR}/imgui.cpp"
    "${SOURCE_DIR}/imgui.h"
    "${SOURCE_DIR}/imgui_demo.cpp"
    "${SOURCE_DIR}/imgui_draw.cpp"
    "${SOURCE_DIR}/imgui_tables.cpp"
    "${SOURCE_DIR}/imgui_widgets.cpp"
    "${SOURCE_DIR}/imconfig.h"
    "${SOURCE_DIR}/imgui_internal.h"
    "${SOURCE_DIR}/imstb_rectpack.h"
    "${SOURCE_DIR}/imstb_textedit.h"
    "${SOURCE_DIR}/backends/imgui_impl_opengl3.cpp"
    "${SOURCE_DIR}/backends/imgui_impl_opengl3.h"
    "${SOURCE_DIR}/backends/imgui_impl_glfw.cpp"
    "${SOURCE_DIR}/backends/imgui_impl_glfw.h"
    "ImGuiFileDialog-checkout/ImGuiFileDialog.cpp"
    "ImGuiFileDialog-checkout/ImGuiFileDialog.h"
    "imgui.cpp"
    "imgui.hh"
    "imguiex.cpp"
    "imguiex.h"
)

add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_CUSTOM=<GLFW/glfw3.h>)
add_compile_definitions(IMGUI_IMPL_OPENGL_ES3=1)

target_include_directories(imgui PUBLIC
    "${SOURCE_DIR}"
)

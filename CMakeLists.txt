cmake_minimum_required(VERSION 3.13)
project(vulkan_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        ${PROJECT_SOURCE_DIR}/vendor/vulkan/Include
)

set(
        LIBS
        ${PROJECT_SOURCE_DIR}/vendor/vulkan/Lib/vulkan-1.lib
)

add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
add_executable(vulkan_1 main.cpp src/core/vulkan_core.cpp src/core/vulkan_core.h src/core/macro.h)

target_link_libraries(vulkan_1 ${LIBS})


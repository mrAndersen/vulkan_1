cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 14)
project(vulkan_1)

#find opengl in system
find_package(OpenGL REQUIRED)

# find vulkan in system
find_package(Vulkan REQUIRED)
if (${Vulkan_FOUND})
    message(STATUS "Vulkan FOUND")
    message(STATUS "Vulkan Include in ${Vulkan_INCLUDE_DIRS}")
    message(STATUS "Vulkan Lib in ${Vulkan_LIBRARIES}")
endif ()

# build gflw from soubmodules
add_subdirectory(vendor/glfw)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)


#includes
include_directories(
        ${Vulkan_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIR}
        vendor/glfw/include
)

set(
        LIBS
        ${Vulkan_LIBRARIES}
        glfw
        ${OPENGL_gl_LIBRARY}
        ${OPENGL_glu_LIBRARY}
)

add_compile_definitions(_CRT_SECURE_NO_WARNINGS)


add_executable(vulkan_1 main.cpp src/core/vulkan_init.cpp src/core/vulkan_init.h src/core/macro.h)

target_include_directories(vulkan_1 PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(vulkan_1 ${LIBS})
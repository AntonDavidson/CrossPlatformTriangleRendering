# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.4.1)

# Project name
project("crossplatformtrianglerendering")

# Explicitly reference the full path for each source file
add_library(main_lib SHARED ${CMAKE_SOURCE_DIR}/main_lib.cpp)
add_library(opengl_utils SHARED ${CMAKE_SOURCE_DIR}/opengl_utils.cpp)
add_library(opengl_shader SHARED ${CMAKE_SOURCE_DIR}/opengl_shader.cpp)

# Include directories for the libraries (current directory)
target_include_directories(main_lib PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(opengl_utils PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(opengl_shader PRIVATE ${CMAKE_SOURCE_DIR})

# Find the GLESv3 library for OpenGL on Android and the log library for logging
find_library(GLES_LIBRARY GLESv3)
find_library(LOG_LIBRARY log)

# Link the GLESv3 and log libraries to each target
target_link_libraries(main_lib PRIVATE ${GLES_LIBRARY} ${LOG_LIBRARY})
target_link_libraries(opengl_utils PRIVATE ${GLES_LIBRARY} ${LOG_LIBRARY})
target_link_libraries(opengl_shader PRIVATE ${GLES_LIBRARY} ${LOG_LIBRARY})

# Make sure the OpenGL main depends on shader and utils libraries
target_link_libraries(main_lib PRIVATE opengl_utils opengl_shader)

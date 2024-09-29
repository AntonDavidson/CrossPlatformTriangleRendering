# Minimum version of CMake required
cmake_minimum_required(VERSION 3.4.1)
project("crossplatformtrianglerendering")

# Add the main native library
add_library(native-lib SHARED native-lib.cpp)

# Include directories for the libraries
target_include_directories(native-lib PRIVATE .)  # Include the current directory

    # Add the native OpenGL library for Android
    add_library(OpenGl SHARED OpenGl.cpp)

    # Find and link GLES library for Android
    find_library(GLES_LIBRARY GLESv3)
    target_link_libraries(OpenGl PRIVATE ${GLES_LIBRARY} log)  # Link against the log library

    target_link_libraries(native-lib PRIVATE ${GLES_LIBRARY} log)  # Link log to native-lib


#ifndef MAIN_LIB_H
#define MAIN_LIB_H

#ifdef __APPLE__

/**
 * @brief Initializes the Metal context and other Metal-specific resources.
 */
void initMetalApp();

/**
 * @brief Renders using Metal.
 */
void renderMetalApp();

#elif defined(ANDROID)

/**
 * @brief Initializes the OpenGL context and other OpenGL-specific resources.
 */
void initOpenGLApp();

/**
 * @brief Renders using OpenGL.
 */
void renderOpenGLApp();

#endif

#endif 
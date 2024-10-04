

#ifndef OPENGL_UTILS_H
#define OPENGL_UTILS_H
#include <GLES3/gl3.h>

/**
 * @brief Sets up a triangle's vertex buffer and vertex array object (VAO) for rendering.
 *
 * @param vao Reference to the VAO that will be created.
 */
void setupTriangle(GLuint& vao);
#endif
#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include <GLES3/gl3.h>

/**
 * @brief Loads and compiles vertex and fragment shaders, and links them into a shader program.
 *
 * @param vertexSource The source code of the vertex shader.
 * @param fragmentSource The source code of the fragment shader.
 * @return GLuint The ID of the compiled and linked shader program.
 */
GLuint loadShaderProgram(const char* vertexSource, const char* fragmentSource);

#endif // OPENGL_SHADER_H

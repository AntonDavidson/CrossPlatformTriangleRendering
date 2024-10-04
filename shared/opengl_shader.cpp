#ifdef ANDROID

#include "opengl_shader.h"
#include <android/log.h>
#include <GLES3/gl3.h>
// Define a tag for logging shader compilation and linking info to Android's logcat
#define LOG_TAG "ShaderLog"
#define LOG_INFO(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

/**
 * @brief Checks the compilation status of a shader.
 *
 * This function retrieves the compilation status of the given shader. If there
 * is a compilation error, it retrieves the error log and outputs it to Android's
 * logcat for debugging purposes.
 *
 * @param shader The shader ID to be checked.
 */
void checkShader(GLuint shader) {
    GLint success;
    GLchar infoLog[512]; // Buffer for the error message

    // Check the compile status of the shader
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        // Retrieve and log the error message if compilation failed
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        LOG_INFO("Shader compilation error: %s", infoLog);
    }
}

/**
 * @brief Checks the linking status of a shader program.
 *
 * This function retrieves the linking status of the given shader program. If there
 * is a linking error, it retrieves the error log and outputs it to Android's
 * logcat for debugging purposes.
 *
 * @param program The shader program ID to be checked.
 */
void checkProgram(GLuint program) {
    GLint success;
    GLchar infoLog[512]; // Buffer for the error message

    // Check the link status of the shader program
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        // Retrieve and log the error message if linking failed
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        LOG_INFO("Program linking error: %s", infoLog);
    }
}

/**
 * @brief Compiles and links a vertex and fragment shader into a shader program.
 *
 * This function takes in the source code for a vertex shader and a fragment shader,
 * compiles them, and links them into a shader program. It checks for compilation and
 * linking errors and returns the ID of the linked shader program.
 *
 * @param vertexSource The source code of the vertex shader.
 * @param fragmentSource The source code of the fragment shader.
 * @return GLuint The ID of the compiled and linked shader program.
 */
GLuint loadShaderProgram(const char *vertexSource, const char *fragmentSource) {
    // Compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);
    checkShader(vertexShader); // Check for vertex shader compilation errors

    // Compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);
    checkShader(fragmentShader); // Check for fragment shader compilation errors

    // Link the vertex and fragment shaders into a shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkProgram(shaderProgram); // Check for linking errors

    // Clean up shaders as they're no longer needed once linked
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram; // Return the linked shader program ID
}

#endif

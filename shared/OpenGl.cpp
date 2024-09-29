#include <jni.h>
#include <android/log.h>
#include <GLES3/gl3.h>

#define LOG_TAG "OpenGlLog"
#define LOG_INFO(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

// Vertex shader source code
const char* vertexShaderSource = R"(
    attribute vec4 position;  // Use attribute for vertex input
    void main() {
        gl_Position = position; // Pass the position to the GPU
    }
)";

// Fragment shader source code
const char* fragmentShaderSource = R"(
    precision mediump float;  // Define precision for float types
    void main() {
        gl_FragColor = vec4(1.0, 0.5, 0.2, 1.0); // Set the color to a shade of orange
    }
)";

GLuint shaderProgram;
GLuint vao;

void checkShader(GLuint shader) {
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        LOG_INFO("Shader compilation error: %s", infoLog);
    }
}

void checkProgram(GLuint program) {
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        LOG_INFO("Program linking error: %s", infoLog);
    }
}

void initShaders() {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    checkShader(vertexShader);  // Check for compilation errors

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    checkShader(fragmentShader);  // Check for compilation errors

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkProgram(shaderProgram);  // Check for linking errors

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void setupTriangle() {
    GLfloat vertices[] = {
            0.0f,  0.5f, 0.0f, // Vertex 1 (X, Y)
            -0.5f, -0.5f, 0.0f, // Vertex 2 (X, Y)
            0.5f, -0.5f, 0.0f   // Vertex 3 (X, Y)
    };

    GLuint vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}



void initOpenGL(){
    initShaders();  // Initialize shaders
    setupTriangle(); // Set up the triangle
}
void renderOpenGL(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Clear to black
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3); // Draw the triangle
    glBindVertexArray(0);
}



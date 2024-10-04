
#include "main_lib.h"




#ifdef __APPLE__
#define NS_PRIVATE_IMPLEMENTATION
#define UI_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MTK_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION

#include "metal_utills.h"
#include "metal_shader.h"
// Metal-specific functions for iOS

/**
 * @brief Initializes Metal on iOS.
 */


void setMTKView(void* view) {
    setMetalView(view);  // Cast the void* to MTK::View*
}
void initMetalApp() {
    initMetal();  // Calls the initMetal function from metal_utils.cpp
}

void renderMetalApp() {
    renderMetal();  // Calls the renderMetal function from metal_utils.cpp
}

#elif defined(ANDROID)

#include "opengl_utils.h"
#include "opengl_shader.h"
#include <jni.h>
#include <GLES3/gl3.h>
// OpenGL-specific variables for Android
GLuint shaderProgram;
GLuint vao;

/**
 * @brief Initializes OpenGL on Android.
 */
void initOpenGLApp() {
    // Vertex and fragment shader source codes for OpenGL
    const char* vertexShaderSource = R"(
        attribute vec4 position;
        void main() {
            gl_Position = position;
        }
    )";

    const char* fragmentShaderSource = R"(
        precision mediump float;
        void main() {
            gl_FragColor = vec4(1.0, 0.5, 0.2, 1.0);  // Set the color to orange
        }
    )";

    // Load shaders and create the shader program
    shaderProgram = loadShaderProgram(vertexShaderSource, fragmentShaderSource);

    // Set up the triangle's vertex buffer and VAO
    setupTriangle(vao);
}

/**
 * @brief Renders the triangle using OpenGL on Android.
 */
void renderOpenGLApp() {
    // Clear the screen to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Use the shader program and draw the triangle
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}
#endif

#ifdef ANDROID
// JNI Functions for Android
extern "C" JNIEXPORT void JNICALL
Java_com_aengineer_crossplatformtrianglerendering_NativeRenderer_initOpenGLApp(JNIEnv *env,jobject obj) {
initOpenGLApp();  // Initialize OpenGL for Android
}

extern "C" JNIEXPORT void JNICALL
Java_com_aengineer_crossplatformtrianglerendering_NativeRenderer_renderOpenGLApp(JNIEnv* env, jobject obj) {
renderOpenGLApp();  // Render using OpenGL for Android
}
#endif

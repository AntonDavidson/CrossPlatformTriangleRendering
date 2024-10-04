#ifndef MAIN_LIB_H
#define MAIN_LIB_H




#ifdef __APPLE__
/**
 * @brief Initializes the Metal context and other Metal-specific resources.
 */
#ifdef __cplusplus
extern "C" {
#endif

void setMTKView(void* view);
void initMetalApp(void);
void renderMetalApp(void);


#ifdef __cplusplus
}
#endif

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

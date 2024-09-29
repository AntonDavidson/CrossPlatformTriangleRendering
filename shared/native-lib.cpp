#include "native-lib.h"
#include "OpenGl.cpp"  // Include OpenGL for Android


#ifdef ANDROID
// JNI Functions for Android
extern "C" JNIEXPORT void JNICALL
Java_com_aengineer_crossplatformtrianglerendering_NativeRenderer_init(JNIEnv* env, jobject obj) {
    initOpenGL();
}

extern "C" JNIEXPORT void JNICALL
Java_com_aengineer_crossplatformtrianglerendering_NativeRenderer_render(JNIEnv* env, jobject obj) {
    renderOpenGL();
}
#endif
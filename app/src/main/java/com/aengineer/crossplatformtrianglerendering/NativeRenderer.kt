package com.aengineer.crossplatformtrianglerendering

import android.opengl.GLES10.glViewport
import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class NativeRenderer : GLSurfaceView.Renderer {
    // Native methods
    external fun init()
    external fun render()

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        // Initialize OpenGL ES
        init()
    }

    override fun onDrawFrame(gl: GL10) {
        // Render a frame
        render()
    }

    override fun onSurfaceChanged(gl: GL10, width: Int, height: Int) {
        // Handle surface size changes
        glViewport(0, 0, width, height)
    }

    companion object {
        init {
            System.loadLibrary("native-lib") // Load the native library
        }
    }
}
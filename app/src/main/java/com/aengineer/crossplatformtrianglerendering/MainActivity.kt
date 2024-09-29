package com.aengineer.crossplatformtrianglerendering

import android.app.Activity
import android.opengl.GLSurfaceView
import android.os.Bundle


class MainActivity : Activity() {
    private var glSurfaceView: GLSurfaceView? = null
    private var nativeRenderer: NativeRenderer? = null
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        // Initialize the GLSurfaceView and set the renderer
        glSurfaceView = GLSurfaceView(this)
        glSurfaceView!!.setEGLContextClientVersion(3) // OpenGL ES 3.0
        nativeRenderer = NativeRenderer()
        glSurfaceView!!.setRenderer(nativeRenderer)

        // Set the view as the content view
        setContentView(glSurfaceView)
    }

    override fun onPause() {
        super.onPause()
        glSurfaceView!!.onPause()
    }

    override fun onResume() {
        super.onResume()
        glSurfaceView!!.onResume()
    }
}
package com.doomgam.sonic4ep2;

import android.opengl.GLSurfaceView;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GameRenderer implements GLSurfaceView.Renderer {

    public native void nativeInitGL();
    public native void nativeResize(int width, int height);
    public native void nativeRenderFrame();

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        nativeInitGL();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        nativeResize(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        nativeRenderFrame();
    }
}

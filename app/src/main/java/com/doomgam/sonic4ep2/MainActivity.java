package com.doomgam.sonic4ep2;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;

public class MainActivity extends Activity {

    static {
        System.loadLibrary("sonic4ep2_loader");
    }

    private GLSurfaceView glSurfaceView;

    public native boolean initNativeEngine(String dataDirPath, String binaryPath);
    public native void sendTouchEvent(int id, float x, float y, int phase);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(
                WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN
        );

        String dataPath = getFilesDir().getAbsolutePath();
        String binaryPath = dataPath + "/Sonic4ep2";

        initNativeEngine(dataPath, binaryPath);

        glSurfaceView = new GLSurfaceView(this);
        glSurfaceView.setEGLContextClientVersion(2);
        glSurfaceView.setRenderer(new GameRenderer());

        glSurfaceView.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                int action = event.getActionMasked();
                int pointerIndex = event.getActionIndex();
                int pointerId = event.getPointerId(pointerIndex);

                float x = event.getX(pointerIndex);
                float y = event.getY(pointerIndex);

                int phase = 3;
                if (action == MotionEvent.ACTION_DOWN || action == MotionEvent.ACTION_POINTER_DOWN) {
                    phase = 0; // Touch Began
                } else if (action == MotionEvent.ACTION_MOVE) {
                    phase = 1; // Touch Moved
                } else if (action == MotionEvent.ACTION_UP || action == MotionEvent.ACTION_POINTER_UP) {
                    phase = 2; // Touch Ended
                }

                sendTouchEvent(pointerId, x, y, phase);
                return true;
            }
        });

        setContentView(glSurfaceView);
    }

    @Override
    protected void onResume() {
        super.onResume();
        if (glSurfaceView != null) glSurfaceView.onResume();
    }

    @Override
    protected void onPause() {
        super.onPause();
        if (glSurfaceView != null) glSurfaceView.onPause();
    }
}

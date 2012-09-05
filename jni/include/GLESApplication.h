#ifndef GLES_APPLICATION_H
#define GLES_APPLICATION_H

#include <android_native_app_glue.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <android/asset_manager.h>
#include <android/native_activity.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stack>
#include "Log.h"

using namespace std;

class GLESApplication
{

public:
        GLESApplication(android_app *context);
        virtual ~GLESApplication() {}

        int initWindow(android_app *app);
        virtual void terminateWindow(android_app *app) {}
        void tearDownEGLContext();
        virtual int32_t handleInput(struct android_app* app, AInputEvent* event);
        void handleCommand(struct android_app* app, int32_t cmd);
        double getCuttentTime();
        void run();
    
protected:
        virtual void saveState(android_app *app) {}
        virtual void gainedFocus(android_app *app) {}
        virtual void lostFocus(android_app *app) {}
        virtual void _drawOneFrame(double ellapsedTime);
        virtual void drawOneFrame(double ellapsedTime)  = 0;
        virtual void onStart(android_app* app) {}
        virtual void positInit(android_app *app) = 0;
        virtual void onPause(android_app *app) = 0;
        virtual void onResume(android_app *app) = 0;
        
        // Input handling
        virtual void onTouchDown(float x, float y) = 0;
        virtual void onTouchMove(float x, float y) = 0;
        virtual void onTouchUp(float x, float y) = 0;
        
    
protected:
        EGLDisplay display;
        EGLSurface surface;
        EGLContext context;
        android_app *androidContext;
        int screenWidth;
        int screenHeight;
};
#endif // GLES_APPLICATION_H

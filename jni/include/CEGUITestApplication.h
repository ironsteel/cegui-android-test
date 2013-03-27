#ifndef CEGUITESTAPPLICATION_H
#define CEGUITESTAPPLICATION_H

#include "GLESApplication.h"
#include "CEGUIAndroidLogger.h"
#include <stdlib.h>
#include <string.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/widgets/PushButton.h>
#include <CEGUI/RendererModules/OpenGLES/Renderer.h>
#include <CEGUI/FontManager.h>


class CEGUITestApplication : public GLESApplication
{
public:
    CEGUITestApplication(android_app *app) : GLESApplication(app) { LOGI("APPLICATION CREATED"); }
    ~CEGUITestApplication() { LOGI("APPLICATION DESTROYED");}
    
public:
	bool handle_ItemDropped(const CEGUI::EventArgs &args);
	void subscribeEvents();
	bool handle_CloseButton(const CEGUI::EventArgs &);
	
protected:
    void drawOneFrame(double ellapsedTime);
    void positInit(android_app *app);
    void terminateWindow(android_app *app);
    
    void onPause(android_app *app);
    void onResume(android_app *app);
    
    void onTouchDown(float x, float y);
    void onTouchMove(float x, float y);
    void onTouchUp(float x, float y);
    
    void initialiseResourceGroupDirectories();
    void initialiseDefaultResourceGroups();
    
    
};



#endif // CEGUITESTAPPLICATION_H

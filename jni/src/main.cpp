#include "CEGUITestApplication.h"

void android_main(struct android_app* state) 
{
    CEGUITestApplication app(state);
    app_dummy();
    app.run();
}

#include "CEGUITestApplication.h"
#include "AndroidResourceProvider.h"
void CEGUITestApplication::positInit(android_app *app)
{
    
    
    glViewport(0, 0, screenWidth, screenHeight);

    new AndroidLogger();
    CEGUI::OpenGLESRenderer::bootstrapSystem(new AndroidResourceProvider(app->activity->assetManager));
    
    initialiseResourceGroupDirectories();
    initialiseDefaultResourceGroups();

    CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
    CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
    CEGUI::WindowManager& winMgr(CEGUI::WindowManager::getSingleton());
    CEGUI::Window* root = winMgr.createWindow("DefaultWindow", "root");

    CEGUI::Window* fw = root->createChild("TaharezLook/FrameWindow");
    fw->setPosition(CEGUI::UVector2(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.25, 0)));
    fw->setSize(CEGUI::USize(CEGUI::UDim(0.5, 0), CEGUI::UDim(0.5, 0)));
    fw->setText("OpenGL ES 1 Tes1");
    CEGUI::PushButton* btn = static_cast<CEGUI::PushButton*>(winMgr.createWindow("TaharezLook/Button", "AddColButton"));
    fw->addChild(btn);
    btn->setPosition(CEGUI::UVector2(cegui_reldim(0.81f), cegui_reldim( 0.32f)));
    btn->setSize(CEGUI::USize(cegui_reldim(0.15f), cegui_reldim( 0.2f)));
    btn->setText("Push ME!");
    root->addChild(winMgr.loadLayoutFromFile("TabControlDemo.layout"));

    btn->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUITestApplication::buttonWasPushed, this)); 
    
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(root);
}

void CEGUITestApplication::drawOneFrame(double ellapsedTime) 
{  
    glClear(GL_COLOR_BUFFER_BIT);
    CEGUI::System::getSingleton().renderAllGUIContexts();
}

void CEGUITestApplication::terminateWindow(android_app *app)
{
    CEGUI::OpenGLESRenderer::destroySystem();
    delete AndroidLogger::getSingletonPtr();
}

void CEGUITestApplication::onPause(android_app *app)
{
}

void CEGUITestApplication::onResume(android_app *app)
{
}

void CEGUITestApplication::onTouchDown(float x, float y)
{
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMousePosition(x, y);
    CEGUI::MouseButton btn;
    btn = CEGUI::LeftButton;
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(btn);
}

void CEGUITestApplication::onTouchMove(float x, float y)
{
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMousePosition(x, y);
}

void CEGUITestApplication::onTouchUp(float x, float y)
{
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMousePosition(x, y);
    CEGUI::MouseButton btn;
    btn = CEGUI::LeftButton;
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(btn);
}

void CEGUITestApplication::initialiseResourceGroupDirectories()
{
    AndroidResourceProvider* rp =
        static_cast<AndroidResourceProvider*>
            (CEGUI::System::getSingleton().getResourceProvider());

    char resourcePath[PATH_MAX];

    // for each resource type, set a resource group directory
    sprintf(resourcePath, "%s", "schemes/");
    rp->setResourceGroupDirectory("schemes", resourcePath);
    sprintf(resourcePath, "%s", "imagesets/");
    rp->setResourceGroupDirectory("imagesets", resourcePath);
    sprintf(resourcePath, "%s", "fonts/");
    rp->setResourceGroupDirectory("fonts", resourcePath);
    sprintf(resourcePath, "%s", "layouts/");
    rp->setResourceGroupDirectory("layouts", resourcePath);
    sprintf(resourcePath, "%s", "looknfeel/");
    rp->setResourceGroupDirectory("looknfeels", resourcePath);
    sprintf(resourcePath, "%s", "lua_scripts/");
    rp->setResourceGroupDirectory("lua_scripts", resourcePath);
    sprintf(resourcePath, "%s", "xml_schemas/");
    rp->setResourceGroupDirectory("schemas", resourcePath);   
    sprintf(resourcePath, "%s", "animations/");
    rp->setResourceGroupDirectory("animations", resourcePath);   
}

void CEGUITestApplication::initialiseDefaultResourceGroups()
{
    // set the default resource groups to be used
    CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
    CEGUI::Font::setDefaultResourceGroup("fonts");
    CEGUI::Scheme::setDefaultResourceGroup("schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
    CEGUI::WindowManager::setDefaultResourceGroup("layouts");
    CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
    CEGUI::AnimationManager::setDefaultResourceGroup("animations");
    // setup default group for validation schemas
    CEGUI::XMLParser* parser = CEGUI::System::getSingleton().getXMLParser();
    if (parser->isPropertyPresent("SchemaDefaultResourceGroup"))
        parser->setProperty("SchemaDefaultResourceGroup", "schemas");
}

bool CEGUITestApplication::buttonWasPushed(const EventArgs &e)
{
    
}

#include "CEGUITestApplication.h"
#include "AndroidResourceProvider.h"

void CEGUITestApplication::positInit(android_app *app)
{
	glViewport(0, 0, screenWidth, screenHeight);
	
	new AndroidLogger();
	CEGUI::OpenGLESRenderer::bootstrapSystem(new AndroidResourceProvider(app->activity->assetManager));
	
	initialiseResourceGroupDirectories();
	initialiseDefaultResourceGroups();
	GUIContext* guiContext = &CEGUI::System::getSingleton().getDefaultGUIContext();
	
	
	// load windows look
	SchemeManager::getSingleton().createFromFile("WindowsLook.scheme");
	
	// load font and setup default if not loaded via scheme
	Font& defaultFont = FontManager::getSingleton().createFromFile("DejaVuSans-10.font");
	// Set default font for the gui context
	guiContext->setDefaultFont(&defaultFont);
	
	// set up defaults
	guiContext->getMouseCursor().setDefaultImage("WindowsLook/MouseArrow");
	
	// load the drive icons imageset
	ImageManager::getSingleton().loadImageset("DriveIcons.imageset");
	
	// load the initial layout
	guiContext->setRootWindow(
				WindowManager::getSingleton().loadLayoutFromFile("DragDropDemo.layout"));
	
	
	subscribeEvents();
}


void CEGUITestApplication::subscribeEvents()
{
	using namespace CEGUI;
	GUIContext* d_guiContext = &CEGUI::System::getSingleton().getDefaultGUIContext();
	Window* root = d_guiContext->getRootWindow();
	
	/*
	 * Subscribe handler to deal with user closing the frame window
	 */
	CEGUI_TRY
	{
		Window* main_wnd = root->getChild("MainWindow");
		main_wnd->subscribeEvent(
					FrameWindow::EventCloseClicked,
					Event::Subscriber(&CEGUITestApplication::handle_CloseButton, this));
	}
	// if something goes wrong, log the issue but do not bomb!
	CEGUI_CATCH(CEGUI::Exception&)
	{}
	
	/*
	 * Subscribe the same handler to each of the twelve slots
	 */
	String base_name = "MainWindow/Slot";
	
	for (int i = 1; i <= 12; ++i)
	{
		CEGUI_TRY
		{
			// get the window pointer for this slot
			Window* wnd =
					root->getChild(base_name + PropertyHelper<int>::toString(i));
			
			// subscribe the handler.
			wnd->subscribeEvent(
						Window::EventDragDropItemDropped,
						Event::Subscriber(&CEGUITestApplication::handle_ItemDropped, this));
		}
		// if something goes wrong, log the issue but do not bomb!
		CEGUI_CATCH(CEGUI::Exception&)
		{}
	}
}


bool CEGUITestApplication::handle_ItemDropped(const CEGUI::EventArgs& args)
{
	using namespace CEGUI;
	
	// cast the args to the 'real' type so we can get access to extra fields
	const DragDropEventArgs& dd_args =
			static_cast<const DragDropEventArgs&>(args);
	
	if (!dd_args.window->getChildCount())
	{
		// add dragdrop item as child of target if target has no item already
		dd_args.window->addChild(dd_args.dragDropItem);
		// Now we must reset the item position from it's 'dropped' location,
		// since we're now a child of an entirely different window
		dd_args.dragDropItem->setPosition(
					UVector2(UDim(0.05f, 0),UDim(0.05f, 0)));
	}
	
	return true;
}

//----------------------------------------------------------------------------//
bool CEGUITestApplication::handle_CloseButton(const CEGUI::EventArgs&)
{
	return true;
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


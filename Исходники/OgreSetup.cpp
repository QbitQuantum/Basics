/** Configures the application - returns false if the user chooses to abandon configuration. */
Ogre::Root* OgreSetup::configure(void)
{

	ConfigService& configService(EmberServices::getSingleton().getConfigService());
	createOgreSystem();
#ifndef BUILD_WEBEMBER
	bool success = false;
	bool suppressConfig = false;
	if (configService.itemExists("ogre", "suppressconfigdialog")) {
		suppressConfig = static_cast<bool>(configService.getValue("ogre", "suppressconfigdialog"));
	}
	try {
		success = mRoot->restoreConfig();
		if (!success || !suppressConfig) {
			success = showConfigurationDialog();
		}

	} catch (const std::exception& ex) {
		S_LOG_WARNING("Error when showing config dialog. Will try to remove ogre.cfg file and retry." << ex);
		unlink((EmberServices::getSingleton().getConfigService().getHomeDirectory() + "/ogre.cfg").c_str());
		try {
			success = mRoot->showConfigDialog();
		} catch (const std::exception& ex) {
			S_LOG_CRITICAL("Could not configure Ogre. Will shut down." << ex);
		}
	}
	if (!success) {
		return false;
	}

	mRenderWindow = mRoot->initialise(true, "Ember");

#else //BUILD_WEBEMBER == true
	//In webember we will disable the config dialog.
	//Also we will use fixed resolution and windowed mode.
	try {
		mRoot->restoreConfig();
	} catch (const std::exception& ex) {
		//this isn't a problem, we will set the needed functions manually.
	}
	Ogre::RenderSystem* renderer = mRoot->getRenderSystem();
#ifdef _WIN32
	//on windows, the default renderer is directX, we will force OpenGL.
	renderer = mRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
	if (renderer != NULL) {
		mRoot->setRenderSystem(renderer);
	} else {
		S_LOG_WARNING("OpenGL RenderSystem not found. Starting with default RenderSystem.");
		renderer = mRoot->getRenderSystem();
	}
#endif // _WIN32
	renderer->setConfigOption("Video Mode", "800 x 600");
	renderer->setConfigOption("Full Screen", "no");

	mRoot->initialise(false, "Ember");

	Ogre::NameValuePairList options;

	if (configService.itemExists("ogre", "windowhandle")) {
		//set the owner window
		std::string windowhandle = configService.getValue("ogre", "windowhandle");
		options["parentWindowHandle"] = windowhandle;

		//put it in the top left corner
		options["top"] = "0";
		options["left"] = "0";
	}

	mRenderWindow = mRoot->createRenderWindow("Ember",800,600,false,&options);

#endif // BUILD_WEBEMBER
#ifdef _WIN32
	//do some FPU fiddling, since we need the correct settings for stuff like mercator (which uses fractals etc.) to work
	_fpreset();
	_controlfp(_PC_64, _MCW_PC);
	_controlfp(_RC_NEAR , _MCW_RC);
#endif

	mRenderWindow->setActive(true);
	mRenderWindow->setAutoUpdated(true);
	mRenderWindow->setVisible(true);

	setStandardValues();

	// Create new scene manager factory
	mSceneManagerFactory = new EmberPagingSceneManagerFactory();

	// Register our factory
	mRoot->addSceneManagerFactory(mSceneManagerFactory);

	return mRoot;
}
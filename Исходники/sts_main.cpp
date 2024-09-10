int main(int argc, char* argv[])
{
	std::unique_ptr<ExecutionArgs> exArgs(new ExecutionArgs());
	if (!processCommandLineArgs(argc, argv, *exArgs)) {
		return -1;
	} else if (exArgs->helpPrompt) {
		std::cout << "Usage: sts [--help] || [--config]" << std::endl;
		std::cout << "Options:" << std::endl;
		std::cout << "\t --help - print this message;" << std::endl;
		std::cout << "\t --config - show config dialog." << std::endl;
		std::cout << std::endl;
		return 0;
	}

	try {
		Ogre::String lConfigFileName = "ogre.cfg";
		Ogre::String lPluginsFileName = "plugins.cfg";
		Ogre::String lLogFileName = "Ogre_STS.log";

		std::unique_ptr<Ogre::Root> lRoot(new Ogre::Root(lPluginsFileName, lConfigFileName, lLogFileName));

		if (exArgs->showConfigDialog) {
			if (!lRoot->showConfigDialog()) {
				return 0;
			}
		}

		Ogre::String lWindowTitle = "STS";
		Ogre::String lCustomCapacities = "";

		/* Check for the valid ogre.cfg */
		bool lCreateAWindowAutomatically = lRoot->restoreConfig();
		if (!lCreateAWindowAutomatically) {
			initSomeRenderSystem(lRoot);
		}
		Ogre::RenderWindow* lWindow = lRoot->initialise(lCreateAWindowAutomatically, lWindowTitle, lCustomCapacities);

		if (!lWindow) {
			/* ogre.cfg is not available - start with hardcoded parameters */
			unsigned int lSizeX = 800;
			unsigned int lSizeY = 600;
			bool lFullscreen = false;

			Ogre::NameValuePairList lParams;
			lParams["FSAA"] = "0";
			lParams["vsync"] = "true";
			lWindow = lRoot->createRenderWindow(lWindowTitle, lSizeX, lSizeY, lFullscreen, &lParams);
		}

		/* Create a scene manager */
		Ogre::SceneManager* lScene = lRoot->createSceneManager(Ogre::ST_GENERIC, "SceneManager");

		Ogre::SceneNode* lRootSceneNode = lScene->getRootSceneNode();

		/* Create camera */
		Ogre::Camera* lCamera = lScene->createCamera("MyCamera");

		/* Create viewport (camera <-> window) */
		Ogre::Viewport* vp = lWindow->addViewport(lCamera);

		vp->setAutoUpdated(true);
		vp->setBackgroundColour(Ogre::ColourValue(1, 0, 1));

		lCamera->setAspectRatio(float(vp->getActualWidth()) / vp->getActualHeight());
		lCamera->setPosition(Ogre::Vector3(0, 100, -1));
		lCamera->lookAt(Ogre::Vector3(0, 0, 0));

		/* Set clipping*/
		lCamera->setNearClipDistance(1.5f);
		lCamera->setFarClipDistance(3000.0f);

		/* Lighting */
		Ogre::Light* lLight = lScene->createLight("MainLight");
		lLight->setPosition(Ogre::Vector3(0, 100, 0));

		/* Resource manager */
		Ogre::String lRcGroupName = "Main group";
		initResourceMainGroup(lRcGroupName);

		/* Load model */
		Ogre::Entity* lShipEntity = lScene->createEntity("airship.mesh");
		lShipEntity->setCastShadows(false);

		Ogre::SceneNode* lShipNode = lRootSceneNode->createChildSceneNode();
		lShipNode->attachObject(lShipEntity);
		lShipNode->setScale(Ogre::Vector3(3.15f, 3.15f, 3.15f));

		/* Starship start point */
		Ogre::Vector3 razorSP(0, -200, -100);
		lShipNode->setPosition(razorSP);

		/* Sprite billboard */
		Ogre::SceneNode* lSpriteNode = lRootSceneNode->createChildSceneNode();
		Ogre::BillboardSet* lBillboardSet = lScene->createBillboardSet();
		lBillboardSet->setMaterialName("enemy_01", lRcGroupName);
		lBillboardSet->setTextureStacksAndSlices(1, 4);
		Ogre::Billboard* lSpriteBillboard = lBillboardSet->createBillboard(Ogre::Vector3(0, 0, 0));
		lSpriteBillboard->setDimensions(48.0f / 2.0f, 58.0f / 2.0f);
		lSpriteBillboard->setTexcoordIndex(1);
		lSpriteNode->attachObject(lBillboardSet);
		lSpriteNode->setPosition(Ogre::Vector3(0, -200, 100));

		/* Obtain the timer pointer */
		Ogre::Timer* lTimer = lRoot->getTimer();

		/* Skip all the messages */
		lWindow->setAutoUpdated(false);
		lRoot->clearEventTimes();

		while (!lWindow->isClosed()) {
			float angle = Ogre::Math::Sin(float(lTimer->getMilliseconds()) * Ogre::Math::PI / 2000.0f) * Ogre::Math::PI / 4.0f;
			float diplacement = Ogre::Math::Cos(float(lTimer->getMilliseconds()) * Ogre::Math::PI / 2000.0f) * 100.0f;
			lShipNode->setOrientation(Ogre::Quaternion(Ogre::Radian(angle), Ogre::Vector3(0, 0, 1)));
			lShipNode->setPosition(razorSP + Ogre::Vector3(diplacement, 0.0f, 0.0f));

			unsigned int spriteFrame = (lTimer->getMilliseconds() / 125) % 2;
			lSpriteBillboard->setTexcoordIndex(spriteFrame);

			lWindow->update(false);
			lWindow->swapBuffers();
			lRoot->renderOneFrame();

			Ogre::WindowEventUtilities::messagePump();
		}
		Ogre::LogManager::getSingleton().logMessage("Render window closed.");
	}
	catch (Ogre::Exception &e) {
		std::cerr << "Ogre::Exception: " << e.what() << std::endl;
	}
	catch (std::exception &e) {
		std::cerr << "std::exception: " << e.what() << std::endl;
	}

	return 0;
}
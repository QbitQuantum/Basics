void ReymentaServerApp::setup()
{
	// parameters
	mParameterBag = ParameterBag::create();
	mParameterBag->mLiveCode = true;
	mParameterBag->mRenderThumbs = false;
	loadShader(getAssetPath("default.fs"));
	// utils
	mBatchass = Batchass::create(mParameterBag);
	CI_LOG_V("reymenta setup");
	mFirstLaunch = true;

	setWindowSize(mParameterBag->mMainWindowWidth, mParameterBag->mMainWindowHeight);
	// 12 fps is enough for a router
	setFrameRate(120.0f);
	setWindowPos(ivec2(0, 40));

	// setup shaders and textures
	mBatchass->setup();

	mParameterBag->mMode = MODE_WARP;
	mParameterBag->iResolution.x = mParameterBag->mRenderWidth;
	mParameterBag->iResolution.y = mParameterBag->mRenderHeight;
	mParameterBag->mRenderResolution = ivec2(mParameterBag->mRenderWidth, mParameterBag->mRenderHeight);

	CI_LOG_V("createRenderWindow, resolution:" + toString(mParameterBag->iResolution.x) + "x" + toString(mParameterBag->iResolution.y));
	mParameterBag->mRenderResoXY = vec2(mParameterBag->mRenderWidth, mParameterBag->mRenderHeight);
	mParameterBag->mRenderPosXY = ivec2(mParameterBag->mRenderX, mParameterBag->mRenderY);

	// instanciate the console class
	mConsole = AppConsole::create(mParameterBag, mBatchass);

	// imgui
	margin = 3;
	inBetween = 3;
	// mPreviewFboWidth 80 mPreviewFboHeight 60 margin 10 inBetween 15 mPreviewWidth = 160;mPreviewHeight = 120;
	w = mParameterBag->mPreviewFboWidth + margin;
	h = mParameterBag->mPreviewFboHeight * 2.3;
	largeW = (mParameterBag->mPreviewFboWidth + margin) * 4;
	largeH = (mParameterBag->mPreviewFboHeight + margin) * 5;
	largePreviewW = mParameterBag->mPreviewWidth + margin;
	largePreviewH = (mParameterBag->mPreviewHeight + margin) * 2.4;
	displayHeight = mParameterBag->mMainDisplayHeight - 50;
	mouseGlobal = false;
	showConsole = showGlobal = showTextures = showAudio = showMidi = showChannels = showShaders = true;
	showTest = showTheme = showOSC = showFbos = false;
	/* set ui window and io events callbacks
	   with autorender == false, we have to use NewFrame and Render
	   but we have access to DrawData to send to remoteImGui
	   void Renderer::initFontTexture()
	   {
	   unsigned char* pixels;
	   int width, height;
	   ImGui::GetIO().Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
	   mFontTexture = gl::Texture::create( pixels, GL_RGBA, width, height, gl::Texture::Format().magFilter(GL_LINEAR).minFilter(GL_LINEAR) );
	   ImGui::GetIO().Fonts->ClearTexData();
	   ImGui::GetIO().Fonts->TexID = (void *)(intptr_t) mFontTexture->getId();
	   }
	  
	ui::initialize(ui::Options().autoRender(false).fonts({
		{ getAssetPath("KontrapunktBob-Light.ttf"), 12 },
		{ getAssetPath("KontrapunktBob-Bold.ttf"), 20 },
		{ getAssetPath("DroidSans.ttf"), 12 }
	})
	.fontGlyphRanges("DroidSans", { 0xf000, 0xf06e, 0 })); */
	ui::initialize(ui::Options().autoRender(false));

	// warping
	mUseBeginEnd = false;
	updateWindowTitle();
	disableFrameRate();

	// initialize warps
	mSettings = getAssetPath("") / "warps.xml";
	if (fs::exists(mSettings)) {
		// load warp settings from file if one exists
		mWarps = Warp::readSettings(loadFile(mSettings));
	}
	else {
		// otherwise create a warp from scratch
		mWarps.push_back(WarpBilinear::create());
		mWarps.push_back(WarpPerspective::create());
		mWarps.push_back(WarpPerspectiveBilinear::create());
	}

	// load test image
	try {
		mImage = gl::Texture::create(loadImage(loadAsset("help.jpg")),
			gl::Texture2d::Format().loadTopDown().mipmap(true).minFilter(GL_LINEAR_MIPMAP_LINEAR));

		//mSrcArea = mImage->getBounds();

		// adjust the content size of the warps
		Warp::setSize(mWarps, mImage->getSize());
	}
	catch (const std::exception &e) {
		console() << e.what() << std::endl;
	}
	mSrcArea = Area(0, 0, mParameterBag->mFboWidth*4, mParameterBag->mFboHeight*4);
	mMesh = gl::VboMesh::create(geom::Rect());
}
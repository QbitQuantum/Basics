void ReymentaHapPlayerApp::setup()
{
	g_Width = 640;
	g_Height = 480;
	// parameters
	mParameterBag = ParameterBag::create();
	// utils
	mBatchass = Batchass::create(mParameterBag);
	// if AutoLayout, try to position the window on the 2nd screen
	if (mParameterBag->mAutoLayout)
	{
		mBatchass->getWindowsResolution();
	}

	setWindowSize(mParameterBag->mRenderWidth, mParameterBag->mRenderHeight);
	setWindowPos(ivec2(mParameterBag->mRenderX, mParameterBag->mRenderY));

	setFullScreen(false);
	//enableHighDensityDisplay();	
	setFrameRate(60);
	mBatchass->setup();
	mLoopVideo = false;
	// -------- SPOUT -------------
	// Set up the texture we will use to send out
	// We grab the screen so it has to be the same size
	bInitialized = false;

}
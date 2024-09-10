void SmilesApp::setup()
{	
    mSmileLimit = 4.0f;
    mSmileAverageNumOfFrames = 10;
    mCamIndex = 0;
    mFps = getAverageFps();
    
    try {
		mCapture = Capture( CAMWIDTH, CAMHEIGHT );
		mCapture.start();
	}
	catch( ... ) {
		console() << "Failed to initialize capture" << std::endl;
	}
    
    mSmileRect = Rectf(300,100,600,400);
    setupSmileDetector(mSmileRect.getInteriorArea().getWidth(), mSmileRect.getInteriorArea().getHeight());
    console()<< mSmileRect.getInteriorArea().getWidth() << mSmileRect.getInteriorArea().getHeight() << endl;
	mSmileThreshold = 0;
	mSmileAverageIndex = 0;
    
    mParams = params::InterfaceGl( "Parameters", Vec2i( 220, 170 ) );
    mParams.addParam( "FPS", &mFps,"", true );
    mParams.addSeparator();
	mParams.addParam( "SmileResponse", &mSmileResponse, "", true );
    mParams.addParam( "SmileThreshold", &mSmileThreshold, "", true );
    
    mParams.addParam( "mSmileLimit", &mSmileLimit );
    mParams.addParam( "mSmileAverageNumOfFrames", &mSmileAverageNumOfFrames );
    
}
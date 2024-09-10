// Initialization for this application
bool SlamDriver::init(void)
{
    std::cout << "SlamDriver init." << std::endl;
	
#ifdef ENABLE_LOG
	std::cout << "Logging is enabled. This severely hits performance! It can be disabled in dtslam/log.h." << std::endl;
#else
	std::cout << "Logging is disabled. See dtslam/log.h to enable it." << std::endl;
#endif

#ifdef ENABLE_PROFILER
	std::cout << "Profiling is enabled.\n";
#else
	std::cout << "Profiling is disabled. See dtslam/Profiler.h to enable it.\n";
#endif

    Profiler::Instance().setCurrentThreadName("render");
    char glogstr[] = "dtslam";

    google::InitGoogleLogging(glogstr);

    if (!initImageSrc())
    {
    	DTSLAM_LOG << "Couldn't initialize image source.\n";
        return false;
    }

    // Initialize Shader
    if (!mShaders.init())
    {
		DTSLAM_LOG << "Couldn't initialize shaders.\n";
		return false;
    }

	//Determine downscale at input
	int width = mImageSrc->getSourceSize().width;
	mDownsampleInputCount = 0;
	while(width > FLAGS_DriverMaxImageWidth)
	{
		width = (width+1)/2;
		mDownsampleInputCount++;
	}
	int scale = 1<<mDownsampleInputCount;

	mImageSrc->setDownsample(mDownsampleInputCount);
	mImageSize = mImageSrc->getSize();
	DTSLAM_LOG << "Input image size after downsampling: " << mImageSize << "\n";

	//Check size vs calibration
	cv::Size expectedSize(FLAGS_CameraWidth/scale, FLAGS_CameraHeight/scale);
	if(mImageSize.width != expectedSize.width || mImageSize.height != expectedSize.height)
	{
		DTSLAM_LOG << "Warning: image size " << mImageSize << " does not match calibration size " << expectedSize << "\n";
	}

	//Get first frame
	if(!mImageSrc->update())
    {
    	DTSLAM_LOG << "Couldn't get first frame from image source.\n";
    	return false;
    }

    //Init camera
	mCamera.reset(new CameraModel());
	mCamera->init((float)FLAGS_CameraFx / scale, (float)FLAGS_CameraFy / scale, (float)FLAGS_CameraU0 / scale, (float)FLAGS_CameraV0 / scale, FLAGS_CameraWidth / scale, FLAGS_CameraHeight / scale);
	mCamera->getDistortionModel().init((float)FLAGS_CameraK1, (float)FLAGS_CameraK2);
	mCamera->getDistortionModel().setMaxRadius(mCamera->getMaxRadiusSq(mImageSize));
	mCamera->initLUT();

	//Slam system
	cv::Mat1b imageGray = mImageSrc->getImgGray();
	cv::Mat3b imageColor = mImageSrc->getImgColor();
	mSlam.init(mCamera.get(), mImageSrc->getCaptureTime(), imageColor, imageGray);
	mSlam.setSingleThreaded(FLAGS_DriverSingleThreaded);

	//Add windows
	mWindows.push_back(std::unique_ptr<BaseWindow>(new MatchesWindow()));
	mWindows.push_back(std::unique_ptr<BaseWindow>(new MapExpanderWindow()));
	mWindows.push_back(std::unique_ptr<BaseWindow>(new MapWindow()));
	mWindows.push_back(std::unique_ptr<BaseWindow>(new KeyFramePairWindow()));
	mWindows.push_back(std::unique_ptr<BaseWindow>(new ARWindow()));
	mWindows.push_back(std::unique_ptr<BaseWindow>(new TestMatchWindow()));
	mWindows.push_back(std::unique_ptr<BaseWindow>(new FrameLinkWindow()));

	//Add bindings
	mKeyBindings.addBinding(true,GLUT_KEY_F5,static_cast<KeyBindingHandler<SlamDriver>::SimpleBindingFunc>(&SlamDriver::runVideo),"Run the video stream.");
	mKeyBindings.addBinding(true, GLUT_KEY_F8, static_cast<KeyBindingHandler<SlamDriver>::SimpleBindingFunc>(&SlamDriver::saveMap), "Save the map to disk.");
	mKeyBindings.addBinding(true, GLUT_KEY_F9, static_cast<KeyBindingHandler<SlamDriver>::SimpleBindingFunc>(&SlamDriver::loadMap), "Load the map from disk.");
	mKeyBindings.addBinding(false, ' ', static_cast<KeyBindingHandler<SlamDriver>::SimpleBindingFunc>(&SlamDriver::stepVideo), "Advance one frame.");
	mKeyBindings.addBinding(false,'p',static_cast<KeyBindingHandler<SlamDriver>::SimpleBindingFunc>(&SlamDriver::toggleProfilerMode),"Toggle profiler mode.");
	mKeyBindings.addBinding(false,'P',static_cast<KeyBindingHandler<SlamDriver>::SimpleBindingFunc>(&SlamDriver::resetProfiler),"Reset profiler counts.");
	mKeyBindings.addBinding(false,'r',static_cast<KeyBindingHandler<SlamDriver>::SimpleBindingFunc>(&SlamDriver::resetSystem),"Reset the slam system.");
	mKeyBindings.addBinding(false,'R',static_cast<KeyBindingHandler<SlamDriver>::SimpleBindingFunc>(&SlamDriver::startRecording),"Reset and start recording.");
	mKeyBindings.addBinding(true,GLUT_KEY_F1,static_cast<KeyBindingHandler<SlamDriver>::SimpleBindingFunc>(&SlamDriver::resyncTracker),"Resyncs the tracker with/without 2D matches.");

	for(int i=0; i<(int)mWindows.size(); ++i)
		mKeyBindings.addBinding(false,i+'1',static_cast<KeyBindingHandler<SlamDriver>::BindingFunc>(&SlamDriver::changeWindowKey),"Show window: " + mWindows[i]->getName());

	mKeyBindings.addBinding(false,27,static_cast<KeyBindingHandler<SlamDriver>::SimpleBindingFunc>(&SlamDriver::escapePressed),"Quit.");

	DTSLAM_LOG << "\nBasic keys:\n";
	mKeyBindings.showHelp();

	setActiveWindow(mWindows[0].get());

	setARCube(cv::Point3f(0, 0,10), cv::Point3f(0.1, 0, 0), cv::Point3f(0, 0.1, 0), cv::Point3f(0, 0, 0.1));
	//disableARCube();

    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);

	mFPS = 0;
	mLastFPSCheck = std::chrono::high_resolution_clock::now();
	mFPSUpdateDuration = std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(std::chrono::seconds(1));
	mFPSSampleAccum = std::chrono::high_resolution_clock::duration(0);
	mFPSSampleCount = 0;

	mInitialized = true;
    return true;
}
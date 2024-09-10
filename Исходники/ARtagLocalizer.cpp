int initARtagPose(int width, int height, float markerWidth, vector<string> camParamFiles)
{
	size_t numPixels = width*height;
	cameraBuffer = new unsigned char[numPixels];
	imgwidth = width;
	imgheight = height;
	patternCenter_[0] = patternCenter_[1] = 0.0;
	patternWidth_ = markerWidth;
	numCams_ = camParamFiles.size();
	trackers = new ARToolKitPlus::TrackerSingleMarker *[numCams_];
	// create a tracker that does:
	//  - 6x6 sized marker images
	//  - samples at a maximum of 6x6
	//  - works with luminance (gray) images
	//  - can load a maximum of 1 pattern
	//  - can detect a maximum of 8 patterns in one image
	for (int i = 0; i < numCams_; ++i) {
		if (camParamFiles[i].compare("null") == 0) {
			trackers[i] = NULL;
			continue;
		}
		ARToolKitPlus::TrackerSingleMarker *tracker = new ARToolKitPlus::TrackerSingleMarkerImpl<6,6,6, 1, 8>(width,height);
		
		tracker->setPixelFormat(ARToolKitPlus::PIXEL_FORMAT_LUM);
		// load a camera file. 
		if(!tracker->init(camParamFiles[i].c_str(), 1.0f, 1000.0f))
		{
			printf("ERROR: init() failed\n");
			delete cameraBuffer;
			delete tracker;
			return -1;
		}

		// define size of the marker
		tracker->setPatternWidth(patternWidth_);

		// the marker in the BCH test image has a thin border...
		tracker->setBorderWidth(THIN_PATTERN_BORDER);

		// set a threshold. alternatively we could also activate automatic thresholding
		tracker->setThreshold(150);
		tracker->activateAutoThreshold(true);

		// let's use lookup-table undistortion for high-speed
		// note: LUT only works with images up to 1024x1024
		tracker->setUndistortionMode(ARToolKitPlus::UNDIST_LUT);

		// RPP is more robust than ARToolKit's standard pose estimator
		tracker->setPoseEstimator(ARToolKitPlus::POSE_ESTIMATOR_RPP);
		//tracker->setPoseEstimator(ARToolKitPlus::POSE_ESTIMATOR_ORIGINAL);

		// switch to simple ID based markers
		// use the tool in tools/IdPatGen to generate markers
		tracker->setMarkerMode(useBCH ? ARToolKitPlus::MARKER_ID_BCH : ARToolKitPlus::MARKER_ID_SIMPLE);

		trackers[i] = tracker;
	}

	init = true;
	return 0;
}
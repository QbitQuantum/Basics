	virtual bool init() {
		// Work with luminance images
		setPixelFormat(ARToolKitPlus::PIXEL_FORMAT_LUM);
		if ( ! checkPixelFormat()) {	
			if (logger)
				logger->artLog("ARToolKitPlus: Invalid Pixel Format!");
			return false;
		}

		// Memory
		if (marker_infoTWO == NULL)
			marker_infoTWO = ARToolKitPlus::artkp_Alloc<ARToolKitPlus::ARMarkerInfo2>(32);

		// Camera
		Camera *camera = new Camera(screenWidth, screenHeight);
		setCamera(camera, 1, 1000);

		// const ARFloat* mat = getProjectionMatrix();
		// printf("Proj mat\n");
		// for(int j=0; j<4; j++) {
		// 	for(int i=0; i<4; i++) {
		// 		printf ("%f, ", mat[i*4 + j]);
		// 	}
		// 	printf ("\n");
		// }

		// Work at full res
		setImageProcessingMode(ARToolKitPlus::IMAGE_FULL_RES);

		// Set border
		setBorderWidth(0.125);

		// Set threshold and activate automatic threshold
		setThreshold(160);
		activateAutoThreshold(true);
		setNumAutoThresholdRetries(2);

		// Switch to BCH ID based markers
		setMarkerMode(ARToolKitPlus::MARKER_ID_BCH);

		// Choose pose estimator
		setPoseEstimator(ARToolKitPlus::
						 //POSE_ESTIMATOR_ORIGINAL);
						 //POSE_ESTIMATOR_ORIGINAL_CONT);
						 POSE_ESTIMATOR_RPP);

		return true;
	}
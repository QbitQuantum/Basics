HRESULT PrimeSenseSensor::createFirstConnected()
{
	HRESULT hr = S_OK;

	openni::Status rc = openni::STATUS_OK;
	const char* deviceURI = openni::ANY_DEVICE;

	rc = openni::OpenNI::initialize();

	std::cout << "After initialization: " << openni::OpenNI::getExtendedError() << std::endl;

	// Create Device
	rc = m_device.open(deviceURI);
	if (rc != openni::STATUS_OK)
	{
		std::cout << "Device open failed: " << openni::OpenNI::getExtendedError() << std::endl;
		openni::OpenNI::shutdown();
		return S_FALSE;
	}

	openni::PlaybackControl* pc = m_device.getPlaybackControl();

	// Create Depth Stream
	rc = m_depthStream.create(m_device, openni::SENSOR_DEPTH);
	if (rc == openni::STATUS_OK)
	{
		rc = m_depthStream.start();
		if (rc != openni::STATUS_OK)
		{
			std::cout << "Couldn't start depth stream: " << openni::OpenNI::getExtendedError() << std::endl;
			m_depthStream.destroy();
		}
	}
	else
	{
		std::cout << "Couldn't find depth stream: " << openni::OpenNI::getExtendedError() << std::endl;
	}

	// Create Color Stream
	rc = m_colorStream.create(m_device, openni::SENSOR_COLOR);
	if (rc == openni::STATUS_OK)
	{
		rc = m_colorStream.start();
		if (rc != openni::STATUS_OK)
		{
			std::cout << "Couldn't start color stream: " << openni::OpenNI::getExtendedError() << " Return code: " << rc << std::endl;
			m_colorStream.destroy();
		}
	}
	else
	{
		std::cout << "Couldn't find color stream: " << openni::OpenNI::getExtendedError() << std::endl;
	}
	if (GlobalAppState::get().s_enableColorCropping) 
	{
		if (m_colorStream.isCroppingSupported()) {
			m_colorStream.setCropping(GlobalAppState::get().s_colorCropX, GlobalAppState::get().s_colorCropY, GlobalAppState::get().s_colorCropWidth, GlobalAppState::get().s_colorCropHeight);
		}
		else {
			std::cout << "cropping is not supported for this color stream" << std::endl;
		}
	}

	// Check Streams
	if (!m_depthStream.isValid() || !m_colorStream.isValid())
	{
		std::cout << "No valid streams. Exiting" << std::endl;
		openni::OpenNI::shutdown();
		return S_FALSE;
	}

	openni::CameraSettings* cs = m_colorStream.getCameraSettings();

	//cs->setAutoWhiteBalanceEnabled(false);
	//cs->setAutoExposureEnabled(false);
	//cs->setGain(1);
	//cs->setExposure(10);

	std::cout << "getGain: " << cs->getGain() << std::endl;
	std::cout << "getExposure: " << cs->getExposure() << std::endl;
	std::cout << "getAutoExposureEnabled: " << cs->getAutoExposureEnabled() << std::endl;
	std::cout << "getAutoWhiteBalanceEnabled: " << cs->getAutoWhiteBalanceEnabled() << std::endl;

	// Get Dimensions
	m_depthVideoMode = m_depthStream.getVideoMode();
	m_colorVideoMode = m_colorStream.getVideoMode();

	int depthWidth = m_depthVideoMode.getResolutionX();
	int depthHeight = m_depthVideoMode.getResolutionY();
	int colorWidth = m_colorVideoMode.getResolutionX();
	int colorHeight = m_colorVideoMode.getResolutionY();

	RGBDSensor::init(depthWidth, depthHeight, colorWidth, colorHeight, 1);

	m_streams = new openni::VideoStream*[2];
	m_streams[0] = &m_depthStream;
	m_streams[1] = &m_colorStream;

	if (rc != openni::STATUS_OK)
	{
		openni::OpenNI::shutdown();
		return 3;
	}

	m_device.setImageRegistrationMode(openni::IMAGE_REGISTRATION_DEPTH_TO_COLOR);

	float focalLengthX = (depthWidth/2.0f)/tan(m_depthStream.getHorizontalFieldOfView()/2.0f);
	float focalLengthY = (depthHeight/2.0f)/tan(m_depthStream.getVerticalFieldOfView()/2.0f);
	initializeDepthIntrinsics(focalLengthX, focalLengthY, depthWidth/2.0f, depthHeight/2.0f);

	focalLengthX =  (colorWidth/2.0f)/tan(m_colorStream.getHorizontalFieldOfView()/2.0f);
	focalLengthY =  (colorHeight/2.0f)/tan(m_colorStream.getVerticalFieldOfView()/2.0f);
	initializeColorIntrinsics(focalLengthX, focalLengthY, colorWidth/2.0f, colorHeight/2.0f);

	Matrix3f R; R.setIdentity(); Vector3f t; t.setZero();
	initializeColorExtrinsics(R, t);

	R(0, 0) =  9.9991741106823473e-001; R(0, 1) =  3.0752530258331304e-003; R(0, 2) = -1.2478536028949385e-002;
	R(1, 0) = -3.0607678272497924e-003; R(1, 1) =  9.9999461994140826e-001; R(1, 2) =  1.1797408808971066e-003;
	R(2, 0) =  1.2482096895408091e-002; R(2, 1) = -1.1414495457493831e-003; R(2, 2) =  9.9992144408949846e-001;

	//t[0] = -2.5331974929667012e+001;  t[1] = 6.1798287248283634e-001; t[2] = 3.8510108109251804e+000;
	//t[0] /= 1000.0f; t[1] /= 1000.0f; t[2] /= 1000.0f;
	//
	//initializeDepthExtrinsics(R, t);

	return hr;
}
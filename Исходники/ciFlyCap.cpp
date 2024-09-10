ciFlyCap::Obj::Obj()
{

	// Set flags
	mCapturing = false;
	mNewFrame = false;

	// Set default properties
	mCamera = 0;
	mChannelCount = 3;
	mDeviceId = 0;
	mSurfaceChannelOrder = SurfaceChannelOrder::RGB;
	setPixelFormat(PixelFormat::PIXEL_FORMAT_RGB8);

	// Get camera count
	mErr = mBusManager.GetNumOfCameras(&mCameraCount);
	if (mErr != PGRERROR_OK)
		showError();

}
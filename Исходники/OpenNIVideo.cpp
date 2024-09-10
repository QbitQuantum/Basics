bool OpenNIVideo::update(osg::NodeVisitor* nv) {

	//this is the main function of your video plugin
	//you can either retrieve images from your video stream/camera/file
	//or communicate with a thread to synchronize and get the data out
	
	//the most important is to synchronize your data
	//and copy the result to the VideoImageSteam used in this plugin
	//

	//0. you can collect some stats, for that you can use a timer
	osg::Timer t;

	{

	//1. mutex lock access to the image video stream
	OpenThreads::ScopedLock<OpenThreads::Mutex> _lock(this->getMutex());

	osg::notify(osg::DEBUG_INFO)<<"osgART::OpenNIVideo::update() get new image.."<<std::endl;

	XnStatus nRetVal = XN_STATUS_OK;

	nRetVal=context.WaitAndUpdateAll();
	CHECK_RC(nRetVal, "Update Data");

	xnFPSMarkFrame(&xnFPS);

	depth_generator.GetMetaData(depthMD);
	const XnDepthPixel* pDepthMap = depthMD.Data();
	//depth pixel floating point depth map.
	
	image_generator.GetMetaData(imageMD);
	const XnUInt8* pImageMap = imageMD.Data();

	// Hybrid mode isn't supported in this sample
	if (imageMD.FullXRes() != depthMD.FullXRes() || imageMD.FullYRes() != depthMD.FullYRes())
	{
		std::cerr<<"The device depth and image resolution must be equal!"<<std::endl;
		exit(1);
	}

	// RGB is the only image format supported.
	if (imageMD.PixelFormat() != XN_PIXEL_FORMAT_RGB24)
	{
		std::cerr<<"The device image format must be RGB24"<<std::endl;
		exit(1);
	}
	
	const XnDepthPixel* pDepth=pDepthMap;
	const XnUInt8* pImage=pImageMap;
	
	XnDepthPixel zMax = depthMD.ZRes();
    //convert float buffer to unsigned short
	for ( unsigned int i=0; i<(depthMD.XRes() * depthMD.YRes()); ++i )
    {
            *(_depthBufferByte + i) = 255 * (float(*(pDepth + i)) / float(zMax));
    }

	memcpy(_videoStreamList[0]->data(),pImage, _videoStreamList[0]->getImageSizeInBytes());
	
	memcpy(_videoStreamList[1]->data(),_depthBufferByte, _videoStreamList[1]->getImageSizeInBytes());

	//3. don't forget to call this to notify the rest of the application
	//that you have a new video image
	_videoStreamList[0]->dirty();
	_videoStreamList[1]->dirty();
	}

	//4. hopefully report some interesting data
	if (nv) {

		const osg::FrameStamp *framestamp = nv->getFrameStamp();

		if (framestamp && _stats.valid())
		{
			_stats->setAttribute(framestamp->getFrameNumber(),
				"Capture time taken", t.time_m());
		}
	}


	// Increase modified count every X ms to ensure tracker updates
	if (updateTimer.time_m() > 50) {
		_videoStreamList[0]->dirty();
		_videoStreamList[1]->dirty();
		updateTimer.setStartTick();
	}

	return true;
}
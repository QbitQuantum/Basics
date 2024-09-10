int Init()
{
	
	XnStatus rc;

	//Make sure our image types are the same as the OpenNI image types.
	assert(sizeof(XnRGB24Pixel) == sizeof(ColorPixel));
	assert(sizeof(XnDepthPixel) == sizeof(DepthPixel));
	assert(sizeof(XnStatus) == sizeof(int));

	// Load OpenNI xml settings
	char filePath[255];
	int length = Util::Helpers::GetExeDirectory(filePath, sizeof(filePath));
	filePath[length] = '\\';
	strcpy(&filePath[length+1], SAMPLE_XML_PATH);

	EnumerationErrors errors;
	rc = deviceContext.InitFromXmlFile(filePath, &errors);
	if (rc == XN_STATUS_NO_NODE_PRESENT)
	{
		//One reason would be if Microsoft SDK is installed beside PrimeSense.  Device manager should say PrimeSense instead of Microsoft Kinect.
		
		//XnChar strError[1024];
		//errors.ToString(strError, 1024);
		//LOGE("%s\n", strError);
		return -1;
	}
	else if (rc != XN_STATUS_OK)
	{
		fprintf(stderr, "%s\n", xnGetStatusString(rc));
		/*LOGE("Open failed: %s\n", xnGetStatusString(rc));*/
		return (rc);
	}

	// Retrieve colour and depth nodes
	rc = deviceContext.FindExistingNode(XN_NODE_TYPE_IMAGE, colorImageGenerator);
	rc = deviceContext.FindExistingNode(XN_NODE_TYPE_DEPTH, depthImageGenerator);

	// Set mirror mode to off
	SetMirrorMode(false);

	// Get a frame to perform checks on it
	ImageMetaData colorImageMetaData;
	DepthMetaData depthImageMetaData;
	depthImageGenerator.GetMetaData(depthImageMetaData);
	colorImageGenerator.GetMetaData(colorImageMetaData);

	// Hybrid mode isn't supported in this sample
	if (colorImageMetaData.FullXRes() != depthImageMetaData.FullXRes() || colorImageMetaData.FullYRes() != depthImageMetaData.FullYRes())
	{
		/*LOGE("The device depth and image resolution must be equal!\n");*/
		return 1;
	}

	// RGB is the only image format supported.
	if (colorImageMetaData.PixelFormat() != XN_PIXEL_FORMAT_RGB24)
	{
		/*LOGE("The device image format must be RGB24\n");*/
		return 1;
	}
	
	// Need to make sure the automatic alignment of colour and depth images is supported.
	XnBool isSupported = depthImageGenerator.IsCapabilitySupported("AlternativeViewPoint");
	if(!isSupported)
	{
		/*LOGE("Cannot set AlternativeViewPoint!\n");*/
		return 1;
	}

	
	// Set it to VGA maps at 30 FPS
	/*XnMapOutputMode mapMode;
	mapMode.nXRes = XN_VGA_X_RES;
	mapMode.nYRes = XN_VGA_Y_RES;
	mapMode.nFPS = 60;
	rc = g_depth.SetMapOutputMode(mapMode);
	if(rc)
	{
		LOGE("Failed to set depth map mode: %s\n", xnGetStatusString(rc));
		return 1;
	}
	mapMode.nFPS = 30;
	rc = g_image.SetMapOutputMode(mapMode);
	if(rc)
	{
		LOGE("Failed to set image map mode: %s\n", xnGetStatusString(rc));
		return 1;
	}*/


	// Set automatic alignment of the colour and depth images.
	rc = depthImageGenerator.GetAlternativeViewPointCap().SetViewPoint(colorImageGenerator);
	if(rc)
	{
		/*LOGE("Failed to set depth map mode: %s\n", xnGetStatusString(rc));*/
		return 1;
	}


	return XN_STATUS_OK;
}
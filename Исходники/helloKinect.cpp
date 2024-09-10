void mixRGB_Depth()
{
	bool bShouldRun = true;
	int c;

	XnStatus nRetVal = XN_STATUS_OK;
	Context context;

	// Initialize context object
	nRetVal = context.Init();

	// Check error code
	if (nRetVal)
		printf("Error: %s", xnGetStatusString(nRetVal));

	context.SetGlobalMirror(true);

	//Create Depth generator node
	DepthGenerator depth;
	nRetVal = depth.Create(context);
	// Check error code
	if (nRetVal)
		printf("Error: %s", xnGetStatusString(nRetVal));

	// Create an ImageGenetor node
	ImageGenerator image;
	nRetVal = image.Create(context);
	if (nRetVal)
		printf("Error: %s", xnGetStatusString(nRetVal));

	// Sync the DepthGenerator with the ImageGenerator
	nRetVal = depth.GetAlternativeViewPointCap().SetViewPoint(image);
	if (nRetVal)
		printf("Error: %s", xnGetStatusString(nRetVal));

	//Set it to VGA maps at 30 fps
	XnMapOutputMode mapMode;
	mapMode.nXRes = XN_VGA_X_RES;
	mapMode.nYRes = XN_VGA_Y_RES;
	mapMode.nFPS = 30;
	nRetVal = depth.SetMapOutputMode(mapMode);

	// Make it start generating data
	nRetVal = context.StartGeneratingAll();
	if (nRetVal)
		printf("Error: %s", xnGetStatusString(nRetVal));

	// Create an OpenCv matrix
	CvMat* depthMetersMat = cvCreateMat(480, 640, CV_16UC1);
	IplImage *kinectDepthImage;
	kinectDepthImage = cvCreateImage(cvSize(640,480), 16, 1);

	IplImage *rgbimg = cvCreateImageHeader(cvSize(640,480), 8,3);

	// Main loop
	while (bShouldRun)
	{
		//wait for new data to be available
		nRetVal = context.WaitOneUpdateAll(depth);
		if (nRetVal)
		{
			printf("Error: %s", xnGetStatusString(nRetVal));
			continue;
		}
		//Take current depth map
		const XnDepthPixel* pDepthMap = depth.GetDepthMap();

		for (int y=0; y<XN_VGA_Y_RES; y++)
		{
			for (int x=0; x<XN_VGA_X_RES; x++)
			{
				depthMetersMat->data.s[y*XN_VGA_X_RES+x]=10*pDepthMap[y*XN_VGA_X_RES+x];
			}
		}

		cvGetImage(depthMetersMat, kinectDepthImage);

		//take current image
		const XnRGB24Pixel* pImage = image.GetRGB24ImageMap();
		//process image data
		XnRGB24Pixel* ucpImage = const_cast<XnRGB24Pixel*>(pImage);
		cvSetData(rgbimg, ucpImage, 640*3);
		cvShowImage("RGB", kinectDepthImage);

		c = cvWaitKey(1);
		if (c == 27)
			bShouldRun = false;
	}

	cvReleaseImageHeader(&kinectDepthImage);
	context.Shutdown();
}
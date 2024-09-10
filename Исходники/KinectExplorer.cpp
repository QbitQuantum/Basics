int main ( int argc, char * argv[] )
{
	// 
	// Initialize OpenNI Settings
	// 

	XnStatus nRetVal = XN_STATUS_OK;
	xn::ScriptNode scriptNode;
	xn::EnumerationErrors errors;

	// 
	// Initialize Context Object
	// 

	nRetVal = g_Context.InitFromXmlFile ( CONFIG_XML_PATH, scriptNode, &errors );
	
	if ( nRetVal == XN_STATUS_NO_NODE_PRESENT ) {
		XnChar strError[1024];
		errors.ToString(strError, 1024);
		printf ( "XN_STATUS_NO_NODE_PRESENT:\n%s\n", strError );
		system ( "pause" );

		return ( nRetVal );
	}
	else if ( nRetVal != XN_STATUS_OK ) {
		printf ( "Open failed: %s\n", xnGetStatusString(nRetVal) );	
		system ( "pause" );

		return ( nRetVal );
	}

	// 
	// Handle Image & Depth Generator Node
	// 

	bool colorFlag = true;
	bool depthFlag = true;

	nRetVal = g_Context.FindExistingNode ( XN_NODE_TYPE_DEPTH, g_DepthGen );
	if ( nRetVal != XN_STATUS_OK ) {
		printf("No depth node exists!\n");
		depthFlag = false;
	}
	nRetVal = g_Context.FindExistingNode ( XN_NODE_TYPE_IMAGE, g_ImageGen );
	if ( nRetVal != XN_STATUS_OK ) {
		printf("No image node exists!\n");
		colorFlag = false;
	}

	// g_DepthGen.GetAlternativeViewPointCap().SetViewPoint( g_ImageGen );

	if ( depthFlag ) {
		g_DepthGen.GetMetaData ( g_DepthMD );
		assert ( g_DepthMD.PixelFormat() == XN_PIXEL_FORMAT_GRAYSCALE_16_BIT );
	}
	if ( colorFlag ) {
		g_ImageGen.GetMetaData ( g_ImageMD );
		assert ( g_ImageMD.PixelFormat() == XN_PIXEL_FORMAT_RGB24 );
	}

	g_DepthImgShow = cv::Mat ( g_DepthMD.YRes(), g_DepthMD.XRes(), CV_8UC1  );
	g_DepthImgMat  = cv::Mat ( g_DepthMD.YRes(), g_DepthMD.XRes(), CV_16UC1 );
	g_ColorImgMat  = cv::Mat ( g_ImageMD.YRes(), g_ImageMD.XRes(), CV_8UC3  );
	
	// 
	// Start to Loop
	// 

	bool flipColor = true;
	int ctlWndKey = -1;

	g_StartTickCount = GetTickCount();
	g_HeadTrackingFrameCount = 0;
	
	while ( ctlWndKey != ESC_KEY_VALUE ) 
	{
		nRetVal = g_Context.WaitOneUpdateAll ( g_DepthGen );
		// nRetVal = g_Context.WaitAnyUpdateAll();

#ifdef HANDLING_IMAGE_DATA

		if ( colorFlag ) 
		{
			g_ImageGen.GetMetaData ( g_ImageMD );

			assert ( g_ImageMD.FullXRes() == g_ImageMD.XRes() );
			assert ( g_ImageMD.FullYRes() == g_ImageMD.YRes() );

			GlobalUtility::CopyColorRawBufToCvMat8uc3 ( (const XnRGB24Pixel *)(g_ImageMD.Data()), g_ColorImgMat );
	
			if ( ctlWndKey == 's' || ctlWndKey == 'S' ) {												// Switch
				flipColor = !flipColor;
			}
			if ( flipColor ) {
				cv::cvtColor ( g_ColorImgMat, g_ColorImgMat, CV_RGB2BGR );
			}

			cv::namedWindow ( IMAGE_WIN_NAME, CV_WINDOW_AUTOSIZE );
			cv::imshow ( IMAGE_WIN_NAME, g_ColorImgMat );
		}

#endif

#ifdef HANDLING_DEPTH_DATA

		if ( depthFlag ) 
		{
			g_DepthGen.GetMetaData(g_DepthMD);
		
			// assert ( g_DepthMD.FullXRes() == g_DepthMD.XRes() );
			// assert ( g_DepthMD.FullYRes() == g_DepthMD.YRes() );

			GlobalUtility::CopyDepthRawBufToCvMat16u ( (const XnDepthPixel *)(g_DepthMD.Data()), g_DepthImgMat );
			GlobalUtility::ConvertDepthCvMat16uToGrayCvMat ( g_DepthImgMat, g_DepthImgShow );

			/*
			cv::putText(colorImgMat, 
						GlobalUtility::DoubleToString(g_ImageMD.FPS()) + " FPS", 
						cv::Point(10, 450), 
						cv::FONT_ITALIC, 
						0.7, 
						cv::Scalar(255, 255, 255, 0),
						2,
						8,
						false);
						*/

			cv::namedWindow ( DEPTH_WIN_NAME, CV_WINDOW_AUTOSIZE );
			cv::imshow ( DEPTH_WIN_NAME, g_DepthImgShow );
		}

#endif

		XnFieldOfView fov;
		g_DepthGen.GetFieldOfView( fov );

		std::cout	<< "HFov = " << fov.fHFOV << std::endl
					<< "VFov = " << fov.fVFOV << std::endl;

		ctlWndKey = cvWaitKey ( 5 );

		g_HeadTrackingFrameCount++;
		g_CurrTickCount = GetTickCount();
		std::cout	<< "FPS = " 
					<< 1000 / ( ( double )( g_CurrTickCount - g_StartTickCount ) / ( double )( g_HeadTrackingFrameCount ) ) 
					<< std::endl;
	}

	g_Context.Release ();

	exit ( EXIT_SUCCESS );
}
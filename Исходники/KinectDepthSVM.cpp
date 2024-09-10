int main()
{
	FILE *fptrI = fopen("C:\\Users\\Alan\\Documents\\ShapeFeatures.csv","w");
	fprintf(fptrI, "Classtype, Area, Perimeter, Circularity, Extent\n");
	fclose(fptrI);

	Mat input = imread("C:\\Users\\Alan\\Pictures\\Science Fair 2014\\SVM\\Shape Features\\Fingers.bmp", 1);
	Mat input2 = imread("C:\\Users\\Alan\\Pictures\\Science Fair 2014\\SVM\\Shape Features\\NotFingers.bmp", 1);
	Mat inputF = imread("C:\\Users\\Alan\\Pictures\\Science Fair 2014\\SVM\\Shape Features\\ImageFeaturesBinaryF.bmp", 1);
	Mat gray(input.rows, input.cols, CV_8UC3);
	Mat gray2(input.rows, input.cols, CV_8UC3);
	Mat grayF(input.rows, input.cols, CV_8UC3);
	cvtColor(input, gray, CV_BGR2GRAY);
	cvtColor(input2, gray2, CV_BGR2GRAY);
	cvtColor(inputF, grayF, CV_BGR2GRAY);
	shapeFeatures(gray, input, 1);
	shapeFeatures(gray2, input2, 2);
	namedWindow("Image");
	imshow("Image", input);
	namedWindow("Image2");
	imshow("Image2", input2);

	//------------------------------------------------------
	//--------[SVM]--------
	// Read input data from file created above
	double parameters[5];
	vector<double> svmI, svmA, svmP, svmC, svmE;
	int size = 1;
	double index = 0; double area = 0; double perimeter = 0; double circularity = 0;
	char buffer[1024];
	char *record, *line;
	FILE* fptrR = fopen("C:\\Users\\Alan\\Documents\\ShapeFeatures.csv", "r");
	fscanf(fptrR, "%*[^\n]\n", NULL);

	svmI.resize(size); svmA.resize(size); svmP.resize(size); svmC.resize(size); 

	while((line=fgets(buffer, sizeof(buffer), fptrR))!=NULL)
	{
		size++;
		svmI.resize(size);
		svmA.resize(size);
		svmP.resize(size);
		svmC.resize(size);
		svmE.resize(size);

		record = strtok(line, ";");
		for(int i = 0; i < 5; i++);
		{
			double value = atoi(record);
			record = strtok(line,";");
		}
		char *lineCopy = record;
		char *pch;

		pch = strtok(lineCopy, ",");
		parameters[0] = atoi(pch);
		
		int j = 1;
		while( j < 5 )
		{
			pch = strtok (NULL, ",");
			parameters[j] = atof(pch);
			j++;
		}
		svmI[size-1] = parameters[0];
		svmA[size-1] = parameters[1];
		svmP[size-1] = parameters[2];
		svmC[size-1] = parameters[3];
		svmE[size-1] = parameters[4];
	}
	fclose(fptrR);
	//---------------------
	// Data for visual representation
    int width = 512, height = 512;
    Mat image = Mat::zeros(height, width, CV_8UC3);

    // Set up training data
    //float labels[8] = {1.0, -1.0, -1.0, -1.0};
	float labels[1000];
	for(int i = 0; i < svmI.size()-1; i++)
	{
		labels[i] = svmI[i+1];
	}
    Mat labelsMat(1000, 1, CV_32FC1, labels);

    float trainingData[1000][4];
	for(int i = 0; i < svmE.size()-1; i++)
	{
		trainingData[i][0] = svmE[i+1];
		trainingData[i][1] = svmC[i+1];
		trainingData[i][2] = svmA[i+1];
		trainingData[i][3] = svmP[i+1];
	}
    Mat trainingDataMat(1000, 4, CV_32FC1, trainingData);

    // Set up SVM's parameters
    CvSVMParams params;
	params = SVMFinger.get_params();
    //params.svm_type    = CvSVM::C_SVC;
    //params.kernel_type = CvSVM::LINEAR;
    //params.term_crit   = cvTermCriteria(CV_TERMCRIT_ITER, 100, 1e-6);

    // Train the SVM
    SVMFinger.train_auto(trainingDataMat, labelsMat, Mat(), Mat(), params);

//	Mat sampleMat = (Mat_<float>(1,2) << 138.5, 57);
//	float response = SVMFinger.predict(sampleMat);

	waitKey();
	destroyWindow("Image");
	destroyWindow("Image2");

	//------------------------------------------
	OpenNI::initialize();

	Device devAnyDevice;
    devAnyDevice.open(ANY_DEVICE);

	//----------------[Define Video Settings]-------------------
	//Set Properties of Depth Stream
	VideoMode mModeDepth;
	mModeDepth.setResolution( 640, 480 );
	mModeDepth.setFps( 30 );
	mModeDepth.setPixelFormat( PIXEL_FORMAT_DEPTH_100_UM );

	//Set Properties of Color Stream
	VideoMode mModeColor;
    mModeColor.setResolution( 640, 480 );
    mModeColor.setFps( 30 );
    mModeColor.setPixelFormat( PIXEL_FORMAT_RGB888 );
	//----------------------------------------------------------
	//----------------------[Initial Streams]---------------------
	VideoStream streamInitDepth;
    streamInitDepth.create( devAnyDevice, SENSOR_DEPTH );

	VideoStream streamInitColor;
    streamInitColor.create( devAnyDevice, SENSOR_COLOR );

	streamInitDepth.setVideoMode( mModeDepth );
	streamInitColor.setVideoMode( mModeColor );

	namedWindow( "Depth Image (Init)",  CV_WINDOW_AUTOSIZE );
    namedWindow( "Color Image (Init)",  CV_WINDOW_AUTOSIZE );
	//namedWindow( "Thresholded Image (Init)", CV_WINDOW_AUTOSIZE );

	VideoFrameRef  frameDepthInit;
    VideoFrameRef  frameColorInit;

	streamInitDepth.start();
	streamInitColor.start();
	cv::Mat BackgroundFrame;

	int avgDist = 0;
	int iMaxDepthInit = streamInitDepth.getMaxPixelValue();
	
	OutX.clear();
	OutY.clear();

	vector<int> OldOutX, OldOutY;
	OldOutX.clear();
	OldOutY.clear();
	//------------------------------------------------------------
	//--------------------[Initiation Process]--------------------
	while( true )
	{
		streamInitDepth.readFrame( &frameDepthInit );
		streamInitColor.readFrame( &frameColorInit );

		const cv::Mat mImageDepth( frameDepthInit.getHeight(), frameDepthInit.getWidth(), CV_16UC1, (void*)frameDepthInit.getData());

        cv::Mat mScaledDepth;
        mImageDepth.convertTo( mScaledDepth, CV_8U, 255.0 / iMaxDepthInit );

        cv::imshow( "Depth Image (Init)", mScaledDepth );

        const cv::Mat mImageRGB(frameColorInit.getHeight(), frameColorInit.getWidth(), CV_8UC3, (void*)frameColorInit.getData());

        cv::Mat cImageBGR;
        cv::cvtColor( mImageRGB, cImageBGR, CV_RGB2BGR );

		//--------------------[Get Average Distance]---------------------
		int depthVal = 0;
		int frameHeight = frameDepthInit.getHeight();
		int frameWidth = frameDepthInit.getWidth();
		//------------
		//backgroundDepth.resize(frameHeight * frameWidth);
		//---------------------------------------------------------------
		
		int initCount = 0;
		for(int i = 0; i < frameHeight; i++)
		{
			for(int j = 0; j < frameWidth; j++)
			{
				depthVal = mImageDepth.at<unsigned short>(i, j) + depthVal;
				initCount++;
			}
		}
		avgDist = depthVal / ((frameHeight) * (frameWidth));

		cout << "Average Distance: " << avgDist << endl;
		cv::imshow( "Color Image (Init)", cImageBGR );

		if( cv::waitKey(1) == 'q')
		{
			mImageDepth.copyTo(BackgroundFrame);
            break;
		}
	}

	streamInitDepth.destroy();
	streamInitColor.destroy();

	destroyWindow( "Depth Image (Init)" );
	destroyWindow( "Color Image (Init)" );

	VideoStream streamDepth;
    streamDepth.create( devAnyDevice, SENSOR_DEPTH );

	VideoStream streamColor;
    streamColor.create( devAnyDevice, SENSOR_COLOR );

	streamDepth.setVideoMode( mModeDepth );
	streamColor.setVideoMode( mModeColor );

	streamDepth.start();
    streamColor.start();

	namedWindow( "Depth Image",  CV_WINDOW_AUTOSIZE );
    namedWindow( "Color Image",  CV_WINDOW_AUTOSIZE );
	namedWindow( "Thresholded Image", CV_WINDOW_AUTOSIZE );

	int iMaxDepth = streamDepth.getMaxPixelValue();

    VideoFrameRef  frameColor;
	VideoFrameRef  frameDepth;

	OutX.clear();
	OutY.clear();
	//------------------------------------------------------------

	//------------------------------------------------------------
	//-----------------------[Main Process]-----------------------
	while( true ) 
    {
        streamDepth.readFrame( &frameDepth );
        streamColor.readFrame( &frameColor );

        const cv::Mat mImageDepth( frameDepth.getHeight(), frameDepth.getWidth(), CV_16UC1, (void*)frameDepth.getData());

        cv::Mat mScaledDepth;
        mImageDepth.convertTo( mScaledDepth, CV_8U, 255.0 / iMaxDepth );

		////////////////////////////////////////////////////////////////////////////////////////////
		//---------------------[Downsampling]-------------------------------------------------------
		double min;
		double max;
		cv::minMaxIdx(mImageDepth, &min, &max);
		cv::Mat adjMap;
		// expand your range to 0..255. Similar to histEq();
		float scale = 255 / (max-min);
		mImageDepth.convertTo(adjMap,CV_8UC1, scale, -min*scale); 

		// this is great. It converts your grayscale image into a tone-mapped one, 
		// much more pleasing for the eye
		// function is found in contrib module, so include contrib.hpp 
		// and link accordingly
		cv::Mat falseColorsMap;
		applyColorMap(adjMap, falseColorsMap, cv::COLORMAP_AUTUMN);

		cv::imshow("Out", falseColorsMap);
		//------------------------------------------------------------------------------------------
		////////////////////////////////////////////////////////////////////////////////////////////

        cv::imshow( "Depth Image", mScaledDepth );
		cv::imshow( "Depth Image2", adjMap );

        const cv::Mat mImageRGB(frameColor.getHeight(), frameColor.getWidth(), CV_8UC3, (void*)frameColor.getData());

        cv::Mat cImageBGR;
        cv::cvtColor( mImageRGB, cImageBGR, CV_RGB2BGR );
		
		//-------------[Threshold]-----------------
		cv::Mat mImageThres( frameDepth.getHeight(), frameDepth.getWidth(), CV_8UC1 );

		int backgroundPxlCount = 0;
		for(int i = 0; i < 480; i++)
		{
			for(int j = 0; j < 640; j++)
			{
				int depthVal = mImageDepth.at<unsigned short>(i, j);

				avgDist = BackgroundFrame.at<unsigned short>(i, j)-2;

				if((depthVal > (avgDist-14)) && (depthVal <= (avgDist-7)))
				{
					//mImageThres.data[mImageThres.step[0]*i + mImageThres.step[1]*j] = 255;
					mImageThres.at<uchar>(i, j) = 255;
				}
				else
				{
					//mImageThres.data[mImageThres.step[0]*i + mImageThres.step[1]*j] = 0;
					mImageThres.at<uchar>(i, j) = 0;
				}

				backgroundPxlCount++;
			}
		}
		GaussianBlur( mImageThres, mImageThres, Size(3,3), 0, 0 );
		
		fingerDetection( mImageThres, cImageBGR, OldOutX, OldOutY);

		cv::imshow("Thresholded Image", mImageThres);
		//----------------------------------------
        if( cv::waitKey(1) == 'q')
		{
            break;
		}
		//------------------------------------------------
		cv::imshow( "Color Image", cImageBGR );
		//----------------------------------
		OldOutX.clear();
		OldOutY.clear();
		OldOutX = OutX;
		OldOutY = OutY;
		OutX.clear();
		OutY.clear();
    }

	return 0;
}
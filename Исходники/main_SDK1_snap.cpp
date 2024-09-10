int  main()
{
	int width;
	char* bayer[] = {"RG","BG","GR","GB"};
	char* controls[MAX_CONTROL] = {"Exposure", "Gain", "Gamma", "WB_R", "WB_B", "Brightness", "USB Traffic"};

	int height;
	int i;
	char c;
	bool bresult;

	int time1,time2;
	int count=0;

	char buf[128]={0};

	int CamNum=0;
	
	///long exposure, exp_min, exp_max, exp_step, exp_flag, exp_default;
	//long gain, gain_min, gain_max,gain_step, gain_flag, gain_default;

	IplImage *pRgb;


	int numDevices = getNumberOfConnectedCameras();
	if(numDevices <= 0)
	{
		printf("no camera connected, press any key to exit\n");
		getchar();
		return -1;
	}
	else
		printf("attached cameras:\n");

	for(i = 0; i < numDevices; i++)
		printf("%d %s\n",i, getCameraModel(i));

	printf("\nselect one to privew\n");
	scanf("%d", &CamNum);


	bresult = openCamera(CamNum);
	if(!bresult)
	{
		printf("OpenCamera error,are you root?,press any key to exit\n");
		getchar();
		return -1;
	}

	printf("%s information\n",getCameraModel(CamNum));
	int iMaxWidth, iMaxHeight;
	iMaxWidth = getMaxWidth();
	iMaxHeight =  getMaxHeight();
	printf("resolution:%dX%d\n", iMaxWidth, iMaxHeight);
	if(isColorCam())
		printf("Color Camera: bayer pattern:%s\n",bayer[getColorBayer()]);
	else
		printf("Mono camera\n");
	
	for( i = 0; i < MAX_CONTROL; i++)
	{
			if(isAvailable((Control_TYPE)i))
				printf("%s support:Yes\n", controls[i]);
			else
				printf("%s support:No\n", controls[i]);
	}



	initCamera(); //this must be called before camera operation. and it only need init once
	printf("sensor temperature:%02f\n", getSensorTemp());

	int bin = 1, Image_type;
	
	do{
		printf("\nPlease input the <width height bin image_type> with one space, ie. 640 480 2 0. use max resolution if input is 0. Press ESC when video window is focused to quit capture\n");

		scanf("%d %d %d %d", &width, &height, &bin, &Image_type);
		if(width == 0 || height == 0)
		{
			width = iMaxWidth;
			height = iMaxHeight;
		}

	}
	while(!setImageFormat(width, height, bin, (IMG_TYPE)Image_type));//IMG_RAW8
	
	printf("\nset image format %d %d %d %d success, start privew, press ESC to stop \n", width, height, bin, Image_type);

	
	if(Image_type == IMG_RAW16)
		pRgb=cvCreateImage(cvSize(getWidth(),getHeight()), IPL_DEPTH_16U, 1);
	else if(Image_type == IMG_RGB24)
		pRgb=cvCreateImage(cvSize(getWidth(),getHeight()), IPL_DEPTH_8U, 3);
	else
		pRgb=cvCreateImage(cvSize(getWidth(),getHeight()), IPL_DEPTH_8U, 1);

	int exp_ms;
	printf("Please input exposure time(ms)\n");
	scanf("%d", &exp_ms);
	setValue(CONTROL_EXPOSURE, exp_ms*1000, false); //ms//auto
	setValue(CONTROL_GAIN,getMin(CONTROL_GAIN), false); 
	setValue(CONTROL_BANDWIDTHOVERLOAD, getMin(CONTROL_BANDWIDTHOVERLOAD), false); //low transfer speed

	setValue(CONTROL_WB_B, 90, false);
 	setValue(CONTROL_WB_R, 48, false);
  	setAutoPara(getMax(CONTROL_GAIN)/2,10,150); //max auto gain and exposure and target brightness


	bDisplay = 1;
#ifdef _LIN
	pthread_t thread_display;
	pthread_create(&thread_display, NULL, Display, (void*)pRgb);
#elif defined _WINDOWS
	HANDLE thread_setgainexp;
	thread_setgainexp = (HANDLE)_beginthread(Display,  NULL, (void*)pRgb);
#endif

	time1 = GetTickCount();
	int iStrLen = 0, iTextX = 40, iTextY = 60;
	void* retval;

	EXPOSURE_STATUS status;
	while(bMain)
	{


		startExposure();
		usleep(10000);//10ms
		status = EXP_WORKING;
		while(status == EXP_WORKING)
		{
			 status = getExpStatus();
				
		}
		if(status == EXP_SUCCESS)
			getImageAfterExp((unsigned char*)pRgb->imageData, pRgb->imageSize);
		
		time2 = GetTickCount();

		count++;
		
		if(time2-time1 > 1000 )
		{
			sprintf(buf, "fps:%d dropped frames:%lu ImageType:%d",count, getDroppedFrames(), (int)getImgType());

			count = 0;
			time1=GetTickCount();	
			printf(buf);
			printf("\n");

		}
		if(Image_type != IMG_RGB24 && Image_type != IMG_RAW16)
		{
			iStrLen = strlen(buf);
			CvRect rect = cvRect(iTextX, iTextY - 15, iStrLen* 11, 20);
			cvSetImageROI(pRgb , rect);
			cvSet(pRgb, CV_RGB(180, 180, 180)); 
			cvResetImageROI(pRgb);
		}
		cvText(pRgb, buf, iTextX,iTextY );

		if(bChangeFormat)
		{
			bChangeFormat = 0;
			bDisplay = false;
			pthread_join(thread_display, &retval);
			cvReleaseImage(&pRgb);

			
			switch(change)
			{
				 case change_imagetype:
					Image_type++;
					if(Image_type > 3)
						Image_type = 0;
					
					break;
				case change_bin:
					if(bin == 1)
					{
						bin = 2;
						width/=2;
						height/=2;
					}
					else 
					{
						bin = 1;
						width*=2;
						height*=2;
					}
					break;
				case change_size_smaller:
					if(width > 320 && height > 240)
					{
						width/= 2;
						height/= 2;
					}
					break;
				
				case change_size_bigger:
				
					if(width*2*bin <= iMaxWidth && height*2*bin <= iMaxHeight)
					{
						width*= 2;
						height*= 2;
					}
					break;
			}
			setImageFormat(width, height, bin, (IMG_TYPE)Image_type);
			if(Image_type == IMG_RAW16)
				pRgb=cvCreateImage(cvSize(getWidth(),getHeight()), IPL_DEPTH_16U, 1);
			else if(Image_type == IMG_RGB24)
				pRgb=cvCreateImage(cvSize(getWidth(),getHeight()), IPL_DEPTH_8U, 3);
			else
				pRgb=cvCreateImage(cvSize(getWidth(),getHeight()), IPL_DEPTH_8U, 1);
			bDisplay = 1;
			pthread_create(&thread_display, NULL, Display, (void*)pRgb);

		}
	}
END:
	
	if(bDisplay)
	{
		bDisplay = 0;
#ifdef _LIN
   		pthread_join(thread_display, &retval);
#elif defined _WINDOWS
		Sleep(50);
#endif
	}
	
	stopCapture();
	closeCamera();
	cvReleaseImage(&pRgb);
	printf("main function over\n");
	return 1;
}
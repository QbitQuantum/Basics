int main(int argc, char *argv[])
{
	Win32LoadOpenCv();
	
	CvMat *imageLeft = OpenCvImreadM("images/obstacles_0stereo.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	CvMat *imageRight = OpenCvImreadM("images/obstacles_10stereo.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	
	if((imageLeft == 0) || (imageRight == 0))
	{
		printf_s("One or more images failed to load \n");
		return -1;
	}
	
	CvMat *imageDisparity16S = OpenCvCreateMat(imageLeft->rows, imageLeft->cols,
		CV_16S); // CvMat{imageLeft->rows, CV_16S};
	CvMat *imageDisparity8U = OpenCvCreateMat(imageLeft->rows, imageLeft->cols,
		CV_8UC1); // CvMat(imageLeft->rows, CV_8UC1);
	
	int32 disparities = 112;
	CvStereoBMState *stereoBMState = OpenCvCreateStereoBMState(CV_STEREO_BM_BASIC,
		disparities);
	stereoBMState->SADWindowSize = 9;
	stereoBMState->preFilterSize = 5;
	stereoBMState->preFilterCap = 61;
	stereoBMState->minDisparity = -39;
	stereoBMState->textureThreshold = 507;
	stereoBMState->uniquenessRatio = 0;
	stereoBMState->speckleWindowSize = 0;
	stereoBMState->speckleRange = 8;
	stereoBMState->disp12MaxDiff = 1;
	
	for(int i = 1;
		i < 4;
		i = i + 2)
	{
		OpenCvSmooth(imageLeft, imageLeft, CV_BLUR, i, i, 3, 3);
	}
	for(int i = 1;
		i < 4;
		i = i + 2)
	{
		OpenCvSmooth(imageRight, imageRight, CV_BLUR, i, i, 3, 3);
	}
	
	OpenCvFindStereoCorrespondenceBM(imageLeft, imageRight,
			imageDisparity16S, stereoBMState);
		
	double minValue;
	double maxValue;
	OpenCvMinMaxLoc(imageDisparity16S, &minValue, &maxValue, 0, 0, 0);
	
	printf_s("Min disparity: %f - Max disparity: %f \n",
		minValue, maxValue);
		
	OpenCvConvertScale(imageDisparity16S, imageDisparity8U,
		255.0/(maxValue - minValue), 0);
		
	// OpenCvNamedWindow(g_WindowName, CV_WINDOW_AUTOSIZE);
	// OpenCvShowImage(g_WindowName, imageDisparity8U);
	
	OpenCvSaveImage("../matlab/disparityMap.bmp", imageDisparity8U, 0);
	
	OpenCvWaitKey(0);
	
	OpenCvReleaseStereoBMState(&stereoBMState);
	
	return 0;
}
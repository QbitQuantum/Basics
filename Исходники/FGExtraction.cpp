/*******************************************************************************
* Function:      extractFGTargets  
* Description:   extract FG targets with given conditions and return objects
* Arguments:
	inImg           -   input image
	fgImg           -   output FG mask image
	seLength        -   length of structuring elements (opening)
	threshVal       -   threshold value for converting to binary image
	minArea         -   minimum area of FG targets
	maxArea         -   maximum area of FG targets
	minAspRatio     -   minimum aspect ratio of FG targets
	maxAspRatio     -   maximum aspect ratio of FG targets
	
* Returns:       vector<FGObject>* - all extracted FG targets
* Comments:
* Revision: 
*******************************************************************************/
vector<FGObject>*
FGExtraction::extractFGTargets(InputArray inImg, OutputArray fgImg, int seLength, int threshVal, 
                                   double minArea, double maxArea, 
								   double minAspRatio, double maxAspRatio)
{
	double theta = 0.4;

	if(!inImg.obj) return NULL;

	_inImg = inImg.getMat();
	this->init();

	//showImage("inImg", _inImg);

	// background subtraction by opening
    int err = subtractBGOpenDiagonal(inImg, _bgsImg, threshVal, seLength);

	if (err>0) {
		vector<FGObject>* fgObjects = new vector<FGObject>;
		return fgObjects;
	}

	//subtractBGMedian(inImg.getMat(), bgSubImg, threshVal, seLength);
	//showImage("inImg", _inImg, 0, 1);
	//showImage("bgSub", _bgsImg);
	
    // get the contour
    vector<vector<Point>> contours = extractContours(_bgsImg);
	//cout<<contours.size()<<endl;

    // double local thresholding
    // histogram backprojection
    Mat mask = Mat::zeros(_bgsImg.size(), CV_8U); 
	vector<int> areas(contours.size());
	int cnt = 0;
	int argMax = 0;
	int max_area = 0;
    for(vector<vector<Point> >::const_iterator it = contours.begin(); it != contours.end(); ++it){
        Rect uprightBox = boundingRect(*it);
		areas[cnt] = uprightBox.height*uprightBox.width;
		if (areas[cnt]>max_area) {
			max_area = areas[cnt];
			argMax = cnt;
		}
		cnt++;
	}
	//showImage("inImg", _inImg, 0, 1);

	vector<Point> largestContour = contours[argMax];	//***** only use the largest contour
		RotatedRect orientedBox = orientedBoundingBox(largestContour);
		orientedBox.size.width *= 1.5;
        orientedBox.size.height *= 1.5;
		ellipse(mask, orientedBox, Scalar(255), -1);

		//Rect tempRect = boundingRect(largestContour);
		//Mat tempImg = mask(tempRect);
		//imshow("tempImg", tempImg);
		//imshow("mask", mask);
		//waitKey(0);

		// double local thresholding
		double percentage = 0.8;
		doubleThresholdByValue(percentage, mask);
		
		/*finish = clock();
		duration = (double)(finish - start) / (double)CLOCKS_PER_SEC;
		cout << duration << " sec" << endl;
		start = clock();*/

		// remove noise by a median filter
		medianBlur(_fgHighImg, _fgHighImg, 3);
		medianBlur(_fgLowImg, _fgLowImg, 3);
		//showImage("_fgHighImg", _fgHighImg);
		//showImage("_fgLowImg", _fgLowImg);

		/*finish = clock();
		duration = (double)(finish - start) / (double)CLOCKS_PER_SEC;
		cout << duration << " sec" << endl;
		
		start = clock();*/
		// merge two masks using histogram backprojection
		//showImage("_fgImg", _fgImg);
		//showImage("mask", mask);
		updateByHistBackproject(theta, mask);
		

		ellipse(mask, orientedBox, Scalar(0), -1);
		ellipse(_fgHighImg, orientedBox, Scalar(0), -1);
		ellipse(_fgLowImg, orientedBox, Scalar(0), -1);

    //}

	
    // thresholding by area and variance
#ifdef IMAGE_DOWNSAMPLING
	int dilateSESize = 3;
	int erodeSESize = 3;
	int varThresh = 30;
#else
	int dilateSESize = 7;
	int erodeSESize = 7;
	int varThresh = 30;
#endif

    //showImage("fg high", _fgHighImg, 0, 1);
    //showImage("fg low", _fgLowImg, 0, 1);
	//showImage("after histbp", _fgImg, 0);

	thresholdByAreaRatioVar(minArea, maxArea, dilateSESize, erodeSESize, minAspRatio, maxAspRatio, varThresh);
	
	//showImage("after area threshold", _fgImg, 0);

	// post-processing
    postProcessing(_fgImg, _fgImg);
	//imshow("_fgImg",_fgImg);
	//waitKey(0);

	// fill the holes of the fgImg
	_fgImg.copyTo(fgImg);
	floodFill(fgImg, cv::Point(0,0), Scalar(255));
	//imshow("fgImg",fgImg);
	//waitKey(0);

    bitwise_not(fgImg, fgImg);
	bitwise_or(fgImg, _fgImg, _fgImg);
	//imshow("inImg", inImg);
	//imshow("_fgImg",_fgImg);
	//waitKey(0);

	// opening
	RotatedRect rotatedR = fitEllipse(Mat(largestContour));
	float objHeight = min(rotatedR.size.height,rotatedR.size.width);
	int seSize = int(objHeight/10.0+0.5);
	
	Mat se = getStructuringElement(MORPH_ELLIPSE, Size(seSize, seSize));		//***** choose different size according to object height
	morphologyEx(_fgImg, _fgImg, MORPH_OPEN, se);

	//imshow("_fgImg",_fgImg);
	//waitKey(0);


	// close
	morphologyEx(_fgImg, _fgImg, MORPH_CLOSE, se);

	// timer
	/*clock_t start, finish;
	double duration = 0.0;
	start = clock();

	finish = clock();
	duration = (double)(finish - start) / (double)CLOCKS_PER_SEC;
	cout << duration << " sec" << endl;*/

	thresholdByAreaRatioVar(0.5*minArea, maxArea, 1, 1, minAspRatio, maxAspRatio, 30);

	// push targets into our vector
	//Mat largeInImg;
#ifdef IMAGE_DOWNSAMPLING
	resize(_fgImg, _fgImg, Size(), 2, 2, INTER_LINEAR);
	resize(_inImg, largeInImg, Size(), 2, 2, INTER_LINEAR);
#endif
	//tempImg = _fgImg.clone(); 
	//findContours(tempImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	//tempImg.release();

	//imshow("_fgImg",_fgImg);
	//waitKey(0);
	contours = extractContours(_fgImg);

	vector<FGObject>* fgObjects = new vector<FGObject>;
	//Mat mask8U = Mat::zeros(largeInImg.size(), CV_8U); 
	for (size_t i = 0; i < contours.size(); i++){
		double area = contourArea(contours[i]);
		RotatedRect orientedRect = orientedBoundingBox(contours[i]);
		Point2f points[4];
		orientedRect.points(points);
		/*
		orientedRect.size.width *= 1.5;
        orientedRect.size.height *= 1.5;
		ellipse(mask8U, orientedRect, Scalar(255), -1);
		
		int channels[] = {0};
		int nbins = 16;
		const int histSize[] = {nbins};
		float range[] = {0, 255};
		const float* ranges[] = {range};
		Mat hist;
		cv::calcHist(&largeInImg, 1, channels, mask8U, hist, 1, histSize, ranges);
		*/
		// push targets into our vector
		FGObject* obj = new FGObject;
		//obj->histogram = hist;
		obj->setObjectProperties(area, orientedRect.angle, contours[i], points, SOURCE_UNRECTIFIED);

		if(obj->isPartialOut(_fgImg.cols, _fgImg.rows) == false){
			fgObjects->push_back(*obj);
		}
		delete obj;

		//ellipse(mask8U, orientedRect, Scalar(0), -1);
		
	}

	//  eliminate artifacts with width of 1 at the border...
	rectangle(_fgImg, Point(0,0), Point(_fgImg.cols-1, _fgImg.rows-1), Scalar(0));
	
	fgImg.getMatRef() = _fgImg.clone();
	return fgObjects;
}
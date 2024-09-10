int main(int argc, char* argv[])
{
	CvCapture* capture = 0;
	Mat frame, frameCopy, image;
	char c;
	vector <Rect> roi;
	VideoCapture cap(0); // open the default camera

	if (!cap.isOpened())  {
		cout << "Error:" << endl;
	}
		// check if we succeeded
	namedWindow("result");
	 char TrackbarName[50];
	sprintf( TrackbarName, "Red max %d", red_t_max );
	createTrackbar( TrackbarName, "result", &red_t_max, 70, on_trackbar );
	sprintf( TrackbarName, "Red min %d", red_t_min );
	createTrackbar( TrackbarName, "result", &red_t_min, 70, on_trackbar );

	sprintf( TrackbarName, "Blue max %d", blue_t_max );
	createTrackbar( TrackbarName, "result", &blue_t_max, 70, on_trackbar );
	sprintf( TrackbarName, "Blue min %d", blue_t_min );
		createTrackbar( TrackbarName, "result", &blue_t_min, 70, on_trackbar );

	sprintf( TrackbarName, "Green max %d", green_t_max );
	createTrackbar( TrackbarName, "result", &green_t_max, 70, on_trackbar );
	sprintf( TrackbarName, "Green min %d", green_t_min );
	createTrackbar( TrackbarName, "result", &green_t_min, 70, on_trackbar );

	int count = 0;
	bool filter = false;
	cv::Scalar total_mean[POINTS];
	 namedWindow("Frame");
	 namedWindow("Background");
	 BackgroundSubtractorMOG2 bg;
	 bg.set("nmixtures",3);
	 bg.set("detectShadows",false);
	// namedWindow("FG Mask MOG 2");


	//cap >> frame;

	//namedWindow("filtered");
	 int background = 500;
	 Mat fore;
	 Mat back;
	for (;;)
	{
		cap >> frame;
		if(background>0)
				{
			bg.operator ()(frame,fore);background--;
				}
				else
				{
					putText(frame,"Ready",Point(10,20),FONT_HERSHEY_PLAIN,1,Scalar(0,0,0));
					filter = true;

					bg.operator()(frame,fore,0);
				}
		bg.getBackgroundImage(back);
		erode(fore,fore,Mat());
				dilate(fore,fore,Mat());
		imshow("Frame",frame);
		imshow("Background",back);
		imshow("Forground",fore);
		//cout<< background << endl;
		/* pMOG->operator()(frame, fgMaskMOG);
			 pMOG2->operator()(frame, fgMaskMOG2);
		 imshow("Frame", frame);
		  imshow("FG Mask MOG", fgMaskMOG);
		  imshow("FG Mask MOG 2", fgMaskMOG2);*/
	//	flip(frame,frameCopy,1);
		//imshow("result", frame);
	//	imshow("result2", frameCopy);
		if (filter) {
			//Mat dst;


		/*	Scalar lowerBound=Scalar( total_mean[0][0] -red_t_min , total_mean[0][1] -green_t_min, total_mean[0][2] - blue_t_min );
			Scalar upperBound=Scalar( total_mean[0][0] + red_t_max , total_mean[0][1] + green_t_max, total_mean[0][2] + blue_t_max );
			Mat dst;
			inRange(frame, lowerBound, upperBound, dst);
			for(int i =1; i < POINTS; i ++) {
				Scalar lowerBound=Scalar( total_mean[i][0] - red_t_min , total_mean[i][1] - green_t_min, total_mean[i][2] - blue_t_min );
				Scalar upperBound=Scalar( total_mean[i][0] + red_t_max , total_mean[i][1] + green_t_max, total_mean[i][2] + blue_t_max );
				Mat tmp;
				inRange(frame, lowerBound, upperBound, tmp);
				dst+=tmp;
			}
			medianBlur(dst, dst,7);
			imshow("result2", dst);
			pyrUp(dst,dst);

*/
			findContours(fore,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
			hullI=vector<vector<int> >(contours.size());
			hullP=vector<vector<Point> >(contours.size());
			defects=vector<vector<Vec4i> > (contours.size());
			//cout << " We found: " << contours.size() << endl;
			int indexOfBiggestContour = -1;
			int sizeOfBiggestContour = 0;
			for (int i = 0; i < contours.size(); i++){
				if(contours[i].size() > sizeOfBiggestContour){
					sizeOfBiggestContour = contours[i].size();
					indexOfBiggestContour = i;
				}
			}
			if(sizeOfBiggestContour < 300)
				continue;
			cout << "Size: " << sizeOfBiggestContour << endl;
			cIdx = indexOfBiggestContour;
			 bRect = boundingRect(Mat(contours[indexOfBiggestContour]));
			 bRect_height=bRect.height;
			 	bRect_width=bRect.width;
			convexHull(Mat(contours[indexOfBiggestContour]),hullP[indexOfBiggestContour],false,true);
			convexHull(Mat(contours[indexOfBiggestContour]),hullI[indexOfBiggestContour],false,false);
			approxPolyDP( Mat(hullP[indexOfBiggestContour]), hullP[indexOfBiggestContour], 18, true );
			if(contours[indexOfBiggestContour].size()>3 ){

				convexityDefects(contours[indexOfBiggestContour],hullI[indexOfBiggestContour],defects[indexOfBiggestContour]);
			    eleminateDefects(&fore);
			}
			getFingerTips(frame);
			bool isHand=detectIfHand();
			rectangle(frame,bRect,cv::Scalar(200,0,0));
			drawContours(frame,hullP,cIdx,cv::Scalar(200,0,0),2, 8, vector<Vec4i>(), 0, Point());
					if(isHand){
					//	getFingerTips(frame);
						drawFingerTips(frame);
					//	myDrawContours(frame);
					}

		}
		/*Scalar color = Scalar(0, 255, 0);
		roi.push_back(Rect(Point(frame.cols / 3, frame.rows / 6), Point(frame.cols / 3 + 20, frame.rows / 6 + 20)));
		roi.push_back(Rect(Point(frame.cols / 4, frame.rows / 2), Point(frame.cols / 4 + 20, frame.rows / 2 + 20)));
		roi.push_back(Rect(Point(frame.cols / 3, frame.rows / 1.5), Point(frame.cols / 3 + 20, frame.rows / 1.5 + 20)));
		roi.push_back(Rect(Point(frame.cols / 2, frame.rows / 2), Point(frame.cols / 2 + 20, frame.rows / 2 + 20)));
		roi.push_back(Rect(Point(frame.cols / 2.5, frame.rows / 2.5), Point(frame.cols / 2.5 + 20, frame.rows / 2.5 + 20)));
		roi.push_back(Rect(Point(frame.cols / 2, frame.rows / 1.5), Point(frame.cols / 2 + 20, frame.rows / 1.5 + 20)));
		roi.push_back(Rect(Point(frame.cols / 2.5, frame.rows / 1.8), Point(frame.cols / 2.5 + 20, frame.rows / 1.8 + 20)));
		rectangle(frame, roi[0], color, 2);
		rectangle(frame,roi[1] , color, 2);
		rectangle(frame, roi[2], color, 2);
		rectangle(frame, roi[3], color, 2);
		rectangle(frame, roi[4], color, 2);
		rectangle(frame, roi[5], color, 2);
		rectangle(frame, roi[6], color, 2);*/

		std::string win = "majd";
		imshow(win, frame);
		//imshow("faaa",frame);

		/*roi.push_back(My_ROI(Point(m->src.cols / 3, m->src.rows / 6), Point(m->src.cols / 3 + square_len, m->src.rows / 6 + square_len), m->src));
		roi.push_back(My_ROI(Point(m->src.cols / 4, m->src.rows / 2), Point(m->src.cols / 4 + square_len, m->src.rows / 2 + square_len), m->src));
		roi.push_back(My_ROI(Point(m->src.cols / 3, m->src.rows / 1.5), Point(m->src.cols / 3 + square_len, m->src.rows / 1.5 + square_len), m->src));
		roi.push_back(My_ROI(Point(m->src.cols / 2, m->src.rows / 2), Point(m->src.cols / 2 + square_len, m->src.rows / 2 + square_len), m->src));
		roi.push_back(My_ROI(Point(m->src.cols / 2.5, m->src.rows / 2.5), Point(m->src.cols / 2.5 + square_len, m->src.rows / 2.5 + square_len), m->src));
		roi.push_back(My_ROI(Point(m->src.cols / 2, m->src.rows / 1.5), Point(m->src.cols / 2 + square_len, m->src.rows / 1.5 + square_len), m->src));
		roi.push_back(My_ROI(Point(m->src.cols / 2.5, m->src.rows / 1.8), Point(m->src.cols / 2.5 + square_len, m->src.rows / 1.8 + square_len), m->src));
		*/
		c = waitKey(10);
		if (c == 'q') {
			return 0;
		}

	//	c = 'a';
		if (c == 'a') {
			//Mat tst = frame(roi[0]);
			//total_mean = cv::mean(tst);;


		   filter = true;


		}
	}
	return 0;
}
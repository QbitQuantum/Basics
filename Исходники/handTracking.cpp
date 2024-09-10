int main(int argc, char* argv[])
{

	VideoCapture cap1(0);
	
	if(!cap1.isOpened())
	{
		cout << "Cannot read the camera feed!" << endl;
		return -1;
	}

	Mat frame, back, fore;
	Ptr<BackgroundSubtractorMOG2> bg = new BackgroundSubtractorMOG2();
	namedWindow("Original");
    namedWindow("Background");

    vector<vector<Point> > contours;
    vector<Point> hand;

	while(1)
	{
		cap1.read(frame);
		bg->operator () (frame,fore);
		bg->getBackgroundImage(back);

		erode(fore,fore,Mat());
        dilate(fore,fore,Mat());
        findContours(fore,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
	        
        int largestArea = 0, largestIndex;
    	Rect bounding_rect;
    	vector<vector<Point> > hull(contours.size());

        for (int i = 0;i < contours.size();i++)
    	{
    		double a = contourArea(contours[i],false);
    		if (a > largestArea)
    		{
    			largestArea = a;
    			bounding_rect = boundingRect(contours[i]);
    			largestIndex = i;
    			convexHull(contours[i],hull[i]);
    		}
    	}

        
        drawContours(frame,hull,largestIndex,Scalar(0,0,255),2);        
    	rectangle(frame, bounding_rect,  Scalar(0,255,0),1, 8,0);

		// Mat object = backgroundSubtraction(frame1,frame2);
		imshow("Original",frame);
		imshow("Background",back);
		

		if(waitKey(100) == 27)
        {
            cout << "ESC is pressed!" << endl;
            break;
        }
	}

	return 0;		
}
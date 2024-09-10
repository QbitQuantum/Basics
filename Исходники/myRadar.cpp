// display function should be good enough
void OpenRadar::DrawRadarData()
{
	int usualColor[15] = {16777215,255,128,65280,32768,
		      16711680,16711935,8421376,65535,32896 }; /*<usual color*/
	CvPoint pt1, pt2;

	cvZero(RadarImage);
	cvCircle(RadarImage, cvPoint(DisplayDx,DisplayDy),3, CV_RGB(0,255,255), -1, 8,0);
	int x,y;
	unsigned char * pPixel = 0;
	int colorIndex = 0, colorRGB;
	int R = 255, G = 0, B = 0;
    
	for (int i = 0; i < RadarDataCnt;i++)
	{  
		if (RadarRho[i] < 0)
		{
			
			//change color
			colorRGB = usualColor[colorIndex];
			R = colorRGB/65536;
			G = (colorRGB%65536)/256;
			B = colorRGB%256;
			colorIndex = (colorIndex + 1)%10;
			
		}
		else 
		{
			x = (int)(RadarRho[i]*cos(RadarTheta[i])/DisplayRatio) + DisplayDx;
			y = (int)(-RadarRho[i]*sin(RadarTheta[i])/DisplayRatio)+ DisplayDy;
	
			if (x >= 0 && x < RadarImageWdith && y >= 0 && y < RadarImageHeight)
			{
				pPixel = (unsigned char*)RadarImage->imageData + y*RadarImage->widthStep + 3*x;
				pPixel[0] = B;
				pPixel[1] = G;
				pPixel[2] = R;
			}
		}     
	}
	
	pt1.x = DisplayDx; pt1.y = DisplayDy;
	pt2.x = DisplayDx+line_length*v_scale*sin(v_angle + 0.5*M_PI); 
	pt2.y = DisplayDy+line_length*v_scale*cos(v_angle + 0.5*M_PI);
	cvLine(RadarImage, pt1, pt2, CV_RGB(255,255,255),2,8,0);

	pt2.x = DisplayDx+line_length*cos(-(-120 + skip_bin_idx * polarH_resolution)* M_PI/180 ); 	
	pt2.y = DisplayDy+line_length*sin(-(-120 + skip_bin_idx * polarH_resolution)* M_PI/180 ); 
	cvLine(RadarImage, pt1, pt2, CV_RGB(0,255,0),1,8,0);

	pt2.x = DisplayDx+line_length*cos(-(-120 + (polarH_length-skip_bin_idx) * polarH_resolution)* M_PI/180 ); 
	pt2.y = DisplayDy+line_length*sin(-(-120 + (polarH_length-skip_bin_idx) * polarH_resolution)* M_PI/180 ); 
	//pt2.x = DisplayDx+line_length*cos(0.25*M_PI); 
	//pt2.y = DisplayDy+line_length*sin(0.25*M_PI);
	//cout<< line_length <<endl; 
	//cout<< pt1.x <<" , " << pt1.y <<endl;
	//cout<< pt2.x <<" , " << pt2.y <<endl;
	cvLine(RadarImage, pt1, pt2, CV_RGB(0,255,0),1,8,0);

	float angle;
	int line_length2;
	for (int i=0; i<polarH_length;i++)
	{
		angle = (-30+i*polarH_resolution)*M_PI/180;
		line_length2 = H[i]/10;
		pt2.x = DisplayDx+line_length2*sin(angle); 
		pt2.y = DisplayDy+line_length2*cos(angle);
		cvCircle(RadarImage, pt2, 2, CV_RGB(255,255,255),1,8,0);
	}

	////////////////////////////////////////////////////////////////////////////////////
	// mine
	////////////////////////////////////////////////////////////////////////////////////
	Mat binImg = Mat::zeros(RadarImageHeight,RadarImageWdith,CV_8UC1);
	vector< Point> centerRaw;
	centerRaw.clear();
	for (int i = 0; i < RadarDataCnt;i++)
	{  
		if (RadarRho[i] > 200)
		{
			x = (int)(RadarRho[i]*cos(RadarTheta[i])/DisplayRatio) + DisplayDx;
			y = (int)(-RadarRho[i]*sin(RadarTheta[i])/DisplayRatio)+ DisplayDy;
			//centerRaw.push_back(Point(x,y));
			//cout<<"P:" <<centerRaw[i].x<<","<<centerRaw[i].y<<endl;
			if (x >= 0 && x < RadarImageWdith && y >= 0 && y < RadarImageHeight)
			{
				 circle( binImg,Point(x,y),1,Scalar(255),-1);
			}
		}     
	}
	imshow("binImg",binImg);
	Mat element = getStructuringElement(MORPH_RECT, Size(1,2));
	Mat element2 = getStructuringElement(MORPH_RECT, Size(10,10));
	erode(binImg, binImg, element);
	morphologyEx(binImg, binImg, MORPH_OPEN, element);
	dilate(binImg, binImg, element2);
	morphologyEx(binImg, binImg, MORPH_CLOSE, element2);
	imshow("dilate",binImg);

	vector< vector<Point> > contours;	
	vector< vector<Point> > filterContours;	
	vector< Vec4i > hierarchy;	
	vector< Point2f> center;
	vector< float > radius;
	vector<Point2f> realPoint;
	

	findContours(binImg, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	center.resize(contours.size());
	radius.resize(contours.size());
	//realPoint.resize(contours.size());
	for(int i = 0; i< contours.size(); i++)
	{
		minEnclosingCircle(Mat(contours[i]),center[i],radius[i]);//对轮廓进行多变形逼近
		circle(binImg,center[i],650/DisplayRatio,Scalar(255),1); 
		//cout<<"No."<<i<<" | P: "<< center[i].x<<","<<center[i].y<<endl;
		float realX = (center[i].x - DisplayDx) * DisplayRatio;
		float realY = (center[i].y - DisplayDy) * DisplayRatio;

		realPoint.push_back(Point2f(realX,realY));
		//cout<<"No."<<i<<" | P: "<< realPoint[i].x<<","<<realPoint[i].y<<endl;
	}
	imshow("findContours",binImg);
	// colar map
	Mat mapImg = Mat::zeros(RadarImageHeight,RadarImageWdith,CV_8UC3);
	circle(mapImg, Point(DisplayDx,DisplayDy),3, CV_RGB(255,255,255),-1);
	line(mapImg, Point(DisplayDx,DisplayDy), Point(DisplayDx+40,DisplayDy), Scalar(0,0,255),1);
	line(mapImg, Point(DisplayDx,DisplayDy), Point(DisplayDx,DisplayDy+40), Scalar(0,255,0),1);
	for(int i = 0; i< center.size(); i++)
	{
		circle(mapImg,center[i],650/DisplayRatio,Scalar(255,255,0),1,CV_AA); 
		circle(mapImg,center[i],100/DisplayRatio,Scalar(0,255,255),-1); 
	}
	imshow("Map",mapImg);
	////////////////////////////////////
	ukftest::laserPoint msg;
	vector <float> xvec;
	vector <float> yvec;
	for(int i = 0 ; i < realPoint.size(); i++)
	{
		// cm
		xvec.push_back(realPoint[i].x/10.0f);
		yvec.push_back(realPoint[i].y/10.0f);
	}

	// msg
	msg.header.stamp = ros::Time::now();
	msg.header.frame_id = "hokuyo_laser";
	msg.x =xvec;
	msg.y =yvec;
	if(realPoint.size() >0) msg.isBlocking = 1;
	else msg.isBlocking = 0;
	pub_xy. publish(msg);
	
}
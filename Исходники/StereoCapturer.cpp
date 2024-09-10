void StereoCapturer::computeStereo(float dt, bool display, bool save_Rectified){

	double min, max;
	cv::Mat imgD,imgD2;
	int i,w,h;
	char buffer[255];


	if(intrinsics.empty()||extrinsics.empty()){
		cerr<< "Missing intrinsic and extrinsic file, file paths required at constructor"<<endl;
		return;
	}

	while(true){
		if(current > finish){
			cout<<"End of frames"<<endl;
			return;
		}

		sprintf(buffer,"%s%i.%s",loadS1.data(),current,ext1.data());
		imgLeft = cv::imread(buffer,0);							//left Image
		if(imgLeft.data == NULL){
			cout<< "image "<< buffer<<" not found"<<endl;
			return;
		}

		sprintf(buffer,"%s%i.%s",loadS2.data(),current,ext2.data());
		imgRight = cv::imread(buffer,0);							//Right Image
		if(imgRight.data == NULL){
			cout<< "image "<< buffer<<" not found"<<endl;
			return;
		}


		cout<<"Read image "<<loadS1.data()<<current<<endl;

		boost::posix_time::ptime startTime, stopTime;


		startTime = boost::posix_time::microsec_clock::local_time();
		computeDisparity(imgDepth);
		stopTime = boost::posix_time::microsec_clock::local_time();
		boost::posix_time::time_duration dur = stopTime - startTime;
		double milliseconds = dur.total_milliseconds();
		cout<<"Time Passed "<<milliseconds<<" Milli seconds"<<endl;

		cout<<(int)imgDepth.step1(1)<<endl;

		cv::minMaxIdx(imgDepth, &min, &max);
		cout<<min<<"    "<<max<<endl;
		cout<<255 / (max-min)<<endl;
		cv::normalize(imgDepth,imgD,0, 255,NORM_MINMAX,CV_8UC1);
		cv::minMaxIdx(imgD, &min, &max);
		cout<<min<<"    "<<max<<endl;

		sprintf(buffer,"disparity/depthImage%i.png",current);
		imwrite(buffer,imgD);									//Viewing purposes
		sprintf(buffer,"disparity/depthImage%i.DMX",current);
		saveMat(imgDepth,buffer,dt);							//Processing purposes

		if(save_Rectified)
		{
			sprintf(buffer,"%sRectified%i.png",loadS1.data(),current);
			imwrite(buffer,imgLeftr);
			sprintf(buffer,"%sRectified%i.png",loadS2.data(),current);
			imwrite(buffer,imgRight);
		}
		if(display){

			w = imgRightr.size().width;
			h = imgRightr.size().height;
			Mat canvas;
			Mat tImage;
			canvas.create(h, w*2, CV_8UC3);

			Mat canvasPart = canvas(Rect(0, 0, w, h));
			cvtColor(imgLeftr, tImage, COLOR_GRAY2BGR);
			resize(tImage, canvasPart, canvasPart.size(), 0, 0, CV_INTER_AREA);
			Rect vroil(cvRound(roi1.x), cvRound(roi1.y),
					cvRound(roi1.width), cvRound(roi1.height));
			rectangle(canvasPart, vroil, Scalar(0,0,255), 3, 8);
			canvasPart = canvas(Rect(w, 0, w, h));
			cvtColor(imgRightr, tImage, COLOR_GRAY2BGR);
			resize(tImage, canvasPart, canvasPart.size(), 0, 0, CV_INTER_AREA);
			Rect vroir(cvRound(roi2.x), cvRound(roi2.y),
					cvRound(roi2.width), cvRound(roi2.height));
			rectangle(canvasPart, vroir, Scalar(0,0,255), 3, 8);




			for( i = 0; i < canvas.rows; i += 16 )
				line(canvas, Point(0, i), Point(canvas.cols, i), Scalar(0, 255, 0), 1, 8);

			//			imshow("left Image",imgLeftr);
			//			imshow("right Image", imgRightr);
			imshow("Rectified Images",canvas);
			imshow("Depth image",imgD);
			waitKey(0);
		}
		current++;
	}
}
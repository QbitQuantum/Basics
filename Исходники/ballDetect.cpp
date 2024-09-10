void ballDetect :: initDetect(char *videoInput){

    VideoCapture capture;
    Mat src, src_HSV, processed;
    int x=0; int y=0; 

    Mat currentFrame, back, fore;   
    BackgroundSubtractorMOG2 bg;

    std::vector<std::vector<cv::Point> > contours;

    capture.open(videoInput);
    capture.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);

    // int xyz=1;

    while(1){

        // cout<<xyz++<<endl;
        capture.read(src);
        cvtColor(src, src_HSV, COLOR_BGR2HSV);

        bg.operator ()(src, fore);
        bg.getBackgroundImage(back);
        erode(fore, fore, Mat());
        dilate(fore, fore, Mat());
        findContours(fore, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
        // drawContours(src,  contours,  -1,  Scalar(0,  0,  255),  2);
        contourCount=contours.size();

        if(white_collide.x != -1 && white_collide.y!=-1){
            circle(src, white_collide, 2, Scalar(0, 0, 0), 2);
            circle(src, white_initial, 2, Scalar(0, 0, 0), 2);
            line(src, white_initial, white_collide, Scalar(255, 255, 255), 1, CV_AA);
        }

        inRange(src_HSV, *minval, *maxval, processed);
        morphOps(processed);
        trackFilteredObject(x, y, processed, src);

        for(int i=0;i<(int)white_position.size()-1;++i){
            line(src, white_position[i], white_position[i+1], Scalar(255, 255, 255), 1, CV_AA); 
        }
        while(white_collide.x == -1 && white_collide.y==-1){
            setMouseCallback("source", onMouseClick, &src);
            putText(src, "Specify Point", Point(750, 40), 1, 1, Scalar(255, 0, 0), 2);
            imshow("source", src);
            waitKey(5);
        }

        imshow("source", src);
        waitKey(5);
    }
}
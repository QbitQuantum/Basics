int main(int argc, char *argv[])
{
    RNG rng(12345);

    Mat frame;
    Mat back;
    Mat fore;
    VideoCapture cap(0);

    const int nmixtures =3;
    const bool bShadowDetection = false;
    const int history = 4;
    double dist2Center;
    BackgroundSubtractorMOG2 bg (history,nmixtures,bShadowDetection);

    vector<vector<Point> > contours;
    
    namedWindow("Frame");
    namedWindow("Background");
    setMouseCallback( "Frame", onMouse, 0 );
    //createTrackbar( "Smin", "CamShift Demo", &smin, 256, 0 );
    createTrackbar( "Vmin", "Frame", &vmin, 256, 0 );
    createTrackbar( "Vmax", "Frame", &vmax, 256, 0 );
    createTrackbar( "Smin", "Frame", &smin, 256, 0 );
    
    for(;;)
    {
        cap >> frame;
        bg.operator ()(frame,fore);
        bg.getBackgroundImage(back);
        erode(fore,fore,Mat());
        dilate(fore,fore,Mat());
        findContours(fore,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE); // CV_RETR_EXTERNAL retrieves only the extreme outer contours
        // vectors to hold contours infos
        vector<vector<Point> > contours_poly( contours.size() );
        vector<Rect> boundRect( contours.size() );
        vector<Point2f>center( contours.size() );
        vector<float>radius( contours.size() );

        for( unsigned int i = 0; i< contours.size(); i++ )
        {
            Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
            approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true);
            boundRect[i] = boundingRect ( Mat(contours_poly[i]) );

            double area = boundRect[i].area();
            if (area > 10000)
            {
                Point2f center(boundRect[i].x + boundRect[i].width/2.0, boundRect[i].y + boundRect[i].height/2.0);

                // Test if the center of a contour has crossed ROI (direction: going in or out)
                if (parking.size() > 3)
                {
                    dist2Center = pointPolygonTest(parking, center, true);
                }
                cout << center << "is " << dist2Center << " distance from the contour. \n"; 
                putText(frame, "I", center, FONT_HERSHEY_COMPLEX_SMALL, 1.5, color, 1);
                rectangle(frame, boundRect[i].tl(), boundRect[i].br(), Scalar(100, 100, 200), 2, CV_AA);
            
                // Tracking object with camShift
                if (trackObject) 
                {
                    CamShiftTracker CSTracker;
                    CSTracker.track(frame, boundRect[i], vmin, vmax, smin);

                    if( backProjMode )
                        cvtColor(CSTracker.getBackProjection(), frame, CV_GRAY2BGR );
                    ellipse(frame, CSTracker.getTrackBox(), Scalar(0,0,255), 3, CV_AA );
                }
            }
        }


        /*
         * Draw parking zone
         */
        for (unsigned int j = 0; j < parking.size(); j++)
        {
            circle(frame, parking[j], 5, Scalar(0,0,255), -1);
        }
        drawPaking(frame);

        imshow("Frame",frame);
        imshow("Background",back);

        char c = (char)waitKey(30);
        if( c == 27 || c == 'q')
            break;
        switch(c)
        {
            case 's':
                traceParking = !traceParking; 
                break;
            case 't':
                trackObject = !trackObject;
                break;
            case 'b':
                backProjMode = !backProjMode;
                break;
            case 'c':
                parking.clear();
                break;
            default:
                ;
        }
    }       

    return 0;
}
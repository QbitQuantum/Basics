int main(int argc, char* argv[])
{
	// Start 
    VideoCapture capture (CV_CAP_OPENNI);
    if(!capture.isOpened())
    {
        int error = -1;
        return 1;
    }

    namedWindow( "Color Image", 1 );
	//namedWindow( "Depth Map", 1);
    Mat view;
    bool blink = false;


	// NITE + openni
	
	XnStatus rc = XN_STATUS_OK;
	
	Context context;
	rc = context.Init();
	rc = g_GestureGenerator.Create(context);
	rc = g_HandsGenerator.Create(context);
	XnCallbackHandle hcb1,hcb2; 
	g_GestureGenerator.RegisterGestureCallbacks(Gesture_Recognized, Gesture_Process, NULL, hcb1);
	g_HandsGenerator.RegisterHandCallbacks(handCreate, handUpdate, handDestroy, NULL, hcb2);
	rc = context.StartGeneratingAll();
	rc = g_GestureGenerator.AddGesture(GESTURE_TO_USE, NULL);

	double d = 1.0;
	double angle = 0.0;
	double angleZ = 0.0;

	Mat result;
	
	Mat orig = imread("crocus.jpg");
	result.create(750, 750, CV_8UC3);
	double centerX = orig.cols/2;
    double centerY = orig.rows/2;
	warpPerspective(orig, orig, getScaleMatrix(1.0), orig.size(), INTER_CUBIC, BORDER_TRANSPARENT);

    while( capture.isOpened() )
    {
		rc = context.WaitAndUpdateAll();
		d = getZoom();
		angle = getAngle();
		angleZ = getAngle3D();
		if (abs(d - oldZoom) > 0.009) {
			//printf("angle = %f \n",angle);
			oldAngle += angle;

			//create the transformation to be passed to warp
			Mat openCVTransform = getRotationMatrix2D(Point2f(centerX, centerY), oldAngle, d);

			//warp image to apply transformation
			result.setTo(Scalar(0));
			warpAffine(orig, result, openCVTransform, result.size(), INTER_CUBIC, BORDER_TRANSPARENT);
			oldZoom = d;
			
		}
		imshow("Result", result);
		

        Mat bgrImage;
        capture.grab();

		capture.retrieve( bgrImage, CV_CAP_OPENNI_BGR_IMAGE );

		if (hand1ID != -1) {
			circle(bgrImage,Point(hand1.back().X + bgrImage.rows/2, bgrImage.cols/2 - hand1.back().Y),2,CV_RGB(0,255,0),3);
		
		}
		if (hand2ID != -1) {
			circle(bgrImage,Point(hand2.back().X + bgrImage.rows/2, bgrImage.cols/2 - hand2.back().Y),2,CV_RGB(0,255,0),3);
		}
		flip(bgrImage,bgrImage,1);
        imshow("Color Image", bgrImage);
		result.create(750, 750, CV_8UC3);
		
        if(waitKey(33) == 'q')
        {
            break;
        }
    }
	context.Shutdown();
    return 0;
}
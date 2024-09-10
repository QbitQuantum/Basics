int main(int argc, char* argv[])
{

	EnumerationErrors errors;


    //rc = context.Init();
    rc = context.InitFromXmlFile(strPathToXML,&errors);
    if (rc == XN_STATUS_NO_NODE_PRESENT)
	{
		XnChar strError[1024];
		errors.ToString(strError, 1024);
		printf("%s\n", strError);
		return (rc);
	}
	else if (rc != XN_STATUS_OK)
	{
		printf("Open failed: %s\n", xnGetStatusString(rc));
		return (rc);
	}
	
	/* UNCOMMENT TO GET FILE READING 
    //rc = context.OpenFileRecording(strInputFile);
	//CHECK_RC(rc, "Open input file");

	//rc = context.FindExistingNode(XN_NODE_TYPE_PLAYER, player);
	//CHECK_RC(rc, "Get player node"); */ 

	rc = context.FindExistingNode(XN_NODE_TYPE_DEPTH, depth);
	CHECK_RC(rc, "Find depth generator");

	rc = context.FindExistingNode(XN_NODE_TYPE_IMAGE, image);
	CHECK_RC(rc, "Find image generator");

    depth.GetMetaData(depthMD);
	image.GetMetaData(imageMD);

    //rc = player.SetRepeat(FALSE);
	XN_IS_STATUS_OK(rc);

    //rc = player.GetNumFrames(image.GetName(), nNumFrames);
	//CHECK_RC(rc, "Get player number of frames");
	//printf("%d\n",nNumFrames);

    //rc = player.GetNumFrames(depth.GetName(), nNumFrames);
	//CHECK_RC(rc, "Get player number of frames");
	//printf("%d\n",nNumFrames);

	// Hybrid mode isn't supported
	if (imageMD.FullXRes() != depthMD.FullXRes() || imageMD.FullYRes() != depthMD.FullYRes())
	{
		printf ("The device depth and image resolution must be equal!\n");
		return 1;
	}

	// RGB is the only image format supported.
	if (imageMD.PixelFormat() != XN_PIXEL_FORMAT_RGB24)
	{
		printf("The device image format must be RGB24\n");
		return 1;
	}

    avi = cvCreateVideoWriter(strOutputFile, 0, 30, cvSize(640,480), TRUE);

    depthMetersMat = cvCreateMat(480, 640, CV_16UC1);
    kinectDepthImage = cvCreateImage( cvSize(640,480),16,1 );

    depthMetersMat2 = cvCreateMat(480, 640, CV_16UC1);
    kinectDepthImage2 = cvCreateImage( cvSize(640,480),16,1 );

    colorArr[0] = cv::Mat(imageMD.YRes(),imageMD.XRes(),CV_8U);
    colorArr[1] = cv::Mat(imageMD.YRes(),imageMD.XRes(),CV_8U);
    colorArr[2] = cv::Mat(imageMD.YRes(),imageMD.XRes(),CV_8U);

    //prepare_for_face_detection();

    int b;
    int g;
    int r;

	while ((rc = image.WaitAndUpdateData()) != XN_STATUS_EOF && (rc = depth.WaitAndUpdateData()) != XN_STATUS_EOF) {
        if (rc != XN_STATUS_OK) {
            printf("Read failed: %s\n", xnGetStatusString(rc));
            break;
        }
        depth.GetMetaData(depthMD);
        image.GetMetaData(imageMD);

        //XnUInt32 a;
        //a = g_imageMD.FPS;
        printf("%d\n",imageMD.FrameID());
        //a = g_depthMD.DataSize();
        //printf("%d\n",a);

        pDepth = depthMD.Data();
        pImageRow = imageMD.RGB24Data();

        for (unsigned int y=0; y<imageMD.YRes(); y++) {
            pPixel = pImageRow;
            uchar* Bptr = colorArr[0].ptr<uchar>(y);
            uchar* Gptr = colorArr[1].ptr<uchar>(y);
            uchar* Rptr = colorArr[2].ptr<uchar>(y);

            for(unsigned int x=0;x<imageMD.XRes();++x , ++pPixel){
                Bptr[x] = pPixel->nBlue;
                Gptr[x] = pPixel->nGreen;
                Rptr[x] = pPixel->nRed;

                depthMetersMat->data.s[y * XN_VGA_X_RES + x ] = 7*pDepth[y * XN_VGA_X_RES + x];
                depthMetersMat2->data.s[y * XN_VGA_X_RES + x ] = pDepth[y * XN_VGA_X_RES + x];
            }
            pImageRow += imageMD.XRes();
        }
        cv::merge(colorArr,3,colorImage);
        iplImage = colorImage;

        //cvThreshold(depthMetersMat2, depthMetersMat2, 150, 1500, THRESH_BINARY);

        cvGetImage(depthMetersMat,kinectDepthImage);
        cvGetImage(depthMetersMat2,kinectDepthImage2);

        depthImage = Bw2Image(kinectDepthImage2);
        printf("1. Middle pixel is %u millimeters away\n",depthImage[240][320]);

        rgbImage = RgbImage(&iplImage);

		// we want to see on up to 2000 MM 
        int THRESH = 2000;

        for (unsigned int y=0; y<imageMD.YRes(); y++) {
            for(unsigned int x=0;x<imageMD.XRes();++x){
                if ( depthImage[y][x] >= THRESH ) {
                    depthImage[y][x] = 0;
                } else {
                    float tmp = depthImage[y][x];
                    tmp = tmp / THRESH * (65536)*(-1) + 65536;
                    depthImage[y][x] = (unsigned int)tmp;
                }
            }
        }
		
		// THE PART ABOUT FILTERING COLOURS IN HSV TO SEE ONLY SPECIFIC ONE 
		// AFTER ONE FEW MORPHOLOGICAL OPERATIONS TO MAKE IT LOOK BETTER 

        IplImage* imgHSV = cvCreateImage(cvGetSize(&iplImage), 8, 3);
        cvCvtColor(&iplImage, imgHSV, CV_BGR2HSV);
        imgThreshed = cvCreateImage(cvGetSize(&iplImage), 8, 1);
        //cvInRangeS(imgHSV, cvScalar(100, 60, 80), cvScalar(110, 255, 255), imgThreshed); // BLUE
        cvInRangeS(imgHSV, cvScalar(29, 95, 95), cvScalar(35, 255, 255), imgThreshed); // YELLOW
        //cvInRangeS(imgHSV, cvScalar(29, 60, 60), cvScalar(35, 255, 255), imgThreshed); // YELLOW DARK
        //cvInRangeS(imgHSV, cvScalar(150, 70, 70), cvScalar(160, 255, 255), imgThreshed); // PINK
        //cvInRangeS(imgHSV, cvScalar(40, 76, 76), cvScalar(70, 255, 255), imgThreshed); // GREEN
        IplConvKernel* kernel = cvCreateStructuringElementEx(3, 3, 1, 1, CV_SHAPE_RECT, NULL);
        //cvDilate(imgThreshed,imgThreshed,kernel);
        //cvErode(imgThreshed,imgThreshed,kernel);
        Mat mat = Mat(imgThreshed);
        blur(Mat(imgThreshed),mat,cvSize(3,3));
        imgThreshed = &IplImage(mat);
        //cvInRangeS(imgThreshed,cvScalar(100),cvScalar(255),imgThreshed);
        //cvErode(imgThreshed,imgThreshed,kernel);
        cvDilate(imgThreshed,imgThreshed,kernel);
        cvDilate(imgThreshed,imgThreshed,kernel);
        cvErode(imgThreshed,imgThreshed,kernel);
        cvErode(imgThreshed,imgThreshed,kernel);
        mat = Mat(imgThreshed);
        blur(Mat(imgThreshed),mat,cvSize(6,6));
        imgThreshed = &IplImage(mat);
        cvInRangeS(imgThreshed,cvScalar(100),cvScalar(255),imgThreshed);
        cvReleaseImage(&imgHSV);
        BwImage threshed = BwImage(imgThreshed);



        if ( initialize == true ) {

            normalizeReferenceFace();
            int currentID = 0;

                for ( int y = 30; y<480; y++ ) {
                    for ( int x = 30; x<640; x++ ) {
                        bool g2g = true;
                        //printf("%d %d %d\n",ID, y,x);
                        if ( threshed[y][x]!=0 ) {
                            for ( int ID2 = 0; ID2<nbOfPoints; ID2++) {
                                if ( (abs(markers[ID2].y-y)<proximityLimit) && (abs(markers[ID2].x-x)<proximityLimit)) {
                                    g2g = false;
                                }
                            }
                            if (currentID >= nbOfPoints || g2g == false ) {
                                break;
                            }
                            markers[currentID].y=y;
                            markers[currentID].x=x;
                            currentID++;
                            printf("WHITE PIXEL INITIALIZED %d: %d %d\n",currentID, x,y);
                        }
                    }
                }


            if (isDebugConf==true || currentID == nbOfMarkers) {
                printf("%d PIXELS INITIALIZED\n", currentID);
                initialize = false;
                //printf("%d,%d\n", currentID, nbOfPoints);
                //return 0;
            } else {
                printf("WAITING FOR %d PIXELS TO APPEAR, %d SO FAR \n",nbOfMarkers, currentID);
                continue;
            }


            // FIND TOP RIGHT AND CHIN PIXEL

            int refPixID = 0;
            int chinPixID = 0;

            for ( int i = 0; i < nbOfMarkers; i++) {
                if ( (markers[i].x + markers[i].y)*(markers[i].x + markers[i].y) < (markers[refPixID].x + markers[refPixID].y)* (markers[refPixID].x + markers[refPixID].y)) {
                    refPixID = i;
                }
                if (markers[i].y > markers[chinPixID].y) {
                    chinPixID = i;
                }
            }

            float width = (markers[1].x-markers[0].x)*2;
            float heigth = abs(markers[1].y-markers[0].y);

            // WE GOT WIDTH & HEIGTH OF THE FACE, LETS ADJUST POINTS

            // SET 0 to REF, SET 1 to CHIN

            MyPoint tmp = MyPoint(markers[refPixID].x,markers[refPixID].y);
            markers[refPixID].x = markers[0].x;
            markers[refPixID].y = markers[0].y;
            markers[0].x = tmp.x;
            markers[0].y = tmp.y;

            tmp = MyPoint(markers[chinPixID].x,markers[chinPixID].y);
            markers[chinPixID].x = markers[1].x;
            markers[chinPixID].y = markers[1].y;
            markers[1].x = tmp.x;
            markers[1].y = tmp.y;


            // REST OF THE POINTS

            for ( int i = 2; i < nbOfPoints; i++) {

                int cost = 0;
                int lowestCost = 0;
                int closestPixID = -1;


                for ( int j = 2; j < nbOfMarkers; j++ ) {
                    cost = (markers[j].x-points[i].x*width)*(markers[j].x-points[i].x*width) + (markers[j].y-points[i].y*heigth)*(markers[j].y-points[i].y*heigth);
                    if ( cost < lowestCost ) {
                        lowestCost = cost;
                        closestPixID = j;
                    }
                    if (closestPixID == -1) {
                        //printf("COS JEST SPORO NIE W PORZADKU, CHECK HERE\n");
                        break;
                    }
                    tmp.x = markers[i].x;
                    tmp.y = markers[i].y;
                    markers[i].x=markers[closestPixID].x;
                    markers[i].x=markers[closestPixID].y;
                    markers[closestPixID].x = tmp.x;
                    markers[closestPixID].y = tmp.y;
                }
            }
        }

        for ( int currentPixelID = 0; currentPixelID < nbOfMarkers; currentPixelID++) {
            if (markers[currentPixelID].x == 0) {
                continue;
            }

            if ( threshed[markers[currentPixelID].y][markers[currentPixelID].x] < 128 ) {
                printf("PIXEL %d LOST\n",currentPixelID);

                for ( int neighbSize = 2; neighbSize < maxNeighbSize; neighbSize = neighbSize + 2 ) {

                    int x1 = markers[currentPixelID].x - neighbSize/2;
                    if ( x1 < intoDepthX(0) ) {
                        x1 = (int)intoDepthX(0);
                    }

                    int y1 = (int)(markers[currentPixelID].y-neighbSize/2);
                    if (  y1 < intoDepthY(0) ) {
                        y1 = intoDepthY(0);
                    }

                    int y2 = markers[currentPixelID].y+neighbSize/2;
                    if (  y2 > intoDepthY(480)  ) {
                        y2 = intoDepthY(480);
                    }

                    int x2 = markers[currentPixelID].x+neighbSize/2;
                    if ( x2 > intoDepthX(640) ) {
                        y2 = intoDepthX(640);
                    }

                    bool found = false;
                    for ( int y = y1; y < y2; y++) {
                        for ( int x = x1; x < x2; x++) {
                            bool g2g = true;
                            if (threshed[y][x] > 128) {
                                for ( int ID2 = 0; ID2<nbOfMarkers; ID2++) {
                                    if ( currentPixelID == ID2 )
                                        continue;
                                    if ( (abs(markers[ID2].y-y)<proximityLimit) && (abs(markers[ID2].x-x)<proximityLimit)) {
                                        g2g = false;
                                        break;
                                    }
                                }

                                if ( g2g ) {
                                    markers[currentPixelID].x = x;
                                    markers[currentPixelID].y = y;
                                    found = true;
                                    printf("Pixel %d, FOUND\n",currentPixelID);
                                    break;
                                }
                            }
                        }
                        if (found == true ) {
                            break;
                        }
                    }
                    if (found == true ) {
                        break;
                    }
                }
            }

            paintMarkerOnBoth(markers[currentPixelID]);

        }
        faceImage = cvCreateImage(cvGetSize(&iplImage), 8, 1);
        paintFace();

		// normal kinect depth
        cvShowImage("Depth_Kinect", kinectDepthImage);
		// depth within 80 - 200 mm, normalized 
        cvShowImage("Depth_Kinect_2", kinectDepthImage2);
		// rgb with tracking points
        cvShowImage("RGB_Kinect", &iplImage);
		// colour detector 
        cvShowImage("RGB_Threshed", imgThreshed);
		// attempt to draw a face 
        cvShowImage("Face Image", faceImage);

        cvWaitKey(50);           // wait 20 ms

        if ( avi == NULL) {
            printf ("dupa%d \n",1);
        }
        //cvWriteFrame (avi, &iplImage);
	}

//    cvReleaseImageHeader(kinectDepthImage);
    cvReleaseVideoWriter(&avi);
//    cvReleaseHaarClassifierCascade( &cascade );
    context.Shutdown();

	return 0;
}
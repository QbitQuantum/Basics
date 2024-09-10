void PushbroomStereo::RunStereoPushbroomStereo( Mat leftImage, Mat rightImage, Mat laplacian_left, Mat laplacian_right,
	cv::vector<Point3f> *pointVector3d, cv::vector<Point3i> *pointVector2d, cv::vector<uchar> *pointColors,
	int row_start,  int row_end, PushbroomStereoState state )
{
    // we will do this by looping through every block in the left image
    // (defined by blockSize) and checking for a matching value on
    // the right image

    cv::vector<Point3f> localHitPoints;

    int blockSize = state.blockSize;
    int disparity = state.disparity;
    int sadThreshold = state.sadThreshold;

    int startJ = 0;
    int stopJ = leftImage.cols - (disparity + blockSize);
    if (disparity < 0)
    {
        startJ = -disparity;
        stopJ = leftImage.cols - blockSize;
    }

    //printf("row_start: %d, row_end: %d, startJ: %d, stopJ: %d, rows: %d, cols: %d\n", row_start, row_end, startJ, stopJ, leftImage.rows, leftImage.cols);

    int hitCounter = 0;


    if (state.random_results < 0) {
		int *sadArray = new int[ leftImage.rows * leftImage.step ];
		int iStep, jStep;
#ifdef USE_GPU
		StopWatchInterface	*timer;
		sdkCreateTimer( &timer );
		sdkResetTimer( &timer );
		sdkStartTimer( &timer );

		//GetSADBlock(row_start, row_end, blockSize, startJ, stopJ, sadArray, leftImage, rightImage, laplacian_left, laplacian_right, state);
		m_sadCalculator.runGetSAD( row_start, row_end, startJ, stopJ, sadArray, leftImage.data, rightImage.data, laplacian_left.data, laplacian_right.data, leftImage.step,
			state.blockSize, state.disparity, state.sobelLimit );

		sdkStopTimer( &timer );
		//printf("RunStereo bottleneck timer: %.2f ms \n", sdkGetTimerValue( &timer) );
		sdkDeleteTimer( &timer );

#endif

		int gridY = (row_end - row_start)/blockSize;
		int gridX = (stopJ - startJ)/blockSize;

		for (int y=0; y< gridY; y++)
		{
			for (int x=0; x< gridX; x++)
			{               
                // check to see if the SAD is below the threshold,
                // indicating a hit
				int i = row_start + y * blockSize;
				int j = startJ + x * blockSize;
#ifdef USE_GPU
				int sad = sadArray[ y * gridX + x];
#else
				int sad= GetSAD(leftImage, rightImage, laplacian_left, laplacian_right, j, i, state);
#endif
                if (sad < sadThreshold && sad >= 0)
                {
                    // got a hit

                    // now check for horizontal invariance
                    // (ie check for parts of the image that look the same as this
                    // which would indicate that this might be a false-positive)

                    if (!state.check_horizontal_invariance || CheckHorizontalInvariance(leftImage, rightImage, laplacian_left, laplacian_right, j, i, state) == false) {

                        // add it to the vector of matches
                        // don't forget to offset it by the blockSize,
                        // so we match the center of the block instead
                        // of the top left corner
                        localHitPoints.push_back(Point3f(j+blockSize/2.0, i+blockSize/2.0, -disparity));

                        //localHitPoints.push_back(Point3f(state.debugJ, state.debugI, -disparity));


                        uchar pxL = leftImage.at<uchar>(i,j);
                        pointColors->push_back(pxL); // TODO: this is the corner of the box, not the center

                        hitCounter ++;

                        if (state.show_display)
                        {
                            pointVector2d->push_back(Point3i(j, i, sad));
                        }
                    } // check horizontal invariance
                }
            }
        }
    } else {

        double intpart;

        float fractpart = modf(state.random_results , &intpart);
        hitCounter = int(intpart);

        // determine if this is a time we'll use that last point
        std::random_device rd;
        std::default_random_engine generator(rd()); // rd() provides a random seed
        std::uniform_real_distribution<float> distribution(0, 1);

        if (fractpart > distribution(generator)) {
            hitCounter ++;
        }

        for (int i = 0; i < hitCounter; i++) {

            int randx = rand() % (stopJ - startJ) + startJ;
            int randy = rand() % (row_end - row_start) + row_start;

            localHitPoints.push_back(Point3f(randx, randy, -disparity));
        }
    }

    // now we have an array of hits -- transform them to 3d points
    if (hitCounter > 0) {

        perspectiveTransform(localHitPoints, *pointVector3d, state.Q);
    }

}
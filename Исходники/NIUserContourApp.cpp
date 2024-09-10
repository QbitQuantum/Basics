void NIUserMaskApp::update()
{
	if ( mNI.checkNewVideoFrame() )
	{
		Surface8u maskSurface = mNIUserTracker.getUserMask();

		cv::Mat cvMask, cvMaskFiltered;
		cvMask = toOcv( Channel8u( maskSurface ) );
		cv::blur( cvMask, cvMaskFiltered, cv::Size( mBlurAmt, mBlurAmt ) );

		cv::Mat dilateElm = cv::getStructuringElement( cv::MORPH_RECT,
				cv::Size( mDilateAmt, mDilateAmt ) );
		cv::Mat erodeElm = cv::getStructuringElement( cv::MORPH_RECT,
				cv::Size( mErodeAmt, mErodeAmt ) );
		cv::erode( cvMaskFiltered, cvMaskFiltered, erodeElm, cv::Point( -1, -1 ), 1 );
		cv::dilate( cvMaskFiltered, cvMaskFiltered, dilateElm, cv::Point( -1, -1 ), 3 );
		cv::erode( cvMaskFiltered, cvMaskFiltered, erodeElm, cv::Point( -1, -1 ), 1 );
		cv::blur( cvMaskFiltered, cvMaskFiltered, cv::Size( mBlurAmt, mBlurAmt ) );

		cv::threshold( cvMaskFiltered, cvMaskFiltered, mThres, 255, CV_THRESH_BINARY);

		vector< vector< cv::Point > > contours;
		cv::findContours( cvMaskFiltered, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE );

		mShape.clear();
		for ( vector< vector< cv::Point > >::const_iterator it = contours.begin();
				it != contours.end(); ++it )
		{
			vector< cv::Point >::const_iterator pit = it->begin();

			if ( it->empty() )
				continue;

			mShape.moveTo( fromOcv( *pit ) );

			++pit;
			for ( ; pit != it->end(); ++pit )
			{
				mShape.lineTo( fromOcv( *pit ) );
			}
			mShape.close();
		}
	}
}
FastSymmetryDetector::FastSymmetryDetector( const Size image_size, const Size hough_size, const int rot_resolution ) {
    this->imageSize     = image_size;
    this->center        = Point2f( imageSize.width - 1.0, imageSize.height - 1.0 ) * 0.5;
    this->diagonal      = hypotf( imageSize.width, imageSize.height );
    this->rhoDivision   = diagonal;
    this->rhoMax        = hough_size.width;
    this->thetaMax      = hough_size.height;
    
    rotMatrices.resize( thetaMax, Mat(2, 2, CV_32FC1) );
    
    float thetaIncDeg = 180.0f / thetaMax;
    float half_theta_max = thetaMax * 0.5f;
    
    /* Pre calculate rotation matrices from -90 deg to 90 deg (actually to 89 deg) */
    for( int t = 0; t < thetaMax; t++ ){
        double angle = thetaIncDeg * ( t - half_theta_max );
        Mat rotation = getRotationMatrix2D( Point2f(0.0, 0.0), angle, 1.0);
        rotation.convertTo( rotation, CV_32FC1 );
        
        rotMatrices[t] = Mat( rotation, Rect(0, 0, 2, 2) );
        rotMatrices[t].row(0) *= 0.5;
    }
    
    accum       = Mat::zeros( thetaMax + 2, rhoMax, CV_32FC1 );
    rotEdges    = Mat::zeros( rhoDivision, diagonal, CV_32FC1 );
    reRows.resize( rhoDivision );
}
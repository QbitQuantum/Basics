Mat TableObjectDetector::determinePlaneRotation(cv::Mat normal) {
    // Graham Schmidt orthogonalization
    int mind = 0; double mval = 999;
    for (int i=0; i<3; i++) {
        if (abs(normal.at<double>(i)) < mval) {
            mind = i;
            mval = abs(normal.at<double>(i));
        }
    }
    
    Mat vstart = -mval*normal;
    vstart.at<double>(mind) = 1;
    vstart = vstart/cv::norm(vstart);
    Mat v2 = normal.cross(vstart);
    v2 = v2/cv::norm(v2);
    Mat v3 = normal.cross(v2);
    v3 = v3/cv::norm(v3);
    
    Mat R(3, 3, CV_64F);
    v2.copyTo(R.col(0));
    v3.copyTo(R.col(1));
    normal.copyTo(R.col(2));
    
    return R;
}
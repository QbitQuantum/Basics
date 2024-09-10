std::vector<KeyPoint> extract_sift_keypoints(Mat image)
{
	cout << "Extracting features..." << endl ;

	image = threshold_and_convert(image);

	SiftFeatureDetector detector;
    vector<KeyPoint> keypoints;
    detector.detect(image, keypoints);

    cout<<"keys:" << keypoints.size()<< endl ;

    if(DEBUG)
    {
    	// Add results to image and save.
    	cv::Mat output;
    	cv::drawKeypoints(image, keypoints, output);
    	imshow("sift_keys", output);
    	moveWindow("sift_keys" , 500 , 100);
	}
    return keypoints;
}
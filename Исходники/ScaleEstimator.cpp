double ScaleEstimator::calcLineIntersection(cv::Mat d1, cv::Mat d2, cv::Mat p2, cv::Mat& ip1) {
	cv::Mat p1(3, 1, CV_64FC1);	p1 = 0.0f;
	cv::Mat ret(3, 1, CV_64FC1);
	double t = 0.0f;
	cv::Mat normalVector = d1.cross(d2);
	t = (p2 - p1).cross(d2).dot(normalVector) / cv::norm(normalVector) / cv::norm(normalVector);
	ret = p1 + t*d1;


	ip1 = ret.clone();
	return cv::norm(normalVector.dot(p2 - p1)) / cv::norm(normalVector);
}
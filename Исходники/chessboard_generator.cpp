void Camera::pitch(double angle)
{
	Mat temp = center - eye;
	Mat rAxis = temp.cross(up);
	Mat cmat = (Mat_<double>(3, 3) <<
		0, -rAxis.at<double>(2, 0), rAxis.at<double>(1, 0),
		rAxis.at<double>(2, 0), 0, -rAxis.at<double>(0, 0),
		-rAxis.at<double>(1, 0), rAxis.at<double>(0, 0), 0);
	angle = (CV_PI / 180) * angle;
	Mat pitchingMat = Mat::eye(3, 3, CV_64F) + sin(angle) * cmat + (1 - cos(angle)) * cmat * cmat;
	rmat = pitchingMat * rmat;
}
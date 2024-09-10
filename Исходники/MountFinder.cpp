double get_point_line_distance(cv::Vec4f line, cv::Point point)
{
	using namespace cv;
	Point2f linePoint(line[2], line[3]);
	Mat lineDirection(Point2f(line[0], line[1]));

	Mat normedLineDirection;
	normalize(lineDirection, normedLineDirection);
;
	Mat pointDifference(linePoint - (Point2f) point);
	pointDifference.at<float>(0, 0);
	double differenceLength = pow(pow(pointDifference.at<float>(0, 0), 2) + pow(pointDifference.at<float>(1, 0), 2), 0.5);

	Mat normedDifference;
	normalize(pointDifference, normedDifference);

	//std::cout << "Line " << normedLineDirection << std::endl;
	//std::cout << "normed" << normedDifference << std::endl;

	double dotProduct = normedLineDirection.dot(normedDifference);

	assert(abs(dotProduct) <= 1.001);

	if (dotProduct > 1)
	{
		dotProduct = 1;
	}
	else if (dotProduct < -1)
	{
		dotProduct = -1;
	}

	//std::cout << "Dot product: " << dotProduct << std::endl;

	double angle = acos(dotProduct);

	//std::cout << "Angle: " << angle << std::endl;

	double distance = differenceLength * sin(angle);

	//std::cout << "Adding distance " << distance << std::endl;
	return distance;
}
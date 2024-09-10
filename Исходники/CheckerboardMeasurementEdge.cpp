void CheckerboardPoseMeasurementEdge::setError(tf::Transform cameraToMarker) {
	// left top point of the marker denotes the origin of the marker's coordinate system
	double xOrigin, yOrigin;
	this->frameImageConverter->project(cameraToMarker.inverse(), xOrigin,
			yOrigin);

	double rows = this->measurement.marker_data[CheckerboardDetection::idx_rows];
	double cols = this->measurement.marker_data[CheckerboardDetection::idx_cols];
	double squareLength =
			this->measurement.marker_data[measurement.marker_data.size() - 1]; // always the last element
	squareLength = squareLength / 1000; // conversion from [mm] to [m]

	// point on the x axis of the marker's coordinate system
	double xAxisX, yAxisX;
	tf::Transform alongXAxis(tf::Quaternion(0, 0, 0, 1),
			tf::Vector3(squareLength, 0, 0));
	this->frameImageConverter->project((alongXAxis * cameraToMarker).inverse(),
			xAxisX, yAxisX);

	// point on the y axis of the marker's coordinate system
	double xAxisY, yAxisY;
	tf::Transform alongYAxis(tf::Quaternion(0, 0, 0, 1),
			tf::Vector3(0, squareLength, 0));
	this->frameImageConverter->project((alongYAxis * cameraToMarker).inverse(),
			xAxisY, yAxisY);

	// set error
	double offset = 4;

	// top left corner
	this->_error[0] = measurement.marker_data[offset + 0 + 0] - xOrigin;
	this->_error[1] = measurement.marker_data[offset + 0 + 1] - yOrigin;

	// one right from the top left corner
	this->_error[2] = measurement.marker_data[offset + (2 * 1) + 0] - xAxisX;
	this->_error[3] = measurement.marker_data[offset + (2 * 1) + 1] - yAxisX;

	// one down from the top left corner
	this->_error[4] = measurement.marker_data[offset + (2 * cols) + 0] - xAxisY;
	this->_error[5] = measurement.marker_data[offset + (2 * cols) + 1] - yAxisY;

	if (false) {
		cv::Mat outImg;
		cv_bridge::CvImagePtr input_bridge;
		input_bridge = cv_bridge::toCvCopy(measurement.image,
				sensor_msgs::image_encodings::BGR8);
		outImg = input_bridge->image;

		cv::line(outImg, cv::Point(xOrigin - 3, yOrigin - 3),
				cv::Point(xOrigin + 3, yOrigin + 3), CV_RGB(255, 0, 0));
		cv::line(outImg, cv::Point(xOrigin - 3, yOrigin + 3),
				cv::Point(xOrigin + 3, yOrigin - 3), CV_RGB(255, 0, 0));
		cv::circle(outImg,
				cv::Point(measurement.marker_data[offset],
						measurement.marker_data[offset + 1]), 3,
				CV_RGB(255, 0, 0));
		cv::line(outImg, cv::Point(xAxisX - 3, yAxisX - 3),
				cv::Point(xAxisX + 3, yAxisX + 3), CV_RGB(0, 255, 0));
		cv::line(outImg, cv::Point(xAxisX - 3, yAxisX + 3),
				cv::Point(xAxisX + 3, yAxisX - 3), CV_RGB(0, 255, 0));
		cv::circle(outImg,
				cv::Point(measurement.marker_data[offset + (2 * 1)],
						measurement.marker_data[offset + (2 * 1) + 1]), 3,
				CV_RGB(0, 255, 0));
		cv::line(outImg, cv::Point(xAxisY - 3, yAxisY - 3),
				cv::Point(xAxisY + 3, yAxisY + 3), CV_RGB(0, 0, 255));
		cv::line(outImg, cv::Point(xAxisY - 3, yAxisY + 3),
				cv::Point(xAxisY + 3, yAxisY - 3), CV_RGB(0, 0, 255));
		cv::circle(outImg,
				cv::Point(measurement.marker_data[offset + (2 * cols)],
						measurement.marker_data[offset + (2 * cols) + 1]), 3,
				CV_RGB(0, 0, 255));
		string filename = "/tmp/" + measurement.id + "-pose.jpg";
		cv::imwrite(filename, outImg);
	}
}
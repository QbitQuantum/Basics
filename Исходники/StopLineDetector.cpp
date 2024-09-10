bool StopLineDetector::EstimateVerticalLine(Mat &input, Mat &debugImage, Rect roi, Point2i searchedSlope, CVMath::Line *outputLine) {
	vector<Vec4i> foundLines;
	Mat localCopy;
	input(roi).copyTo(localCopy);
	Canny(localCopy, localCopy, 50, 200, 3);

	HoughLinesP(localCopy, foundLines, 1, CV_PI / 180 , 10, 15, 4);

	const float COS_ANGLE_LIMIT = cos(20.0 / 180 * CV_PI);

	int resultListSize = 0;
	Point2f resultTangent;
	Point2f resultPoint;

	size_t listSize = foundLines.size();
	for (size_t i = 0; i < listSize; i++) {
		Vec4i l = foundLines[i];

		Point2f p0 = Point2f(l[0], l[1]) + Point2f(roi.x, roi.y);
		Point2f p1 = Point2f(l[2], l[3]) + Point2f(roi.x, roi.y);

		Point2f tangent = p0 - p1;
		tangent /= cv::norm(tangent);

		float dotProduct = tangent.dot(searchedSlope);
		if (dotProduct > COS_ANGLE_LIMIT || -dotProduct > COS_ANGLE_LIMIT ) {
			if(debugEnabled) {
				line(debugImage, p0, p1, Scalar(255, 0, 0), 2);
			}

			resultPoint += p0;
			resultTangent += tangent;
			resultListSize++;
		}
	}

	if(resultListSize > 0) {
		*outputLine = CVMath::Line (resultPoint / resultListSize, resultTangent / resultListSize);
		if(debugEnabled) {
			line(debugImage, outputLine->pointOnLine - outputLine->direction*20, outputLine->pointOnLine + outputLine->direction*20, Scalar(0, 100, 100), 2);
		}
		return true;
	}

	return false;
}
void OpticalFlowTransitionModel::predict(vector<shared_ptr<Sample>>& samples, const Mat& image, const shared_ptr<Sample> target) {
	points.clear();
	forwardPoints.clear();
	backwardPoints.clear();
	forwardStatus.clear();
	error.clear();
	squaredDistances.clear();
	correctFlowCount = 0;

	// build pyramid of the current image
	cv::buildOpticalFlowPyramid(makeGrayscale(image), currentPyramid, windowSize, maxLevel, true, BORDER_REPLICATE, BORDER_REPLICATE);
	if (previousPyramid.empty() || !target) { // optical flow cannot be computed if there is no previous pyramid or no current target
		swap(previousPyramid, currentPyramid);
		return fallback->predict(samples, image, target);
	}

	// compute grid of points at target location
	for (auto point = templatePoints.begin(); point != templatePoints.end(); ++point)
		points.push_back(Point2f(target->getWidth() * point->x + target->getX(), target->getHeight() * point->y + target->getY()));
	// compute forward and backward optical flow
	cv::calcOpticalFlowPyrLK(previousPyramid, currentPyramid, points, forwardPoints, forwardStatus, error, windowSize, maxLevel);
	cv::calcOpticalFlowPyrLK(currentPyramid, previousPyramid, forwardPoints, backwardPoints, backwardStatus, error, windowSize, maxLevel);
	swap(previousPyramid, currentPyramid);

	// compute flow and forward-backward-error
	vector<Point2f> flows;
	flows.reserve(points.size());
	squaredDistances.reserve(points.size());
	for (unsigned int i = 0; i < points.size(); ++i) {
		flows.push_back(forwardPoints[i] - points[i]);
		if (forwardStatus[i] && backwardStatus[i]) {
			Point2f difference = backwardPoints[i] - points[i];
			squaredDistances.push_back(make_pair(difference.dot(difference), i));
		}
	}
	if (squaredDistances.size() < points.size() / 2) // the flow for more than half of the points could not be computed
		return fallback->predict(samples, image, target);

	// find the flows with the least forward-backward-error (not more than 1 pixel)
	float maxError = 1 * 0.5f;
	vector<float> xs, ys;
	sort(squaredDistances.begin(), squaredDistances.end(), [](pair<float, int> lhs, pair<float, int> rhs) { return lhs.first < rhs.first; });
	xs.reserve(squaredDistances.size());
	ys.reserve(squaredDistances.size());
	for (correctFlowCount = 0; correctFlowCount < squaredDistances.size(); ++correctFlowCount) {
		if (squaredDistances[correctFlowCount].first > maxError)
			break;
		int index = squaredDistances[correctFlowCount].second;
		xs.push_back(flows[index].x);
		ys.push_back(flows[index].y);
	}
	if (correctFlowCount < points.size() / 2) // too few correct correspondences
		return fallback->predict(samples, image, target);

	// compute median flow (only change in position for now)
	sort(xs.begin(), xs.end());
	sort(ys.begin(), ys.end());
	float medianX = xs[xs.size() / 2];
	float medianY = ys[ys.size() / 2];
	Point2f medianFlow(medianX, medianY);

	// compute ratios of point distances in previous and current image
	vector<float> squaredRatios;
	squaredRatios.reserve(correctFlowCount * (correctFlowCount - 1) / 2);
	for (unsigned int i = 0; i < correctFlowCount; ++i) {
		for (unsigned int j = i + 1; j < correctFlowCount; ++j) {
			Point2f point1 = points[squaredDistances[i].second];
			Point2f forwardPoint1 = forwardPoints[squaredDistances[i].second];
			Point2f point2 = points[squaredDistances[j].second];
			Point2f forwardPoint2 = forwardPoints[squaredDistances[j].second];
			Point2f differenceBefore = point1 - point2;
			Point2f differenceAfter = forwardPoint1 - forwardPoint2;
			float squaredDistanceBefore = differenceBefore.dot(differenceBefore);
			float squaredDistanceAfter = differenceAfter.dot(differenceAfter);
			squaredRatios.push_back(squaredDistanceAfter / squaredDistanceBefore);
		}
	}

	// compute median ratio to complete the median flow
	sort(squaredRatios.begin(), squaredRatios.end());
	float medianRatio = sqrt(squaredRatios[squaredRatios.size() / 2]);

	// predict samples according to median flow and random noise
	for (shared_ptr<Sample> sample : samples) {
		// add noise to velocity
		double vx = medianX;
		double vy = medianY;
		double vs = medianRatio;
		// diffuse
		vx += positionDeviation * generator();
		vy += positionDeviation * generator();
		vs *= pow(2, sizeDeviation * generator());
		// round to integer
		sample->setVx(static_cast<int>(std::round(vx)));
		sample->setVy(static_cast<int>(std::round(vy)));
		sample->setVSize(vs);
		// change position according to velocity
		sample->setX(sample->getX() + sample->getVx());
		sample->setY(sample->getY() + sample->getVy());
		sample->setSize(static_cast<int>(std::round(sample->getSize() * sample->getVSize())));
	}
}
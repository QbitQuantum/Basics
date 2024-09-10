tf::Transform SvdTransformOptimization::svdOwnImpl(
		std::vector<tf::Vector3> pointcloudX,
		std::vector<tf::Vector3> pointcloudP) {

	// Calculate center of mass for both pointclouds.
	int numOfPoints = pointcloudX.size();
	tf::Vector3 centerOfMassX, centerOfMassP;
	for (int i = 0; i < numOfPoints; i++) {
		centerOfMassX += pointcloudX[i];
		centerOfMassP += pointcloudP[i];
	}
	centerOfMassX /= numOfPoints;
	centerOfMassP /= numOfPoints;

	// Extract the center of mass from the corresponding points.
	std::vector<tf::Vector3> pointcloudXPrime, pointcloudPPrime;
	for (int i = 0; i < numOfPoints; i++) {
		pointcloudXPrime.push_back(pointcloudX[i] - centerOfMassX);
		pointcloudPPrime.push_back(pointcloudP[i] - centerOfMassP);
	}

	// Calculate matrix W
	Eigen::MatrixXf W = Eigen::MatrixXf::Zero(3, 3);
	for (int i = 0; i < numOfPoints; i++) {
		Eigen::Vector3f currentPointXPrime(pointcloudXPrime[i].getX(),
				pointcloudXPrime[i].getY(), pointcloudXPrime[i].getZ());
		Eigen::Vector3f currentPointPPrime(pointcloudPPrime[i].getX(),
				pointcloudPPrime[i].getY(), pointcloudPPrime[i].getZ());
		W += currentPointXPrime * currentPointPPrime.transpose();
	}

	// Perform the SVD.
	Eigen::JacobiSVD<Eigen::MatrixXf> svd(W);
	svd.compute(W, Eigen::ComputeFullU | Eigen::ComputeFullV);
	Eigen::MatrixXf U = svd.matrixU();
	Eigen::MatrixXf V = svd.matrixV();

	// Caclulate Rotation and translation and convert to tf.
	Eigen::MatrixXf R = U * V.transpose();
	Eigen::Vector3f centerOfMassXEigen(centerOfMassX.getX(),
			centerOfMassX.getY(), centerOfMassX.getZ());
	Eigen::Vector3f centerOfMassPEigen(centerOfMassP.getX(),
			centerOfMassP.getY(), centerOfMassP.getZ());
	Eigen::MatrixXf t = centerOfMassXEigen - R * (centerOfMassPEigen);

	tf::Matrix3x3 Rtf(R(0, 0), R(0, 1), R(0, 2), R(1, 0), R(1, 1), R(1, 2),
			R(2, 0), R(2, 1), R(2, 2));
	tf::Vector3 ttf(t(0), t(1), t(2));

	// Create and return the new transform.
	tf::Transform newTransform(Rtf, ttf);
	return newTransform;
}
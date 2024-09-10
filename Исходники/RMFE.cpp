Eigen::Matrix3d RMFE::getRotationMatrix() {
	// Paper: Robust Manhattan Frame Estimation from a Single RGB-D Image
	double lambda = 0.3;
	Eigen::MatrixXd N = this->getNormalMatrix();
	Eigen::Matrix3d R = Eigen::Matrix<double, 3, 3>::Identity();

	float last_error = 10000.0f, error_diff = 10000.0f;
	while (error_diff > 0.0001 || error_diff < 0) {
		Eigen::MatrixXd X = R * N;
		RMFE::applySoftThresholding(X, lambda);
		Eigen::MatrixXd XNTranspose = X * N.transpose();
		Eigen::JacobiSVD<Eigen::MatrixXd> svd(XNTranspose,
				Eigen::ComputeFullU | Eigen::ComputeFullV);
		Eigen::MatrixXd U = svd.matrixU();
		Eigen::MatrixXd V = svd.matrixV();
		Eigen::VectorXd D = svd.singularValues();

		/*std::cout << "U: " << U << std::endl;
		 std::cout << "V: " << V << std::endl;
		 std::cout << "D: " << D << std::endl;*/

		//std::cout << "Remaining: " << (U * D.asDiagonal() * V.transpose() - XNTranspose) << std::endl;
		Eigen::Matrix3d S = Eigen::Matrix<double, 3, 3>::Identity();
		if (XNTranspose.determinant() < 0) {
			S(2, 2) = -1;
		}

		R = U * S * V.transpose();

		float L1NormSum = 0;
		for (int j = 0; j < X.rows(); j++) {
			L1NormSum += X.row(j).lpNorm<1>();
		}
		float error = 0.5 * std::pow((R * N - X).lpNorm<2>(), 2)
				+ lambda * L1NormSum;

		error_diff = last_error - error;
		last_error = error;

		/*std::cout << "Iteration: " << iter << std::endl;
		 std::cout << "R: " << R << std::endl;
		 //std::cout << "X: " << X << std::endl;
		 std::cout << "Error: " << error << std::endl;*/
	}

	return R;
}
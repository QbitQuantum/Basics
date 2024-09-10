MatrixXd CMT::MLR::sample(const MatrixXd& input) const {
	if(input.rows() != mDimIn)
		throw Exception("Inputs have wrong dimensionality.");

	// distribution over outputs
	ArrayXXd prob = predict(input);

	MatrixXd output = MatrixXd::Zero(mDimOut, input.cols());

	#pragma omp parallel for
	for(int j = 0; j < input.cols(); ++j) {
		double urand = static_cast<double>(rand()) / RAND_MAX;
		double cdf = 0.;

		for(int k = 0; k < mDimOut; ++k) {
			cdf += prob(k, j);

			if(urand < cdf) {
				output(k, j) = 1.;
				break;
			}
		}
	}

	return output;
}
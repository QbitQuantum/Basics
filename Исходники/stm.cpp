void CMT::STM::initialize(const MatrixXd& input, const MatrixXd& output) {
	if(input.rows() != dimIn() || output.rows() != dimOut())
		throw Exception("Data has wrong dimensionality.");
	if(input.cols() != output.cols())
		throw Exception("The number of inputs and outputs should be the same.");

	Array<bool, 1, Dynamic> spikes = output.array() > 0.5;
	int numSpikes = spikes.sum();

	if(numSpikes > dimInNonlinear() && dimInNonlinear() > 0) {
		mSharpness = 1.;
		MatrixXd inputNonlinear = input.topRows(dimInNonlinear());
		MatrixXd inputs1(inputNonlinear.rows(), numSpikes);
		MatrixXd inputs0(inputNonlinear.rows(), spikes.size() - numSpikes);

		// separate data into spike-triggered and non-spike-triggered stimuli
		for(int i = 0, i0 = 0, i1 = 0; i < spikes.size(); ++i)
			if(spikes[i])
				inputs1.col(i1++) = inputNonlinear.col(i);
			else
				inputs0.col(i0++) = inputNonlinear.col(i);

		// spike-triggered/non-spike-triggered mean and precision
		VectorXd m1 = inputs1.rowwise().mean();
		VectorXd m0 = inputs0.rowwise().mean();

		MatrixXd S1 = covariance(inputs1).inverse();
		MatrixXd S0 = covariance(inputs0).inverse();

		// parameters of a quadratic model
		MatrixXd K = (S0 - S1) / 2.;
		VectorXd w = S1 * m1 - S0 * m0;
		double p = static_cast<float>(numSpikes) / output.cols();
		double a = 0.5 * (m0.transpose() * S0 * m0)(0, 0) - 0.5 * (m1.transpose() * S1 * m1)(0, 0)
			+ 0.5 * logDetPD(S1) - 0.5 * logDetPD(S0) + log(p) - log(1. - p)
			- log(mNumComponents);

		// decompose matrix into eigenvectors
		SelfAdjointEigenSolver<MatrixXd> eigenSolver(K);
		VectorXd eigVals = eigenSolver.eigenvalues();
		MatrixXd eigVecs = eigenSolver.eigenvectors();
		VectorXi indices = argSort(eigVals.array().abs());

		// use most informative eigenvectors as features
		for(int i = 0; i < mNumFeatures && i < indices.size(); ++i) {
			int j = indices[i];
			mWeights.col(i).setConstant(eigVals[j]);
			mFeatures.col(i) = eigVecs.col(j);
		}

		mWeights = mWeights.array() * (0.5 + 0.5 * ArrayXXd::Random(mNumComponents, mNumFeatures).abs());
		mPredictors.rowwise() = w.transpose();
		mPredictors += sampleNormal(mNumComponents, mDimInNonlinear).matrix() * log(mNumComponents) / 10.;
		mBiases.setConstant(a);
		mBiases += VectorXd::Random(mNumComponents) * log(mNumComponents) / 100.;
	}

	if(dimInLinear() > 0)
		mLinearPredictor = input.bottomRows(dimInLinear()) * output.transpose() / numSpikes;
}
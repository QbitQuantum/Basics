	void calcMeanAndCovarWeighedVectorized(const Eigen::MatrixXf &input, const Eigen::VectorXd &inputWeights, Eigen::MatrixXf &out_covMat, Eigen::VectorXf &out_mean,Eigen::MatrixXf &temp)
	{
		out_mean=input.col(0); //to resize
		out_mean.setZero();
		double wSumInv=1.0/inputWeights.sum();
		for (int k=0;k<inputWeights.size();k++){
			double w=inputWeights[k];
			out_mean+=input.col(k)*(float)(w*wSumInv);
		}
		out_mean = input.rowwise().mean();
		temp = (input.colwise() - out_mean);
		for (int k=0;k<inputWeights.size();k++){
			temp.col(k) *= (float)(sqrt(inputWeights(k)*wSumInv));	//using square roots, as we only want the normalized weights to be included once for each result element in the multiplication below
		}
		out_covMat = temp*temp.transpose();
	}
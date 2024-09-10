void ConvPoolLayer::bp_bias(const vector<MatrixXd>& grad_conved, const int& num_kernel, MatrixXd& grad_bias_single)
{
	grad_bias_single.setZero(num_kernel, 1);
	double grad_bias_partial;
	int num_input = grad_conved.size() / num_kernel;
	for(int i = 0; i < num_kernel; i++)
	{
		for(int j = 0; j < num_input; j++)
		{
			int index = i * num_input + j;
			grad_bias_partial = grad_conved[index].sum();
			grad_bias_single(i, 0) += grad_bias_partial;
		}
	}
}
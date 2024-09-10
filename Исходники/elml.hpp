int elmTrain( double *X, int dims, int nsmp, 
       	      double *Y,
	      const int nhn, const double C,
	      MatrixBase<Derived> &inW, MatrixBase<Derived> &bias, MatrixBase<Derived> &outW ) {

	// map the samples into the matrix object
	MatrixXd mX = Map<MatrixXd>( X, dims, nsmp );

	// build target matrix
	MatrixXd mTargets = buildTargetMatrix( Y, nsmp );

	// generate random input weight matrix - inW
	inW = MatrixXd::Random( nhn, dims );

	// generate random bias vectors
	bias = MatrixXd::Random( nhn, 1 );

	// compute the pre-H matrix
	MatrixXd preH = inW * mX;

	// compute hidden neuron output
	MatrixXd H = (1 + (-preH.array()).exp()).cwiseInverse();

	// build matrices to solve Ax = b
	MatrixXd A = (MatrixXd::Identity(nhn,nhn)).array()*(1/C) + (H * H.transpose()).array();
	MatrixXd b = H * mTargets.transpose();
	
	// solve the output weights as a solution to a system of linear equations
	outW = A.llt().solve( b );
	
	return 0;

}
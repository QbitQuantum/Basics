VectorXf project1D( const RMatrixXf & Y, int * rep_label=NULL ) {
// 	const int MAX_SAMPLE = 20000;
	const bool fast = true, very_fast = true;
	// Remove the DC (Y : N x M)
	RMatrixXf dY = Y.rowwise() - Y.colwise().mean();
// 	RMatrixXf sY = dY;
// 	if( 0 < MAX_SAMPLE && MAX_SAMPLE < dY.rows() ) {
// 		VectorXi samples = randomChoose( dY.rows(), MAX_SAMPLE );
// 		std::sort( samples.data(), samples.data()+samples.size() );
// 		sY = RMatrixXf( samples.size(), dY.cols() );
// 		for( int i=0; i<samples.size(); i++ )
// 			sY.row(i) = dY.row( samples[i] );
// 	}
	
	// ... and use (pc > 0)
	VectorXf lbl = VectorXf::Zero( Y.rows() );
	
	// Find the largest PC of (dY.T * dY) and project onto it
	if( very_fast ) {
		// Find the largest PC using poweriterations
		VectorXf U = VectorXf::Random( dY.cols() );
		U = U.array() / U.norm()+std::numeric_limits<float>::min();
		for( int it=0; it<20; it++ ){
			// Normalize
			VectorXf s = dY.transpose()*(dY*U);
			s.array() /= s.norm()+std::numeric_limits<float>::min();
			if ( (U-s).norm() < 1e-6 )
				break;
			U = s;
		}
		// Project onto the PC
		lbl = dY*U;
	}
	else if(fast) {
		// Compute the eigen values of the covariance (and project onto the largest eigenvector)
		MatrixXf cov = dY.transpose()*dY;
		SelfAdjointEigenSolver<MatrixXf> eigensolver(0.5*(cov+cov.transpose()));
		MatrixXf ev = eigensolver.eigenvectors();
		lbl = dY * ev.col( ev.cols()-1 );
	}
	else {
		// Use the SVD
		JacobiSVD<RMatrixXf> svd = dY.jacobiSvd(ComputeThinU | ComputeThinV );
		// Project onto the largest PC
		lbl = svd.matrixU().col(0) * svd.singularValues()[0];
	}
	// Find the representative label
	if( rep_label )
		dY.array().square().rowwise().sum().minCoeff( rep_label );
	
	return (lbl.array() < 0).cast<float>();
}
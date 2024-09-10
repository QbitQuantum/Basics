MatrixXd _sym_decorrelation(MatrixXd w_init){
	
	MatrixXd wt;
	MatrixXd W;
	int n = dimensions.n;
	int i,j;
	
	MatrixXd s(1,n);	//eigenvalues
	MatrixXd u(n,n);	//eigenvectors
	MatrixXcd values;	//complex array returned by eigenvalues
	MatrixXcd vectors;	//complex array returned by eigenvectors
	
	wt = w_init.transpose();
	W	= w_init * wt;
	
	/*
	Since Eigenvalue compute give complex structure
	We should parse it into MatrixXd type
	*/
	EigenSolver<MatrixXd> eigenSolver(W,true);	//initializing eigen solver
	
	values = eigenSolver.eigenvalues();
	for(i=0;i<n;i++){
		s(0,n-i-1)= values(i,0).real();
	}
	
	vectors = eigenSolver.eigenvectors();
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			u(i,j) = vectors(i,n-j-1).real();
		}
	}
	
	return (arrayMultiplierRowWise(u,(1/sqrt(s.array())),n) * u.transpose())*w_init;
}
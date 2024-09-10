std::vector<double>  Decomposition::QR_decomposition(std::vector<std::vector<double> > A, int n){
	std::vector<double> R(n, .0);
	std::vector<double> c(n, .0);
	double scale, sigma, tau;
	for(unsigned short int k = 0; k < n ; k++){
		scale = 0.0;
		for(unsigned short int i=k; i<n; i++) scale = FMAX(scale, ABS(A[i][k]));
		if(scale == 0.0){
			c[k] = R[k] = .0;
		} else {	// form !_k and Q_k.A
			for (int i = k; i < n; i++)	A[i][k] /= scale;
			double sum = .0;
			for(unsigned short int i = k; i < n; i++){ // calculating the norm of column 'k'
				sum += pow(A[i][k], 2.0);
			}
			sigma = SIGN(sqrt(sum), A[k][k]);
			A[k][k] += sigma;
			c[k] = sigma * A[k][k];
			R[k] = scale*sigma;
			for(unsigned short int j = k+1; j<n;j++){	// calculate Q_k.A
				double sum = .0;
				for(unsigned short int i = k; i<n; i++){
					sum += A[i][k]*A[i][j];
				}
				tau = sum/c[k];
				for(unsigned short int i = k; i<n; i++){
					A[i][j] -= tau*A[i][k];
				}
			}
		}
	}
	return R;
}
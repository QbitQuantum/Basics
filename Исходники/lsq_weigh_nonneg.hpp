VectorXd lsq_weigh_nonneg(const MatrixXd& A, const VectorXd& b, const VectorXd& w)
{
	const unsigned m = A.rows();
	const unsigned n = A.cols();
	if(b.size() != m || w.size() != m || n < 1 || m < 1)
	{
		std::cerr<<"#error in lsq_weigh_nonneg: If A is a m by n matrix, then b and w must have length m. We also want n >= 1 and m >= 1. A is "<< m <<" by "<< n <<", b has length "<< b.size() <<" and w has length "<< w.size() <<"."<<std::endl;
		throw std::invalid_argument("lsq_weigh_nonneg: dimension mismatch");
	}
	
	// initialization
	const MatrixXd H = A.transpose() * w.asDiagonal() * A;
	const VectorXd f = - A.transpose() * w.asDiagonal() * b;
	VectorXd x = VectorXd::Zero(n), mu = f;
	
	// iterate
	double relerr;
	do
	{
		for(unsigned k = 0; k < n; ++k)
		{
			const double xtmp = x(k);
			x(k) -= mu(k) / H(k,k);
			if(x(k) < 0) x(k) = 0;
			const double d = x(k) - xtmp;
			if(d != 0) mu += d * H.col(k);
		}
		
		relerr = 0;
		for(unsigned k = 0; k < n; ++k)
		{
			if(x(k) != 0)
			{
				double err = mu(k) / x(k);
				if(err < 0) err = -err;
				if(err > relerr) relerr = err;
			}
		}
	}
	while(relerr >= 1e-2);
	
	// update non-zero columns with more costly, but also more precise calculation
	const VectorXi p = find(x.array() > 0);
	const VectorXd xp = lscov(pick_col(A, p), b, w);
	if(find(xp.array() >= 0).all()) set_ind(x, p, xp);
	
	return x;
}
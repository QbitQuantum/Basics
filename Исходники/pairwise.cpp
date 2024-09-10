	virtual VectorXf gradient( const MatrixXf & a, const MatrixXf & b ) const {
		if (ktype_ == CONST_KERNEL)
			return VectorXf();
		MatrixXf fg = featureGradient( a, b );
		if (ktype_ == DIAG_KERNEL)
			return (f_.array()*fg.array()).rowwise().sum();
		else {
			MatrixXf p = fg*f_.transpose();
			p.resize( p.cols()*p.rows(), 1 );
			return p;
		}
	}
	virtual double gradient( const Eigen::VectorXf & x, Eigen::VectorXf & dx ) {
		int p = 0;
		if (unary_) {
			crf_.setUnaryParameters( x.segment( p, initial_u_param_.rows() ) );
			p += initial_u_param_.rows();
		}
		if (pairwise_) {
			crf_.setLabelCompatibilityParameters( x.segment( p, initial_lbl_param_.rows() ) );
			p += initial_lbl_param_.rows();
		}
		if (kernel_)
			crf_.setKernelParameters( x.segment( p, initial_knl_param_.rows() ) );
		
		Eigen::VectorXf du = 0*initial_u_param_, dl = 0*initial_u_param_, dk = 0*initial_knl_param_;
		double r = crf_.gradient( NIT_, objective_, unary_?&du:NULL, pairwise_?&dl:NULL, kernel_?&dk:NULL );
		dx.resize( unary_*du.rows() + pairwise_*dl.rows() + kernel_*dk.rows() );
		dx << -(unary_?du:Eigen::VectorXf()), -(pairwise_?dl:Eigen::VectorXf()), -(kernel_?dk:Eigen::VectorXf());
		r = -r;
		if( l2_norm_ > 0 ) {
			dx += l2_norm_ * x;
			r += 0.5*l2_norm_ * (x.dot(x));
		}
		
		return r;
	}
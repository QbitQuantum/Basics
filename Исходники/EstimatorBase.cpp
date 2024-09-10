void
EstimatorFull::UpdateCamera(const Eigen::Vector3d &p_c_v, const Eigen::Quaterniond &q_c_v,
	const Eigen::Matrix<double,6,6> &R,
	bool absolute, bool isKeyframe, double dLambda )
{
	Eigen::QuaternionAd q_c_kf;
	Eigen::Vector3d p_c_kf;
	if (absolute)
	{
		q_c_kf = Eigen::QuaternionAd(q_c_v.conjugate() * q_kf_v.toQuat().conjugate());
	    p_c_kf = q_kf_v.toQuat().toRotationMatrix() * (p_c_v - p_kf_v);
	}
	else
	{
		q_c_kf.q = q_c_v;
		p_c_kf = p_c_v;
	}

	Matrix3d C_q_w_v = q_w_v.toQuat().toRotationMatrix();
	Matrix3d C_q_i_w = q_i_w.toQuat().toRotationMatrix();
	Matrix3d C_q_c_i = q_c_i.toQuat().toRotationMatrix();

	// Build Jacobian
	Matrix<double,3,28> H_p;
	H_p <<
	C_q_w_v.transpose() * exp(lambda),
	Matrix3d::Zero(),
	-C_q_w_v.transpose()*C_q_i_w.transpose()*crossMat(p_c_i)*exp(lambda),
	Matrix3d::Zero(),
	Matrix3d::Zero(),
	(C_q_w_v.transpose()*(C_q_i_w.transpose()*p_c_i + p_i_w) + p_w_v) * exp(lambda),
	C_q_w_v.transpose()*C_q_i_w.transpose()*exp(lambda),
	Matrix3d::Zero(),
	Matrix3d::Identity()*exp(lambda),
	-C_q_w_v.transpose()*crossMat( p_i_w + C_q_i_w.transpose()*p_c_i )*exp(lambda);

	Matrix<double,3,28> H_q;
	H_q <<
	Matrix3d::Zero(),
	Matrix3d::Zero(),
	C_q_c_i,
	Matrix3d::Zero(),
	Matrix3d::Zero(),
	Vector3d::Zero(),
	Matrix3d::Zero(),
	Matrix3d::Identity(),
	Matrix3d::Zero(),
	C_q_c_i*C_q_i_w;

	Matrix<double,6,28> H;
	H << H_p, H_q;

	// Calculate residual

	Vector3d r_p = p_c_kf - ( C_q_w_v.transpose()*(p_i_w + C_q_i_w.transpose()*p_c_i) + p_w_v ) * exp(lambda);
	Quaterniond r_q = (q_c_kf.toQuat()*( q_c_i.toQuat()*q_i_w.toQuat()*q_w_v.toQuat() ).conjugate()).conjugate();

	Matrix<double,6,1> r;
	r << r_p, 2*r_q.x(), 2*r_q.y(), 2*r_q.z();

	// Calculate kalmn gain
	Matrix<double,6,6> S = H*P*H.transpose() + R;
	//K = P*H.transpose()*S^-1;
	//TODO: use cholsky to solve K*S = P*H.transposed()? 
	// (K*S)' = (P*H')'
	// S'*K' = H*P'
	// K' = S.transpose.ldlt().solve(H*P.transpose)
	Matrix<double,28,6> K = (S.ldlt().solve(H*P)).transpose(); // P and S are symmetric
	//Matrix<double,28,6> K = P*H.transpose()*S.inverse();//S.lu().solve(H*P).transpose();
	
	Matrix<double,28,1>	x_error = K*r;

	// Apply Kalman gain
	ApplyCorrection( x_error );
	Matrix<double,28,28> T = Matrix<double,28,28>::Identity() - K*H;
	P = T*P*T.transpose() + K*R*K.transpose();

	// Symmetrize
	P = (P + P.transpose())/2.0;

	if (isKeyframe)
	{
		// Add new keyframe from current position/camera pose
		UpdateKeyframe( );

		// Add noise to lambda
		P(15,15) += dLambda;

		// Update keyframe reference, if given path is absolute
		if (absolute)
		{
			p_kf_v = p_c_v;
			q_kf_v.q = q_c_v;
		}
	}
}
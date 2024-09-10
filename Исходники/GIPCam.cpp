void GIPCam::SetParams(float fx, float fy, float cx, float cy, uint width, uint height) {
	// TODO: NOTE: WE IGNORE THE SKEW TERM IN THE GIVEN K MATRIX

	const float scale_x = 240.f; //      // width*( 1.f/(MAX_X-MIN_X) ); // width*0.5.
	const float scale_y = 240.f; // height*( 1.f/(MAX_Y-MIN_Y) ); // height*0.75*0.5.
	
	const float new_fx = scale_x * fx;
	const float new_fy = scale_y * fy;

	const int new_cx = (int)(scale_x*cx + 180.f); // (float)width/2;
	const int new_cy = (int)(scale_y*cy + 240.f); //(float)height/2;

	//m_params.m_height = height;
	//m_params.m_width = width;
	m_params.m_intrinsic.Set(-new_fx, -new_fy, new_cx, new_cy);

	Eigen::Matrix<float, 3, 3, Eigen::RowMajor> intrinsic;
	intrinsic.setZero();
	intrinsic(0,0) = m_params.m_intrinsic.m_fx;
	intrinsic(1,1) = m_params.m_intrinsic.m_fy;
	intrinsic(2,2) = 1.f;
	intrinsic(0,2) = m_params.m_intrinsic.m_cx;
	intrinsic(1,2) = m_params.m_intrinsic.m_cy;

	Eigen::Matrix<float, 3, 3, Eigen::RowMajor> invIntrinsic = intrinsic.inverse();

	m_params.m_invIntrinsic.Set(invIntrinsic(0,0), invIntrinsic(1,1), invIntrinsic(0,2), invIntrinsic(1,2));
}
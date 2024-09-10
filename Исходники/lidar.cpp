void BlockLocalPositionEstimator::lidarCorrect()
{
	// measure lidar
	Vector<float, n_y_lidar> y;

	if (lidarMeasure(y) != OK) { return; }

	// account for leaning
	y(0) = y(0) *
	       cosf(_sub_att.get().roll) *
	       cosf(_sub_att.get().pitch);

	// measurement matrix
	Matrix<float, n_y_lidar, n_x> C;
	C.setZero();
	// y = -(z - tz)
	// TODO could add trig to make this an EKF correction
	C(Y_lidar_z, X_z) = -1; // measured altitude, negative down dir.
	C(Y_lidar_z, X_tz) = 1; // measured altitude, negative down dir.

	// use parameter covariance unless sensor provides reasonable value
	Matrix<float, n_y_lidar, n_y_lidar> R;
	R.setZero();
	float cov = _sub_lidar->get().covariance;

	if (cov < 1.0e-3f) {
		R(0, 0) = _lidar_z_stddev.get() * _lidar_z_stddev.get();

	} else {
		R(0, 0) = cov;
	}

	// residual
	Matrix<float, n_y_lidar, n_y_lidar> S_I = inv<float, n_y_lidar>((C * _P * C.transpose()) + R);
	Vector<float, n_y_lidar> r = y - C * _x;

	// fault detection
	float beta = (r.transpose() * (S_I * r))(0, 0);

	if (beta > BETA_TABLE[n_y_lidar]) {
		if (_lidarFault < FAULT_MINOR) {
			_lidarFault = FAULT_MINOR;
			mavlink_and_console_log_info(&mavlink_log_pub, "[lpe] lidar fault,  beta %5.2f", double(beta));
		}

		// abort correction
		return;

	} else if (_lidarFault) { // disable fault if ok
		_lidarFault = FAULT_NONE;
		//mavlink_and_console_log_info(&mavlink_log_pub, "[lpe] lidar OK");
	}

	// kalman filter correction if no fault
	if (_lidarFault < fault_lvl_disable) {
		Matrix<float, n_x, n_y_lidar> K = _P * C.transpose() * S_I;
		Vector<float, n_x> dx = K * r;

		if (!_canEstimateXY) {
			dx(X_x) = 0;
			dx(X_y) = 0;
			dx(X_vx) = 0;
			dx(X_vy) = 0;
		}

		_x += dx;
		_P -= K * C * _P;
	}
}
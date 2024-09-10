void BlockLocalPositionEstimator::baroCorrect()
{
	// measure
	Vector<float, n_y_baro> y;

	if (baroMeasure(y) != OK) { return; }

	// subtract baro home alt
	y -= _baroAltHome;

	// baro measurement matrix
	Matrix<float, n_y_baro, n_x> C;
	C.setZero();
	C(Y_baro_z, X_z) = -1; // measured altitude, negative down dir.

	Matrix<float, n_y_baro, n_y_baro> R;
	R.setZero();
	R(0, 0) = _baro_stddev.get() * _baro_stddev.get();

	// residual
	Matrix<float, n_y_baro, n_y_baro> S_I =
		inv<float, n_y_baro>((C * _P * C.transpose()) + R);
	Vector<float, n_y_baro> r = y - (C * _x);

	// fault detection
	float beta = (r.transpose() * (S_I * r))(0, 0);

	if (beta > BETA_TABLE[n_y_baro]) {
		if (_baroFault < FAULT_MINOR) {
			//mavlink_and_console_log_info(&mavlink_log_pub, "[lpe] baro fault, r %5.2f m, beta %5.2f",
			//double(r(0)), double(beta));
			_baroFault = FAULT_MINOR;
		}

	} else if (_baroFault) {
		_baroFault = FAULT_NONE;
		//mavlink_and_console_log_info(&mavlink_log_pub, "[lpe] baro OK");
	}

	// kalman filter correction if no fault
	if (_baroFault < fault_lvl_disable) {
		Matrix<float, n_x, n_y_baro> K = _P * C.transpose() * S_I;
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
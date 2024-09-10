void BlockLocalPositionEstimator::landingTargetCorrect()
{
	if (_param_ltest_mode.get() == Target_Moving) {
		// nothing to do in this mode
		return;
	}

	// measure
	Vector<float, n_y_target> y;

	if (landingTargetMeasure(y) != OK) { return; }

	// calculate covariance
	float cov_vx = _sub_landing_target_pose.get().cov_vx_rel;
	float cov_vy = _sub_landing_target_pose.get().cov_vy_rel;

	// use sensor value only if reasoanble
	if (cov_vx < _param_lpe_lt_cov.get() || cov_vy < _param_lpe_lt_cov.get()) {
		cov_vx = _param_lpe_lt_cov.get();
		cov_vy = _param_lpe_lt_cov.get();
	}

	// target measurement matrix and noise matrix
	Matrix<float, n_y_target, n_x> C;
	C.setZero();
	// residual = (y + vehicle velocity)
	// sign change because target velocitiy is -vehicle velocity
	C(Y_target_x, X_vx) = -1;
	C(Y_target_y, X_vy) = -1;

	// covariance matrix
	SquareMatrix<float, n_y_target> R;
	R.setZero();
	R(0, 0) = cov_vx;
	R(1, 1) = cov_vy;

	// residual
	Vector<float, n_y_target> r = y - C * _x;

	// residual covariance, (inverse)
	Matrix<float, n_y_target, n_y_target> S_I =
		inv<float, n_y_target>(C * _P * C.transpose() + R);

	// fault detection
	float beta = (r.transpose()  * (S_I * r))(0, 0);

	if (beta > BETA_TABLE[n_y_target]) {
		if (!(_sensorFault & SENSOR_LAND_TARGET)) {
			mavlink_and_console_log_info(&mavlink_log_pub, "Landing target fault, beta %5.2f", double(beta));
			_sensorFault |= SENSOR_LAND_TARGET;
		}

		// abort correction
		return;

	} else if (_sensorFault & SENSOR_LAND_TARGET) {
		_sensorFault &= ~SENSOR_LAND_TARGET;
		mavlink_and_console_log_info(&mavlink_log_pub, "Landing target OK");
	}

	// kalman filter correction
	Matrix<float, n_x, n_y_target> K =
		_P * C.transpose() * S_I;
	Vector<float, n_x> dx = K * r;
	_x += dx;
	_P -= K * C * _P;

}
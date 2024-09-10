void BlockLocalPositionEstimator::mocapCorrect()
{
	// measure
	Vector<float, n_y_mocap> y;

	if (mocapMeasure(y) != OK) {
		mavlink_and_console_log_info(&mavlink_log_pub, "[lpe] mocap data invalid. eph: %f epv: %f", _mocap_eph, _mocap_epv);
		return;
	}

	// mocap measurement matrix, measures position
	Matrix<float, n_y_mocap, n_x> C;
	C.setZero();
	C(Y_mocap_x, X_x) = 1;
	C(Y_mocap_y, X_y) = 1;
	C(Y_mocap_z, X_z) = 1;

	// noise matrix
	Matrix<float, n_y_mocap, n_y_mocap> R;
	R.setZero();

	// use std dev from mocap data if available
	if (_mocap_eph > _param_lpe_vic_p.get()) {
		R(Y_mocap_x, Y_mocap_x) = _mocap_eph * _mocap_eph;
		R(Y_mocap_y, Y_mocap_y) = _mocap_eph * _mocap_eph;

	} else {
		R(Y_mocap_x, Y_mocap_x) = _param_lpe_vic_p.get() * _param_lpe_vic_p.get();
		R(Y_mocap_y, Y_mocap_y) = _param_lpe_vic_p.get() * _param_lpe_vic_p.get();
	}

	if (_mocap_epv > _param_lpe_vic_p.get()) {
		R(Y_mocap_z, Y_mocap_z) = _mocap_epv * _mocap_epv;

	} else {
		R(Y_mocap_z, Y_mocap_z) = _param_lpe_vic_p.get() * _param_lpe_vic_p.get();
	}

	// residual
	Vector<float, n_y_mocap> r = y - C * _x;
	// residual covariance
	Matrix<float, n_y_mocap, n_y_mocap> S = C * _P * C.transpose() + R;

	// publish innovations
	for (size_t i = 0; i < 3; i++) {
		_pub_innov.get().vel_pos_innov[i] = r(i);
		_pub_innov.get().vel_pos_innov_var[i] = S(i, i);
	}

	for (size_t i = 3; i < 6; i++) {
		_pub_innov.get().vel_pos_innov[i] = 0;
		_pub_innov.get().vel_pos_innov_var[i] = 1;
	}

	// residual covariance, (inverse)
	Matrix<float, n_y_mocap, n_y_mocap> S_I = inv<float, n_y_mocap>(S);

	// fault detection
	float beta = (r.transpose() * (S_I * r))(0, 0);

	if (beta > BETA_TABLE[n_y_mocap]) {
		if (!(_sensorFault & SENSOR_MOCAP)) {
			//mavlink_and_console_log_info(&mavlink_log_pub, "[lpe] mocap fault, beta %5.2f", double(beta));
			_sensorFault |= SENSOR_MOCAP;
		}

	} else if (_sensorFault & SENSOR_MOCAP) {
		_sensorFault &= ~SENSOR_MOCAP;
		//mavlink_and_console_log_info(&mavlink_log_pub, "[lpe] mocap OK");
	}

	// kalman filter correction always
	Matrix<float, n_x, n_y_mocap> K = _P * C.transpose() * S_I;
	Vector<float, n_x> dx = K * r;
	_x += dx;
	_P -= K * C * _P;
}
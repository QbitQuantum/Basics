void BlockLocalPositionEstimator::gpsCorrect()
{
	// measure
	Vector<double, n_y_gps> y_global;

	if (gpsMeasure(y_global) != OK) { return; }

	// gps measurement in local frame
	double  lat = y_global(0);
	double  lon = y_global(1);
	float  alt = y_global(2);
	float px = 0;
	float py = 0;
	float pz = -(alt - _gpsAltHome);
	map_projection_project(&_map_ref, lat, lon, &px, &py);
	Vector<float, 6> y;
	y.setZero();
	y(0) = px;
	y(1) = py;
	y(2) = pz;
	y(3) = y_global(3);
	y(4) = y_global(4);
	y(5) = y_global(5);

	// gps measurement matrix, measures position and velocity
	Matrix<float, n_y_gps, n_x> C;
	C.setZero();
	C(Y_gps_x, X_x) = 1;
	C(Y_gps_y, X_y) = 1;
	C(Y_gps_z, X_z) = 1;
	C(Y_gps_vx, X_vx) = 1;
	C(Y_gps_vy, X_vy) = 1;
	C(Y_gps_vz, X_vz) = 1;

	// gps covariance matrix
	Matrix<float, n_y_gps, n_y_gps> R;
	R.setZero();

	// default to parameter, use gps cov if provided
	float var_xy = _gps_xy_stddev.get() * _gps_xy_stddev.get();
	float var_z = _gps_z_stddev.get() * _gps_z_stddev.get();
	float var_vxy = _gps_vxy_stddev.get() * _gps_vxy_stddev.get();
	float var_vz = _gps_vz_stddev.get() * _gps_vz_stddev.get();

	// if field is not zero, set it to the value provided
	if (_sub_gps.get().eph > 1e-3f) {
		var_xy = _sub_gps.get().eph * _sub_gps.get().eph;
	}

	if (_sub_gps.get().epv > 1e-3f) {
		var_z = _sub_gps.get().epv * _sub_gps.get().epv;
	}

	R(0, 0) = var_xy;
	R(1, 1) = var_xy;
	R(2, 2) = var_z;
	R(3, 3) = var_vxy;
	R(4, 4) = var_vxy;
	R(5, 5) = var_vz;

	// get delayed x and P
	float t_delay = 0;
	int i = 0;

	for (i = 1; i < HIST_LEN; i++) {
		t_delay = 1.0e-6f * (_timeStamp - _tDelay.get(i)(0, 0));

		if (t_delay > _gps_delay.get()) {
			break;
		}
	}

	// if you are 3 steps past the delay you wanted, this
	// data is probably too old to use
	if (t_delay > GPS_DELAY_MAX) {
		mavlink_and_console_log_info(&mavlink_log_pub, "[lpe] gps delayed data too old: %8.4f", double(t_delay));
		return;
	}

	Vector<float, n_x> x0 = _xDelay.get(i);

	// residual
	Vector<float, n_y_gps> r = y - C * x0;
	Matrix<float, n_y_gps, n_y_gps> S_I = inv<float, 6>(C * _P * C.transpose() + R);

	// fault detection
	float beta = (r.transpose() * (S_I * r))(0, 0);

	if (beta > BETA_TABLE[n_y_gps]) {
		if (_gpsFault < FAULT_MINOR) {
			//mavlink_and_console_log_info(&mavlink_log_pub, "[lpe] gps fault, beta: %5.2f", double(beta));
			//mavlink_and_console_log_info(&mavlink_log_pub, "[lpe] r: %5.2f %5.2f %5.2f %5.2f %5.2f %5.2f",
			//double(r(0)),  double(r(1)), double(r(2)),
			//double(r(3)), double(r(4)), double(r(5)));
			//mavlink_and_console_log_info(&mavlink_log_pub, "[lpe] S_I: %5.2f %5.2f %5.2f %5.2f %5.2f %5.2f",
			//double(S_I(0, 0)),  double(S_I(1, 1)), double(S_I(2, 2)),
			//double(S_I(3, 3)),  double(S_I(4, 4)), double(S_I(5, 5)));
			_gpsFault = FAULT_MINOR;
		}

	} else if (_gpsFault) {
		_gpsFault = FAULT_NONE;
		//mavlink_and_console_log_info(&mavlink_log_pub, "[lpe] GPS OK");
	}

	// kalman filter correction if no hard fault
	if (_gpsFault < fault_lvl_disable) {
		Matrix<float, n_x, n_y_gps> K = _P * C.transpose() * S_I;
		_x += K * r;
		_P -= K * C * _P;
	}
}
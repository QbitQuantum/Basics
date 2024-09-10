void BlockLocalPositionEstimator::correctGps()  	// TODO : use another other metric for glitch detection
{

	// gps measurement in local frame
	double  lat = _sub_gps.get().lat * 1.0e-7;
	double  lon = _sub_gps.get().lon * 1.0e-7;
	float  alt = _sub_gps.get().alt * 1.0e-3f;

	float px = 0;
	float py = 0;
	float pz = alt - _gpsAltHome;
	map_projection_project(&_map_ref, lat, lon, &px, &py);

	//printf("gps: lat %10g, lon, %10g alt %10g\n", lat, lon, double(alt));
	//printf("home: lat %10g, lon, %10g alt %10g\n", _sub_home.lat, _sub_home.lon, double(_sub_home.alt));
	//printf("local: x %10g y %10g z %10g\n", double(px), double(py), double(pz));

	Matrix<float, 6, 1> y;
	y.setZero();
	y(0) = px;
	y(1) = py;
	y(2) = pz;
	y(3) = _sub_gps.get().vel_n_m_s;
	y(4) = _sub_gps.get().vel_e_m_s;
	y(5) = _sub_gps.get().vel_d_m_s;

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

	// TODO is velocity covariance provided from gps sub
	R(0, 0) = var_xy;
	R(1, 1) = var_xy;
	R(2, 2) = var_z;
	R(3, 3) = var_vxy;
	R(4, 4) = var_vxy;
	R(5, 5) = var_vz;

	// residual
	Matrix<float, 6, 1> r = y - C * _x;
	Matrix<float, 6, 6> S_I = (C * _P * C.transpose() + R).inverse();

	// fault detection
	float beta = sqrtf((r.transpose() * (S_I * r))(0, 0));
	uint8_t nSat = _sub_gps.get().satellites_used;
	float eph = _sub_gps.get().eph;

	if (nSat < 6 || eph > _gps_eph_max.get()) {
		if (!_gpsFault) {
			mavlink_log_info(_mavlink_fd, "[lpe] gps fault nSat: %d eph: %5.2f", nSat, double(eph));
			warnx("[lpe] gps fault nSat: %d eph: %5.2f", nSat, double(eph));
			_gpsFault = FAULT_SEVERE;
		}

	} else if (beta > _beta_max.get()) {
		if (!_gpsFault) {
			mavlink_log_info(_mavlink_fd, "[lpe] gps fault, beta: %5.2f", double(beta));
			warnx("[lpe] gps fault, beta: %5.2f", double(beta));
			mavlink_log_info(_mavlink_fd, "[lpe] r: %5.2f %5.2f %5.2f %5.2f %5.2f %5.2f",
					 double(r(0)),  double(r(1)), double(r(2)),
					 double(r(3)), double(r(4)), double(r(5)));
			mavlink_log_info(_mavlink_fd, "[lpe] S_I: %5.2f %5.2f %5.2f %5.2f %5.2f %5.2f",
					 double(S_I(0, 0)),  double(S_I(1, 1)), double(S_I(2, 2)),
					 double(S_I(3, 3)),  double(S_I(4, 4)), double(S_I(5, 5)));
			mavlink_log_info(_mavlink_fd, "[lpe] r: %5.2f %5.2f %5.2f %5.2f %5.2f %5.2f",
					 double(r(0)),  double(r(1)), double(r(2)),
					 double(r(3)), double(r(4)), double(r(5)));
			_gpsFault = FAULT_MINOR;
		}

		// trust GPS less
		S_I = ((C * _P * C.transpose()) + R * 10).inverse();

	} else if (_gpsFault) {
		_gpsFault = FAULT_NONE;
		mavlink_log_info(_mavlink_fd, "[lpe] GPS OK");
		warnx("[lpe] GPS OK");
	}

	// kalman filter correction if no hard fault
	if (_gpsFault == FAULT_NONE) {
		Matrix<float, n_x, n_y_gps> K = _P * C.transpose() * S_I;
		_x += K * r;
		_P -= K * C * _P;
	}

	_time_last_gps = _timeStamp;
}
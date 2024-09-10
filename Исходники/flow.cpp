void BlockLocalPositionEstimator::flowCorrect()
{
	// measure flow
	Vector<float, n_y_flow> y;

	if (flowMeasure(y) != OK) { return; }

	// flow measurement matrix and noise matrix
	Matrix<float, n_y_flow, n_x> C;
	C.setZero();
	C(Y_flow_vx, X_vx) = 1;
	C(Y_flow_vy, X_vy) = 1;

	SquareMatrix<float, n_y_flow> R;
	R.setZero();

	// polynomial noise model, found using least squares fit
	// h, h**2, v, v*h, v*h**2
	const float p[5] = {0.04005232f, -0.00656446f, -0.26265873f,  0.13686658f, -0.00397357f};

	// prevent extrapolation past end of polynomial fit by bounding independent variables
	float h = agl();
	float v = y.norm();
	const float h_min = 2.0f;
	const float h_max = 8.0f;
	const float v_min = 0.5f;
	const float v_max = 1.0f;

	if (h > h_max) {
		h = h_max;
	}

	if (h < h_min) {
		h = h_min;
	}

	if (v > v_max) {
		v = v_max;
	}

	if (v < v_min) {
		v = v_min;
	}

	// compute polynomial value
	float flow_vxy_stddev = p[0] * h + p[1] * h * h + p[2] * v + p[3] * v * h + p[4] * v * h * h;

	float rotrate_sq = _sub_att.get().rollspeed * _sub_att.get().rollspeed
			   + _sub_att.get().pitchspeed * _sub_att.get().pitchspeed
			   + _sub_att.get().yawspeed * _sub_att.get().yawspeed;

	matrix::Eulerf euler(matrix::Quatf(_sub_att.get().q));
	float rot_sq = euler.phi() * euler.phi() + euler.theta() * euler.theta();

	R(Y_flow_vx, Y_flow_vx) = flow_vxy_stddev * flow_vxy_stddev +
				  _flow_r.get() * _flow_r.get() * rot_sq +
				  _flow_rr.get() * _flow_rr.get() * rotrate_sq;
	R(Y_flow_vy, Y_flow_vy) = R(Y_flow_vx, Y_flow_vx);

	// residual
	Vector<float, 2> r = y - C * _x;

	// residual covariance
	Matrix<float, n_y_flow, n_y_flow> S = C * _P * C.transpose() + R;

	// publish innovations
	_pub_innov.get().flow_innov[0] = r(0);
	_pub_innov.get().flow_innov[1] = r(1);
	_pub_innov.get().flow_innov_var[0] = S(0, 0);
	_pub_innov.get().flow_innov_var[1] = S(1, 1);

	// residual covariance, (inverse)
	Matrix<float, n_y_flow, n_y_flow> S_I = inv<float, n_y_flow>(S);

	// fault detection
	float beta = (r.transpose() * (S_I * r))(0, 0);

	if (beta > BETA_TABLE[n_y_flow]) {
		if (!(_sensorFault & SENSOR_FLOW)) {
			mavlink_and_console_log_info(&mavlink_log_pub, "[lpe] flow fault,  beta %5.2f", double(beta));
			_sensorFault |= SENSOR_FLOW;
		}

	} else if (_sensorFault & SENSOR_FLOW) {
		_sensorFault &= ~SENSOR_FLOW;
		mavlink_and_console_log_info(&mavlink_log_pub, "[lpe] flow OK");
	}

	if (!(_sensorFault & SENSOR_FLOW)) {
		Matrix<float, n_x, n_y_flow> K =
			_P * C.transpose() * S_I;
		Vector<float, n_x> dx = K * r;
		_x += dx;
		_P -= K * C * _P;
	}
}
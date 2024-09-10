void Standard::update_mc_state()
{
	VtolType::update_mc_state();

	// enable MC motors here in case we transitioned directly to MC mode
	if (_flag_enable_mc_motors) {
		set_max_mc(2000);
		set_idle_mc();
		_flag_enable_mc_motors = false;
	}

	// if the thrust scale param is zero then the pusher-for-pitch strategy is disabled and we can return
	if (_params_standard.forward_thrust_scale < FLT_EPSILON) {
		return;
	}

	matrix::Dcmf R(matrix::Quatf(_v_att->q));
	matrix::Dcmf R_sp(&_v_att_sp->R_body[0]);
	matrix::Eulerf euler(R);
	matrix::Eulerf euler_sp(R_sp);
	_pusher_throttle = 0.0f;

	// direction of desired body z axis represented in earth frame
	matrix::Vector3f body_z_sp(R_sp(0, 2), R_sp(1, 2), R_sp(2, 2));

	// rotate desired body z axis into new frame which is rotated in z by the current
	// heading of the vehicle. we refer to this as the heading frame.
	matrix::Dcmf R_yaw = matrix::Eulerf(0.0f, 0.0f, -euler(2));
	body_z_sp = R_yaw * body_z_sp;
	body_z_sp.normalize();

	// calculate the desired pitch seen in the heading frame
	// this value corresponds to the amount the vehicle would try to pitch forward
	float pitch_forward = asinf(body_z_sp(0));

	// only allow pitching forward up to threshold, the rest of the desired
	// forward acceleration will be compensated by the pusher
	if (pitch_forward < -_params_standard.down_pitch_max) {
		// desired roll angle in heading frame stays the same
		float roll_new = -atan2f(body_z_sp(1), body_z_sp(2));

		_pusher_throttle = (sinf(-pitch_forward) - sinf(_params_standard.down_pitch_max))
				   * _v_att_sp->thrust * _params_standard.forward_thrust_scale;

		// limit desired pitch
		float pitch_new = -_params_standard.down_pitch_max;

		// create corrected desired body z axis in heading frame
		matrix::Dcmf R_tmp = matrix::Eulerf(roll_new, pitch_new, 0.0f);
		matrix::Vector3f tilt_new(R_tmp(0, 2), R_tmp(1, 2), R_tmp(2, 2));

		// rotate the vector into a new frame which is rotated in z by the desired heading
		// with respect to the earh frame.
		float yaw_error = _wrap_pi(euler_sp(2) - euler(2));
		matrix::Dcmf R_yaw_correction = matrix::Eulerf(0.0f, 0.0f, -yaw_error);
		tilt_new = R_yaw_correction * tilt_new;

		// now extract roll and pitch setpoints
		float pitch = asinf(tilt_new(0));
		float roll = -atan2f(tilt_new(1), tilt_new(2));
		R_sp = matrix::Eulerf(roll, pitch, euler_sp(2));
		matrix::Quatf q_sp(R_sp);
		memcpy(&_v_att_sp->R_body[0], &R_sp._data[0], sizeof(_v_att_sp->R_body));
		memcpy(&_v_att_sp->q_d[0], &q_sp._data[0], sizeof(_v_att_sp->q_d));
	}

	_pusher_throttle = _pusher_throttle < 0.0f ? 0.0f : _pusher_throttle;

}
void MobileVRInterface::set_position_from_sensors() {
	_THREAD_SAFE_METHOD_

	// this is a helper function that attempts to adjust our transform using our 9dof sensors
	// 9dof is a misleading marketing term coming from 3 accelerometer axis + 3 gyro axis + 3 magnetometer axis = 9 axis
	// but in reality this only offers 3 dof (yaw, pitch, roll) orientation

	uint64_t ticks = OS::get_singleton()->get_ticks_usec();
	uint64_t ticks_elapsed = ticks - last_ticks;
	float delta_time = (double)ticks_elapsed / 1000000.0;

	// few things we need
	Input *input = Input::get_singleton();
	Vector3 down(0.0, -1.0, 0.0); // Down is Y negative
	Vector3 north(0.0, 0.0, 1.0); // North is Z positive

	// make copies of our inputs
	bool has_grav = false;
	Vector3 acc = input->get_accelerometer();
	Vector3 gyro = input->get_gyroscope();
	Vector3 grav = input->get_gravity();
	Vector3 magneto = scale_magneto(input->get_magnetometer()); // this may be overkill on iOS because we're already getting a calibrated magnetometer reading

	if (sensor_first) {
		sensor_first = false;
	} else {
		acc = scrub(acc, last_accerometer_data, 2, 0.2);
		magneto = scrub(magneto, last_magnetometer_data, 3, 0.3);
	};

	last_accerometer_data = acc;
	last_magnetometer_data = magneto;

	if (grav.length() < 0.1) {
		// not ideal but use our accelerometer, this will contain shakey shakey user behaviour
		// maybe look into some math but I'm guessing that if this isn't available, its because we lack the gyro sensor to actually work out
		// what a stable gravity vector is
		grav = acc;
		if (grav.length() > 0.1) {
			has_grav = true;
		};
	} else {
		has_grav = true;
	};

	bool has_magneto = magneto.length() > 0.1;
	if (gyro.length() > 0.1) {
		/* this can return to 0.0 if the user doesn't move the phone, so once on, it's on */
		has_gyro = true;
	};

	if (has_gyro) {
		// start with applying our gyro (do NOT smooth our gyro!)
		Basis rotate;
		rotate.rotate(orientation.get_axis(0), gyro.x * delta_time);
		rotate.rotate(orientation.get_axis(1), gyro.y * delta_time);
		rotate.rotate(orientation.get_axis(2), gyro.z * delta_time);
		orientation = rotate * orientation;

		tracking_state = ARVRInterface::ARVR_NORMAL_TRACKING;
	};

	///@TODO improve this, the magnetometer is very fidgity sometimes flipping the axis for no apparent reason (probably a bug on my part)
	// if you have a gyro + accelerometer that combo tends to be better then combining all three but without a gyro you need the magnetometer..
	if (has_magneto && has_grav && !has_gyro) {
		// convert to quaternions, easier to smooth those out
		Quat transform_quat(orientation);
		Quat acc_mag_quat(combine_acc_mag(grav, magneto));
		transform_quat = transform_quat.slerp(acc_mag_quat, 0.1);
		orientation = Basis(transform_quat);

		tracking_state = ARVRInterface::ARVR_NORMAL_TRACKING;
	} else if (has_grav) {
		// use gravity vector to make sure down is down...
		// transform gravity into our world space
		grav.normalize();
		Vector3 grav_adj = orientation.xform(grav);
		float dot = grav_adj.dot(down);
		if ((dot > -1.0) && (dot < 1.0)) {
			// axis around which we have this rotation
			Vector3 axis = grav_adj.cross(down);
			axis.normalize();

			Basis drift_compensation(axis, acos(dot) * delta_time * 10);
			orientation = drift_compensation * orientation;
		};
	};

	// JIC
	orientation.orthonormalize();

	last_ticks = ticks;
};
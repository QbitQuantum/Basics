void
basic_ins_qkf::predict_ned(const Vector3d& gyro_meas,
		const Vector3d& accel_meas,
		double dt)
{
#ifdef TIME_OPS
	timer clock;
	clock.start();
#endif
	Vector3d accel_body = avg_state.orientation.conjugate()*accel_meas;
	// Vector3d accel_dir = accel_body.normalized();
	Matrix<double, 3, 3> accel_cov = cross<double>(-accel_body);

	// 1500x realtime, without vectorization, on 2.2 GHz Athlon X2
	// See basic_ins_qkf::predict() for the full blockwise form
	const Matrix<double, 12, 12> pcov = cov;
	const Matrix3d dtR = dt * avg_state.orientation.conjugate().toRotationMatrix();
	const Matrix3d dtQ = accel_cov * dt;

	cov.block<3, 3>(0, 3) -= pcov.block<3,3>(0, 0)*dtR.transpose();
	cov.block<3, 3>(0, 6) += dt * pcov.block<3, 3>(0, 9);
	cov.block<3, 3>(0, 9) -= pcov.block<3, 3>(0, 3) * dtQ.transpose();
	cov.block<3, 3>(3, 3) += dtR*pcov.block<3, 3>(0, 0)*dtR.transpose()
			- dtR*pcov.block<3, 3>(0, 3) - pcov.block<3, 3>(3, 0)*dtR.transpose();
	cov.block<3, 3>(3, 6) += -dtR * (pcov.block<3, 3>(0, 6) + dt*pcov.block<3, 3>(0, 9))
			+ dt*pcov.block<3, 3>(3, 9);
	cov.block<3, 3>(3, 9) += -dtR*( -pcov.block<3, 3>(0, 3)*dtQ.transpose() + pcov.block<3, 3>(0, 9))
			- pcov.block<3, 3>(3, 3)*dtQ.transpose();
	cov.block<3, 3>(6, 6) += dt*pcov.block<3, 3>(6, 9) + dt*dt*pcov.block<3, 3>(9, 9)
			+ dt*pcov.block<3, 3>(9, 6);
	cov.block<3, 3>(6, 9) += -pcov.block<3, 3>(6, 3)*dtQ.transpose() + dt*pcov.block<3, 3>(9, 9)
			- dt*pcov.block<3, 3>(9, 3)*dtQ.transpose();
	cov.block<3, 3>(9, 9) += dtQ*pcov.block<3, 3>(3, 3)*dtQ.transpose()
			- dtQ*pcov.block<3, 3>(3, 9) - pcov.block<3, 3>(9, 3)*dtQ.transpose();

	// Update symmetric cross-covariance terms
	cov.block<3, 3>(3, 0) = cov.block<3, 3>(0, 3).transpose();
	cov.block<3, 3>(6, 0) = cov.block<3, 3>(0, 6).transpose();
	cov.block<3, 3>(6, 3) = cov.block<3, 3>(3, 6).transpose();
	cov.block<3, 3>(9, 0) = cov.block<3, 3>(0, 9).transpose();
	cov.block<3, 3>(9, 3) = cov.block<3, 3>(3, 9).transpose();
	cov.block<3, 3>(9, 6) = cov.block<3, 3>(6, 9).transpose();

	// Add state transition noise
	cov.block<3, 3>(0, 0) += gyro_stability_noise.asDiagonal() * dt;
	cov.block<3, 3>(3, 3) += gyro_white_noise.asDiagonal() * dt;
	cov.block<3, 3>(6, 6) += accel_white_noise.asDiagonal() * 0.5*dt*dt;
	cov.block<3, 3>(9, 9) += accel_white_noise.asDiagonal() * dt;

	Quaterniond orientation = exp<double>((gyro_meas - avg_state.gyro_bias) * dt)
			* avg_state.orientation;
	// The contribution of the acceleration due to gravity on the accelerometer.
	// Note that in NED, the z axis is down, and the accelerometer observes
	// an extra acceleration due to gravity in the "up" direction.
	Vector3d accel_gravity = -Vector3d::UnitZ() * 9.81;
	Vector3d accel = accel_body - accel_gravity;
	Vector3d position = avg_state.position + avg_state.velocity * dt + 0.5*accel*dt*dt;
	Vector3d velocity = avg_state.velocity + accel*dt;

	avg_state.position = position;
	avg_state.velocity = velocity;
	// Note: Renormalization occurs during all measurement updates.
	avg_state.orientation = orientation;

	assert(invariants_met());
#ifdef TIME_OPS
	double time = clock.stop()*1e6;
	std::cout << "unscented predict time: " << time << "\n";
#endif
}
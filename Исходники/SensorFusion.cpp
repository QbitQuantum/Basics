void SensorFusion::reset(const Eigen::Vector3f& accel, const Eigen::Vector3f& magnetom)
{
	G_Dt = 0;

	Eigen::Vector3f temp1;
	Eigen::Vector3f temp2;
	Eigen::Vector3f xAxis;
	xAxis << 1.0f, 0.0f, 0.0f;

	timestamp = highResClock.now();

	// GET PITCH
	// Using y-z-plane-component/x-component of gravity vector
	pitch = -atan2f(accel(0), sqrtf(accel(1) * accel(1) + accel(2) * accel(2)));

	// GET ROLL
	// Compensate pitch of gravity vector
	temp1 = accel.cross(xAxis);
	temp2 = xAxis.cross(temp1);

	// Normally using x-z-plane-component/y-component of compensated gravity vector
	// roll = atan2(temp2[1], sqrt(temp2[0] * temp2[0] + temp2[2] * temp2[2]));
	// Since we compensated for pitch, x-z-plane-component equals z-component:
	roll = atan2f(temp2(1), temp2(2));

	// GET YAW
	compassHeading(magnetom);
	yaw = magHeading;

	// Init rotation matrix
	init_rotation_matrix(dcmMatrix, yaw, pitch, roll);
}
// ****** find roll, pitch, yaw from quaternion ********
void CoordinateConversions::Quaternion2RPY(const float q[4], float rpy[3])
{
	float R13, R11, R12, R23, R33;
	float q0s = q[0] * q[0];
	float q1s = q[1] * q[1];
	float q2s = q[2] * q[2];
	float q3s = q[3] * q[3];

	R13 = 2 * (q[1] * q[3] - q[0] * q[2]);
	R11 = q0s + q1s - q2s - q3s;
	R12 = 2 * (q[1] * q[2] + q[0] * q[3]);
	R23 = 2 * (q[2] * q[3] + q[0] * q[1]);
	R33 = q0s - q1s - q2s + q3s;

	rpy[1] = RAD2DEG * asinf(-R13);	// pitch always between -pi/2 to pi/2
	rpy[2] = RAD2DEG * atan2f(R12, R11);
	rpy[0] = RAD2DEG * atan2f(R23, R33);

	//TODO: consider the cases where |R13| ~= 1, |pitch| ~= pi/2
}
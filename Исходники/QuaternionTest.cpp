TEST_F(QuaternionTest, Slerp) {
	setAxisAngle(20, 1, 0, 0);
	Quaternion start = quaternion;
	setAxisAngle(40, 1, 0, 0);
	float fraction = 0.5;
	quaternion = start.slerp(quaternion, fraction);

	assertClose(quaternion, 0.9659, 0.2588, 0, 0);
}
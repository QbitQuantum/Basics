CameraMatrix CameraMatrix::inverse() const {

	CameraMatrix cm = *this;
	cm.invert();
	return cm;
}
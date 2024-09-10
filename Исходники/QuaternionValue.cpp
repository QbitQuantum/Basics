void QuaternionValue::set(const Quaternion &quat) {
	set(quat.getW(), quat.getX(), quat.getY(), quat.getZ());
}
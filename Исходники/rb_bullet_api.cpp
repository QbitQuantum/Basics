static inline void copy_quat_btquat(float quat[4], const btQuaternion &btquat)
{
	quat[0] = btquat.getW();
	quat[1] = btquat.getX();
	quat[2] = btquat.getY();
	quat[3] = btquat.getZ();
}
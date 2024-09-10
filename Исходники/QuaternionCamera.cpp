void Quaternion::rotateAround(float angle, Vector axis)
{
	Quaternion temp(axis.x * sin(angle/2), axis.y * sin(angle/2), axis.z * sin(angle/2), cos(angle/2));
	Quaternion quat_view (_v, 0);

	Quaternion result = temp.conjugate() * quat_view * temp;
	result = result.normalize();

	_v.x = result.v().x;
	_v.y = result.v().y;
	_v.z = result.v().z;
}
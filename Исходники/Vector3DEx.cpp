float Vector3DEx::angle(Vector3DEx& other)
{
	float cosAngle = (*this*other)/(length()*other.length());
	float ang = acosf(cosAngle);
	return ang;
}
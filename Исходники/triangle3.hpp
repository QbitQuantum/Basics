bool triangle3<T>::is_front_facing(const vec3<T>& lookDirection) const
{
	const vec3<T> n = get_normal();
	n.normalize();
	const T d = dot(n, lookDirection);
	return F32_LOWER_EQUAL_0(d);
}
bool BaseTransform::intersect(const Ray & ray) const
{	
	Matrix44F s = worldSpace();
	s.inverse();
	Vector3F a = ray.m_origin + ray.m_dir * ray.m_tmin;
	a = s.transform(a);
	Vector3F b = ray.m_origin + ray.m_dir * ray.m_tmax;
	b = s.transform(b);
	Ray objR(a, b);
	
	float hit0, hit1;
	return getBBox().intersect(objR, &hit0, &hit1);
}
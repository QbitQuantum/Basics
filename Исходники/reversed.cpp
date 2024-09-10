void Sphere::checkAndChange(Sphere& s)
{
	if (this == &s)
		return;

	Vector3f dist = s.pos - pos;
	if (dist.dot(dist) > (r + s.r)*(r + s.r))
		return;
	if (s.velo.dot(dist) > velo.dot(dist))
		return;

	dist = dist.normalize();
	Vector3f vn1 = velo.dot(dist) * dist;
	Vector3f vn2 = s.velo.dot(dist) * dist;
	Vector3f vt1 = velo - vn1;
	Vector3f vt2 = s.velo - vn2;
	float ee = e * s.e;

	Vector3f vvn1 = (ee*mass - s.mass)*vn1 + (ee + 1)*s.mass*vn2;
	vvn1 /= ee*(mass + s.mass);
	Vector3f vvn2 = (ee + 1)*mass*vn1 + (ee*s.mass - mass)*vn2;
	vvn2 /= ee*(mass + s.mass);

	velo = vvn1 + vt1;
	s.velo = vvn2 + vt2;
}
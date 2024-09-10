//-----------------------------------------------------------
float LOCAL_DistToPlane(Vector3f * p, Vector3f * p0, Vector3f * p1, Vector3f * p2)
{
	Vector3f q0 = *p1 - *p0;
	Vector3f q1 = *p2 - *p0;
	Vector3f c = (q0.Cross(q1)).Normalized();
	Vector3f q = *p - *p0;
	return(c.Dot(q));
}
bool SegInterSeg(const Point2D& p0, const Point2D& p1, const Point2D& q0, const Point2D& q1,Point2D& result)
{
	Vector2D direction1 = p1 - p0;
	Vector2D direction2 = q1 - q0;

	Real dir1Square = direction1.magnitudeSquared();
	Real dir2Square = direction2.magnitudeSquared();

	Real kcross = direction1.cross(direction2);
	Vector2D e = q0 - p0;

	if( (kcross*kcross) > EPS*EPS*dir1Square*dir2Square  )
	{//The intersection angle is not 0 based on relative error.||Cross(d1,d2)||^2/ (||d1||^2*||d2||^2)<=sin(a).
		Real s = e.cross(direction2) / kcross;
		if( LESS(s,0) || GREATER(s,1) )
			return false;
		Real t = e.cross(direction1) / kcross;
		if( LESS(t,0) || GREATER(t,1) )
			return false;
		result = p0 + s*direction1;
		return true;
	}
	return false;
}
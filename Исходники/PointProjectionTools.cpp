//! Returns true if the AB and CD segments intersect each other
bool Intersect(const CCVector2& A, const CCVector2& B, const CCVector2& C, const CCVector2& D)
{
	if (cross(A,B,C) * cross(A,B,D) >= 0) //both points are on the same side? No intersection
		return false;

	CCVector2 AB = B-A;
	CCVector2 AC = C-A;
	CCVector2 CD = D-C;

	PointCoordinateType q = CD.y * AB.x - CD.x * AB.y;
	if (fabs(q) > ZERO_TOLERANCE) //AB and CD are not parallel
	{
		//where do they interest?
		PointCoordinateType p = AC.x * AB.y - AC.y * AB.x;
		PointCoordinateType v = p/q;
		if (v <= 0 || v >= 1) //not CD!
			return false;

		//test further with AB
		p = CD.y * AC.x - CD.x * AC.y;
		v= p/q;
		return (v > 0 && v < 1); //not AB?
	}
	else //AB and CD are parallel
	{
		PointCoordinateType dAB = AB.norm();
		PointCoordinateType dAC = AC.norm();
		PointCoordinateType dot = AB.dot(AC) / (dAB * dAC);
		if (fabs(dot) < 0.999)
		{
			//not colinear
			return false;
		}
		else
		{
			//colinear --> do they actually intersect?
			return (dAC < dAB || (D-A).norm() < dAB);
		}
	}
}
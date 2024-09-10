pscalar LineSegment2D::distanceSquared (Point2 &P)
{
	Vector2 M = B.coord - A.coord;
	pscalar t = M.dot(P-A.coord) / (M.squaredNorm());

	if (t<=0)
		return (P-A.coord).squaredNorm();
	else if (t>0 and t<1)
		return (P - (A.coord+M*t)).squaredNorm();
	else
		return (P - B.coord).squaredNorm();
}
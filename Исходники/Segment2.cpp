bool Segment2::intersect(const Segment2 &seg, double &t, Point2 &intersection) const
{
	//need the normal of the other line, represent line as a normal
	//and distance from origin instead of two points
	Vector2 normal = seg.getNormal();


	//raytrace
	double nDotDirection = normal.dot( getDirection() );

	if ( nDotDirection == 0.0 )
	{
		return false;
	}

	//distance from line to origin
	double d = seg.a.dot( normal );

	t = ( d - a.dot( normal ) )  /  nDotDirection;
	intersection = a  +  ( getDirection() * t );

	//t must be between 0 and 1 (intersection between a and b)
	//check that the intersection is within the bounds of line
	return ( t >= 0.0 )  &&  ( t <= 1.0 )  &&
			 seg.boundsContain( intersection );
}
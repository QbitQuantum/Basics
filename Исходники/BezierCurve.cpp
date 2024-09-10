// Returns true if this BezierCurve is C1 continuous with the beginning
// of another BezierCurve (checks continuity at the end of this curve)
bool BezierCurve::c1Continuous(BezierCurve& next) {

	Vector4 myEnd = p3;
	Vector4 otherEnd = next.p0;
	Vector3 mySlope = (p3 - p2).getVector3();
	Vector3 otherSlope = (next.p0 - next.p1).getVector3();

	// Normalize them so we're less likely to run into floating point issues
	mySlope.normalize();
	otherSlope.normalize();

	// The points p2, p3, other.p0, other.p1 must lie in the same line
	// Thus, they can all be represented as parallel vectors. The dot
	// product of two parallel vectors is 1.
	
	if ( myEnd.getX() == otherEnd.getX() && 
		 myEnd.getY() == otherEnd.getY() && 
		 myEnd.getZ() == otherEnd.getZ() && 
		 myEnd.getW() == otherEnd.getW() ) {
		return ( mySlope.dot(mySlope, otherSlope) == 1.0 );
	}
	else {
		// They aren't even C0 continuous :(
		return false;
	}

};
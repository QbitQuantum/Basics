bool HLine::FindNearPoint(const double* ray_start, const double* ray_direction, double *point){
	// The OpenCascade libraries throw an exception when one tries to
	// create a gp_Lin() object using a vector that doesn't point
	// anywhere.  If this is a zero-length line then we're in
	// trouble.  Don't bother with it.
	if ((A->m_p.X() == B->m_p.X()) &&
	    (A->m_p.Y() == B->m_p.Y()) &&
	    (A->m_p.Z() == B->m_p.Z())) return(false);

	gp_Lin ray(make_point(ray_start), make_vector(ray_direction));
	gp_Pnt p1, p2;
	ClosestPointsOnLines(GetLine(), ray, p1, p2);

	if(!Intersects(p1))
		return false;

	extract(p1, point);
	return true;
}
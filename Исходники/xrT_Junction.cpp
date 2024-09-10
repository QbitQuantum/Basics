IC float	SqrDistance2Segment(const Fvector& P, const Fvector& A, const Fvector& B)
{
	// Determine t (the length of the vector from ‘a’ to ‘p’)
	Fvector c; c.sub(P,A);
	Fvector V; V.sub(B,A); 
	
	float d = V.magnitude	();
	
	V.div	(d); 
	float t = V.dotproduct	(c);
	
	// Check to see if ‘t’ is beyond the extents of the line segment
	if (t <= 0.0f)	return P.distance_to_sqr(A);
	if (t >= d)		return P.distance_to_sqr(B);
	
	// Return the point between ‘a’ and ‘b’
	// set length of V to t. V is normalized so this is easy
	Fvector	R;	R.mad		(A,V,t);
	return P.distance_to_sqr(R);
}
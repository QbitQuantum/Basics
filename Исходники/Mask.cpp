double Mask::Intersection(Point sA, Point vA) const
{
	// Keep track of the closest intersection point found.
	double closest = 1.;
	
	Point prev = outline.back();
	for(const Point &next : outline)
	{
		// Check if there is an intersection. (If not, the cross would be 0.) If
		// there is, handle it only if it is a point where the segment is
		// entering the polygon rather than exiting it (i.e. cross > 0).
		Point vB = next - prev;
		double cross = vB.Cross(vA);
		if(cross > 0.)
		{
			Point vS = prev - sA;
			double uB = vA.Cross(vS);
			double uA = vB.Cross(vS);
			// If the intersection occurs somewhere within this segment of the
			// outline, find out how far along the query vector it occurs and
			// remember it if it is the closest so far.
			if((uB >= 0.) & (uB < cross) & (uA >= 0.))
				closest = min(closest, uA / cross);
		}
		
		prev = next;
	}
	return closest;
}
//static 
// returns 'true' if planes intersect, and stores the result 
// the second and third arguments are treated as planes
// where mPoint is on the plane and mDirection is the normal
// result.mPoint will be the intersection line's closest approach 
// to first_plane.mPoint
bool LLLine::getIntersectionBetweenTwoPlanes( LLLine& result, const LLLine& first_plane, const LLLine& second_plane )
{
	// TODO -- if we ever get some generic matrix solving code in our libs
	// then we should just use that, since this problem is really just
	// linear algebra.

	F32 dot = fabs(first_plane.mDirection * second_plane.mDirection);
	if (dot > ALMOST_PARALLEL)
	{
		// the planes are nearly parallel
		return false;
	}

	LLVector3 direction = first_plane.mDirection % second_plane.mDirection;
	direction.normalize();

	LLVector3 first_intersection;
	{
		LLLine intersection_line(first_plane);
		intersection_line.mDirection = direction % first_plane.mDirection;
		intersection_line.mDirection.normalize();
		intersection_line.intersectsPlane(first_intersection, second_plane);
	}

	/*
	LLVector3 second_intersection;
	{
		LLLine intersection_line(second_plane);
		intersection_line.mDirection = direction % second_plane.mDirection;
		intersection_line.mDirection.normalize();
		intersection_line.intersectsPlane(second_intersection, first_plane);
	}
	*/

	result.mPoint = first_intersection;
	result.mDirection = direction;

	return true;
}
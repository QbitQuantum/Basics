//////////////////////////////////////////////////////////////////////////////
//
// Sphere line intersection - this sets the parameter intersection,
// and returns TRUE if the line and sphere really do intersect.
//
// line-sphere intersection algorithm lifted from Eric Haines chapter in 
// Glassner's "Introduction to Ray Tracing", pp. 35-7
//
SbBool
SbSphere::intersect(const SbLine &l, SbVec3f &enter, SbVec3f &exit) const
//
//////////////////////////////////////////////////////////////////////////////
{
    float   B,C;	// At^2 + Bt + C = 0, but A is 1 since we normalize Rd
    float   discr;	// discriminant (B^2 - 4AC)
    SbVec3f v;
    float   sqroot;
    SbBool  doesIntersect = TRUE;

    // setup B,C
    v = l.getPosition() - center;
    B = 2.0 * (l.getDirection().dot(v));
    C = v.dot(v) - (radius * radius);

    // compute discriminant
    // if negative, there is no intersection
    discr = B*B - 4.0*C;

    if (discr < 0.0) {
	// line and sphere do not intersect
	doesIntersect = FALSE;
    }
    else {
	sqroot = sqrtf(discr);
	    
	float t0 = (-B - sqroot) * 0.5;
	enter = l.getPosition() + (l.getDirection() * t0);
	
	float t1 = (-B + sqroot) * 0.5;
	exit = l.getPosition() + (l.getDirection() * t1);
    }

    return doesIntersect;
}
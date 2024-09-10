SbRotation
SbSphereSectionProjector::getRotation(const SbVec3f &p1, const SbVec3f &p2)
//
////////////////////////////////////////////////////////////////////////
{
    SbBool tol1 = isWithinTolerance(p1);
    SbBool tol2 = isWithinTolerance(p2);

    if (tol1 && tol2) {
	// both points in tolerance, rotate about
	// sphere center

	return SbRotation(
	    p1 - sphere.getCenter(),
	    p2 - sphere.getCenter());
    }
    else if (!tol1 && !tol2) {
	// both points out of tolerance, rotate about
	// plane point

	// Would like to just use this:
	SbRotation badRot = SbRotation(p1 - planePoint, p2 - planePoint);
	// but fp instablity gives back a goofy axis, so we don't get
	// pure roll.

	// So we need to snap the axis to be parallel to plane dir
	SbVec3f badAxis; float goodAngle;
	badRot.getValue(badAxis, goodAngle);

	SbVec3f goodAxis;
	if (badAxis.dot(planeDir) > 0.0)
	    goodAxis = planeDir;
	else 	    
	    goodAxis = -planeDir;

	SbRotation rollRot(goodAxis, goodAngle);

	//Now find rotation in the direction perpendicular to this:
	SbVec3f diff1 = p1 - planePoint;
	SbVec3f diff2 = p2 - planePoint;
	float d = diff2.length() - diff1.length();

	// Check for degenerate cases
	float theta = d / sphere.getRadius();
	if ( fabs(theta) < 0.000001 || fabs(theta) > 1.0 )
	    return rollRot;

	diff1.normalize();
	SbVec3f pullAxis = planeDir.cross( diff1 );
	pullAxis.normalize();
	SbRotation pullRot(pullAxis, getRadialFactor() * theta );

	SbRotation totalRot = rollRot * pullRot;
	return totalRot;

    }
    else {
	// one point in, one point out, so rotate about
	// the center of the sphere from the point on the
	// sphere to the intersection of the plane and the
	// sphere closest to the point off the sphere

	SbLine planeLine;
	SbVec3f intersection;

	if (tol1) {
	    planeLine.setValue(planePoint, p2);
	}
	else {
	    planeLine.setValue(planePoint, p1);
	}

	if (! sphere.intersect(planeLine, intersection))
#ifdef DEBUG
	    SoDebugError::post("SbSphereSectionProjector::getRotation",
			       "Couldn't intersect plane line with sphere");
#else
	/* Do nothing */;
#endif

	if (tol1) {
	    // went off sphere
	    return SbRotation(
		p1 - sphere.getCenter(),
		intersection - sphere.getCenter());
	}
	else {
	    // came on to sphere
	    // "Hey cutie. You've got quite a radius..."
	    return SbRotation(
		intersection - sphere.getCenter(),
		p2 - sphere.getCenter());
	}
    }

}
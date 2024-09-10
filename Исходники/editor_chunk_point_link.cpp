/**
 *	This method overrides the base class' implementation to return the
 *	appropriate end points for this kind of link, using the start item
 *	and the end point.
 *
 *	@param s				Return parameter for the start point position.
 *	@param index			Return parameter for the end point position.
 *	@param absoluteCoords	True to use absolute coordinates instead of local.
 *	@return					True if successful, false otherwise.
 */
/*virtual*/ bool EditorChunkPointLink::getEndPoints(
	Vector3 &s, Vector3 &e, bool absoluteCoords ) const
{
    EditorChunkItem *start  = (EditorChunkItem *)startItem().getObject();

    // Maybe it's still loading...
    if ( start == NULL || start->chunk() == NULL)
    {
        return false;
    }

    Vector3 lStartPt = start->edTransform().applyToOrigin();
    s = start->chunk()->transform().applyPoint( lStartPt );
	e = endPoint_;

	// Get the start height, and check if it's in the ground
	bool foundHeight;
	float sh  = heightAtPos(s.x, s.y + NEXT_HEIGHT_SAMPLE, s.z, &foundHeight);
	float sd = s.y - sh;
	if (!foundHeight)
		sd = 0.0f;

	bool inAir = fabs(sd) > AIR_THRESHOLD;
	if ( !inAir )
	{
		// It's in the ground, get height at the middle and interpolate it to
		// the end using the start height.
		Vector3 mid = (e - s) / 2.0f + s;
		float mh = heightAtPos(mid.x, mid.y + NEXT_HEIGHT_SAMPLE, mid.z);
		float h = (mh-sh) * 2.0f + sh;
		if ( h > e.y )
		{
			// It's not in the air, and the terrain occluding the link, so
			// make the end point as high as the terrain at that position.
			float oldLength = ( e - s ).length();
			e.y = h;
			// Preserve the length
			Vector3 dir = ( e - s );
			dir.normalise();
			e = dir * oldLength + s;
		}
	}

    if (!absoluteCoords)
    {
        Matrix m = outsideChunk()->transform();
        m.invert();
        s = m.applyPoint(s);
        e = m.applyPoint(e);
    }

    return true;
}
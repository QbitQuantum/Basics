/* NOTE: this is called findSegmentIndexToSnap in JTS */
CoordinateList::iterator
LineStringSnapper::findSegmentToSnap(
			const Coordinate& snapPt,
			CoordinateList::iterator from,
			CoordinateList::iterator too_far)
{
	LineSegment seg;
	double minDist = snapTolerance; // make sure the first closer then
	                                // snapTolerance is accepted
	CoordinateList::iterator match=too_far;

	// TODO: use std::find_if
	for ( ; from != too_far; ++from)
	{
		seg.p0 = *from; 
		CoordinateList::iterator to = from;
		++to;
		seg.p1 = *to;

#if GEOS_DEBUG
cerr << " Checking segment " << seg << endl;
#endif

		/**
		 * Check if the snap pt is equal to one of
		 * the segment endpoints.
		 *
		 * If the snap pt is already in the src list,
		 * don't snap at all (unless allowSnappingToSourceVertices
		 * is set to true)
		 */
		if ( seg.p0.equals2D(snapPt) || seg.p1.equals2D(snapPt) )
		{

			if (allowSnappingToSourceVertices) {
#if GEOS_DEBUG
cerr << "   snap point matches a segment endpoint, checking next segment"
     << endl;
#endif
				continue;
			} else {
#if GEOS_DEBUG
cerr << "   snap point matches a segment endpoint, giving up seek" << endl;
#endif
				return too_far;
			}
		}

		double dist = seg.distance(snapPt);
		if ( dist >= minDist) {
#if GEOS_DEBUG
cerr << "   snap point distance " << dist
     << " not smaller than tolerance "
     << snapTolerance << " or previous closest "
     << minDist << endl;
#endif
      continue;
    }

#if GEOS_DEBUG
    cerr << "   snap point distance " << dist << " within tolerance "
         << snapTolerance << " and closer than previous candidate "
         << minDist << endl;
#endif

    if ( dist == 0.0 ) return from; // can't find any closer

    match = from;
    minDist = dist;

	}

	return match;
}
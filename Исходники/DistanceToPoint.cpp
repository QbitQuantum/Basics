/* public static */
void
DistanceToPoint::computeDistance(const geom::Polygon& poly,
                                          const geom::Coordinate& pt,
                                          PointPairDistance& ptDist)
{
	computeDistance(*(poly.getExteriorRing()), pt, ptDist);
	for (size_t i=0, n=poly.getNumInteriorRing(); i<n; ++i)
	{
		computeDistance(*(poly.getInteriorRingN(i)), pt, ptDist);
	}
}
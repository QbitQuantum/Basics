/*private*/
void
InteriorPointLine::add(const Coordinate& point)
{

	double dist=point.distance(centroid);
#if GEOS_DEBUG
	std::cerr << "point " << point << " dist " << dist << ", minDistance " << minDistance << std::endl;
#endif
	if (!hasInterior || dist<minDistance) {
		interiorPoint=point;
#if GEOS_DEBUG
		std::cerr << " is new InteriorPoint" << std::endl;
#endif
		minDistance=dist;
		hasInterior=true;
	}
}
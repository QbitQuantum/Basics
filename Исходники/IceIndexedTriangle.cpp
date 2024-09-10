float IndexedTriangle::ComputeOcclusionPotential(const Point* verts, const Point& view)	const
{
	if(!verts)	return 0.0f;
	// Occlusion potential: -(A * (N|V) / d^2)
	// A = polygon area
	// N = polygon normal
	// V = view vector
	// d = distance viewpoint-center of polygon

	float A = Area(verts);
	Point N;	Normal(verts, N);
	Point C;	Center(verts, C);
	float d = view.Distance(C);
	return -(A*(N|view))/(d*d);
}
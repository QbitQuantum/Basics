bool Polyhedron::FaceContains(int faceIndex, const float3 &worldSpacePoint, float polygonThickness) const
{
	// N.B. This implementation is a duplicate of Polygon::Contains, but adapted to avoid dynamic memory allocation
	// related to converting the face of a Polyhedron to a Polygon object.

	// Implementation based on the description from http://erich.realtimerendering.com/ptinpoly/

	const Face &face = f[faceIndex];
	const std::vector<int> &vertices = face.v;

	if (vertices.size() < 3)
		return false;

	Plane p = FacePlane(faceIndex);
	if (FacePlane(faceIndex).Distance(worldSpacePoint) > polygonThickness)
		return false;

	int numIntersections = 0;

	float3 basisU = v[vertices[1]] - v[vertices[0]];
	basisU.Normalize();
	float3 basisV = Cross(p.normal, basisU).Normalized();
	mathassert(basisU.IsNormalized());
	mathassert(basisV.IsNormalized());
	mathassert(basisU.IsPerpendicular(basisV));
	mathassert(basisU.IsPerpendicular(p.normal));
	mathassert(basisV.IsPerpendicular(p.normal));

	float2 localSpacePoint = float2(Dot(worldSpacePoint, basisU), Dot(worldSpacePoint, basisV));

	const float epsilon = 1e-4f;

	float2 p0 = float2(Dot(v[vertices.back()], basisU), Dot(v[vertices.back()], basisV)) - localSpacePoint;
	if (Abs(p0.y) < epsilon)
		p0.y = -epsilon; // Robustness check - if the ray (0,0) -> (+inf, 0) would pass through a vertex, move the vertex slightly.
	for(size_t i = 0; i < vertices.size(); ++i)
	{
		float2 p1 = float2(Dot(v[vertices[i]], basisU), Dot(v[vertices[i]], basisV)) - localSpacePoint;
		if (Abs(p1.y) < epsilon)
			p0.y = -epsilon; // Robustness check - if the ray (0,0) -> (+inf, 0) would pass through a vertex, move the vertex slightly.

		if (p0.y * p1.y < 0.f)
		{
			if (p0.x > 1e-3f && p1.x > 1e-3f)
				++numIntersections;
			else
			{
				// P = p0 + t*(p1-p0) == (x,0)
				//     p0.x + t*(p1.x-p0.x) == x
				//     p0.y + t*(p1.y-p0.y) == 0
				//                 t == -p0.y / (p1.y - p0.y)

				// Test whether the lines (0,0) -> (+inf,0) and p0 -> p1 intersect at a positive X-coordinate.
				float2 d = p1 - p0;
				if (Abs(d.y) > 1e-5f)
				{
					float t = -p0.y / d.y;
					float x = p0.x + t * d.x;
					if (t >= 0.f && t <= 1.f && x > 1e-6f)
						++numIntersections;
				}
			}
		}
		p0 = p1;
	}

	return numIntersections % 2 == 1;
}
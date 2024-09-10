Vertex Region::findClosestRegionPoint(const Vertex &point) const {
	// Determine whether the point is inside a hole. If that is the case, the closest
	// point on the edge of the hole is determined
	int polygonIdx = 0;
	{
		for (uint i = 1; i < _polygons.size(); ++i) {
			if (_polygons[i].isPointInPolygon(point)) {
				polygonIdx = i;
				break;
			}
		}
	}

	const Polygon &polygon = _polygons[polygonIdx];

	assert(polygon.vertexCount > 1);

	// For each line of the polygon, calculate the point that is cloest to the given point
	// The point of this set with the smallest distance to the given point is the result.
	Vertex closestVertex = findClosestPointOnLine(polygon.vertices[0], polygon.vertices[1], point);
	int closestVertexDistance2 = closestVertex.distance(point);
	for (int i = 1; i < polygon.vertexCount; ++i) {
		int j = (i + 1) % polygon.vertexCount;

		Vertex curVertex = findClosestPointOnLine(polygon.vertices[i], polygon.vertices[j], point);
		if (curVertex.distance(point) < closestVertexDistance2) {
			closestVertex = curVertex;
			closestVertexDistance2 = curVertex.distance(point);
		}
	}

	// Determine whether the point is really within the region. This must not be so, as a result of rounding
	// errors can occur at the edge of polygons
	if (isPointInRegion(closestVertex))
		return closestVertex;
	else {
		// Try to construct a point within the region - 8 points are tested in the immediate vacinity
		// of the point
		if (isPointInRegion(closestVertex + Vertex(-2, -2)))
			return closestVertex + Vertex(-2, -2);
		else if (isPointInRegion(closestVertex + Vertex(0, -2)))
			return closestVertex + Vertex(0, -2);
		else if (isPointInRegion(closestVertex + Vertex(2, -2)))
			return closestVertex + Vertex(2, -2);
		else if (isPointInRegion(closestVertex + Vertex(-2, 0)))
			return closestVertex + Vertex(-2, 0);
		else if (isPointInRegion(closestVertex + Vertex(0, 2)))
			return closestVertex + Vertex(0, 2);
		else if (isPointInRegion(closestVertex + Vertex(-2, 2)))
			return closestVertex + Vertex(-2, 2);
		else if (isPointInRegion(closestVertex + Vertex(-2, 0)))
			return closestVertex + Vertex(2, 2);
		else if (isPointInRegion(closestVertex + Vertex(2, 2)))
			return closestVertex + Vertex(2, 2);

		// If no point could be found that way that lies within the region, find the next point
		closestVertex = polygon.vertices[0];
		int shortestVertexDistance2 = polygon.vertices[0].sqrDist(point);
		{
			for (int i = 1; i < polygon.vertexCount; i++) {
				int curDistance2 = polygon.vertices[i].sqrDist(point);
				if (curDistance2 < shortestVertexDistance2) {
					closestVertex = polygon.vertices[i];
					shortestVertexDistance2 = curDistance2;
				}
			}
		}

		warning("Clostest vertex forced because edgepoint was outside region.");
		return closestVertex;
	}
}
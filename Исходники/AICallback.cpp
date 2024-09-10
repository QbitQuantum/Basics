float CAICallback::GetPathLength(float3 start, float3 end, int pathType, float goalRadius)
{
	const int pathID  = InitPath(start, end, pathType, goalRadius);
	float     pathLen = -1.0f;

	if (pathID == 0) {
		return pathLen;
	}

	std::vector<float3> points;
	std::vector<int>    lengths;

	pathManager->GetPathWayPoints(pathID, points, lengths);

	if (points.empty()) {
		return 0.0f;
	}

	// distance to first intermediate node
	pathLen = start.distance(points[0]);

	// we don't care which path segment has
	// what resolution, just lump all points
	// together
	for (size_t i = 1; i < points.size(); i++) {
		pathLen += points[i].distance(points[i - 1]);
	}

	/*
	// this method does not work without a path-owner
	// TODO: add an alternate GPL() callback for this?
	bool      haveNextWP = true;
	float3    currWP     = start;
	float3    nextWP     = start;

	while (haveNextWP) {
		nextWP = GetNextWaypoint(pathID);

		if (nextWP.y == -2) {
			// next path node not yet known
			continue;
		}

		if (nextWP.y == -1) {
			if (nextWP.x >= 0.0f && nextWP.z >= 0.0f) {
				// end of path (nextWP == end)
				pathLen += (nextWP - currWP).Length2D();
			} else {
				// invalid path
				pathLen = -1.0f;
			}

			haveNextWP = false;
		} else {
			pathLen += (nextWP - currWP).Length2D();
			currWP   = nextWP;
		}
	}
	*/

	FreePath(pathID);
	return pathLen;
}
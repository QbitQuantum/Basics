bool Obstacles::mergePolygons(Polygon &polyA, Polygon &polyB) {
	bool flagDidMergePolygons = false;
	Polygon polyMerged;
	polyMerged.rect = merge(polyA.rect, polyB.rect);

	Polygon *polyPrimary, *polySecondary;
	if (polyA.rect.y0 < polyB.rect.y0 || (polyA.rect.y0 == polyB.rect.y0 && polyA.rect.x0 < polyB.rect.x0)) {
		polyPrimary = &polyA;
		polySecondary = &polyB;
	} else {
		polyPrimary = &polyB;
		polySecondary = &polyA;
	}

	Vector2 intersectionPoint;
	LineSegment polyLine;
	bool flagAddVertexToVertexList = true;
	bool flagDidFindIntersection = false;
	int vertIndex = 0;

	Polygon *startingPolygon = polyPrimary;
	int flagDone = false;
	while (!flagDone) {
		VertexType polyPrimaryType;

		polyLine.start  = flagDidFindIntersection ? intersectionPoint : polyPrimary->vertices[vertIndex];
		polyLine.end    = polyPrimary->vertices[(vertIndex + 1) % polyPrimary->verticeCount];

		// TODO(madmoose): How does this work when adding a new intersection point?
		polyPrimaryType = polyPrimary->vertexType[vertIndex];

		if (flagAddVertexToVertexList) {
			assert(polyMerged.verticeCount < kPolygonVertexCount);
			polyMerged.vertices[polyMerged.verticeCount] = polyLine.start;
			polyMerged.vertexType[polyMerged.verticeCount] = polyPrimaryType;
			polyMerged.verticeCount++;
		}

		flagAddVertexToVertexList = true;
		int polySecondaryIntersectionIndex = -1;

		if (linePolygonIntersection(polyLine, polyPrimaryType, polySecondary, &intersectionPoint, &polySecondaryIntersectionIndex)) {
			if (WITHIN_TOLERANCE(intersectionPoint.x, polyLine.start.x) && WITHIN_TOLERANCE(intersectionPoint.y, polyLine.start.y)) {
				warning("Set: %d Scene: %d", _vm->_scene->getSetId(), _vm->_scene->getSceneId());
				assert(0 && "Report instances of this to madmoose!");
				flagAddVertexToVertexList = false;
				polyMerged.verticeCount--; // TODO(madmoose): How would this work?
			} else {
				// Obstacles::nop
			}
			vertIndex = polySecondaryIntersectionIndex;
			flagDidFindIntersection = true;

			SWAP(polyPrimary, polySecondary);

			flagDidMergePolygons = true;
		} else {
			vertIndex = (vertIndex + 1) % polyPrimary->verticeCount;
			flagDidFindIntersection = false;
		}
		if (polyPrimary->vertices[vertIndex] == startingPolygon->vertices[0]) {
			flagDone = true;
		}
	}

	if (flagDidMergePolygons) {
		*startingPolygon = polyMerged;
		startingPolygon->isPresent = true;
		if (startingPolygon == &polyA) {
			polyB.isPresent = false;
		} else {
			polyA.isPresent = false;
		}
	}

	return flagDidMergePolygons;
}
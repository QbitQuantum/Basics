/*
============
idAASLocal::FloorEdgeSplitPoint

  calculates either the closest or furthest point on the floor of the area which also lies on the pathPlane
  the point has to be on the front side of the frontPlane to be valid
============
*/
bool idAASLocal::FloorEdgeSplitPoint( idVec3 &bestSplit, int areaNum, const idPlane &pathPlane, const idPlane &frontPlane, bool closest ) const {
	int i, j, faceNum, edgeNum;
	const aasArea_t *area;
	const aasFace_t *face;
	idVec3 split;
	float dist, bestDist;
	const aasEdge_t *edge;
	idVec3 v1, v2;
	float d1, d2;

	area = &file->GetArea( areaNum );
	if ( closest ) {
		bestDist = maxWalkPathDistance;

		for ( i = area->numFaces-1; i >= 0; i-- ) {
			faceNum = file->GetFaceIndex( area->firstFace + i );
			face = &file->GetFace( abs(faceNum) );

			if ( !(face->flags & FACE_FLOOR ) ) {
				continue;
			}

			for ( j = face->numEdges-1; j >= 0; j-- ) {
				edgeNum = file->GetEdgeIndex( face->firstEdge + j );

				edge = &file->GetEdge( abs( edgeNum ) );
				v1 = file->GetVertex( edge->vertexNum[0] );
				v2 = file->GetVertex( edge->vertexNum[1] );
				d1 = v1 * pathPlane.Normal() - pathPlane.Dist();
				d2 = v2 * pathPlane.Normal() - pathPlane.Dist();

				//if ( (d1 < CM_CLIP_EPSILON && d2 < CM_CLIP_EPSILON) || (d1 > -CM_CLIP_EPSILON && d2 > -CM_CLIP_EPSILON) ) {
				if ( FLOATSIGNBITSET( d1 ) == FLOATSIGNBITSET( d2 ) ) {
					continue;
				}

				split = v1 + (d1 / (d1 - d2)) * (v2 - v1);
				dist = frontPlane.Distance( split );
				if ( dist >= -0.1f && dist < bestDist ) {
					bestDist = dist;
					bestSplit = split;
				}
			}
		}

		return ( bestDist < maxWalkPathDistance );

	} else {
		bestDist = -0.1f;

		for ( i = area->numFaces-1; i >= 0; i-- ) {
			faceNum = file->GetFaceIndex( area->firstFace + i );
			face = &file->GetFace( abs(faceNum) );

			if ( !(face->flags & FACE_FLOOR ) ) {
				continue;
			}

			for ( j = face->numEdges-1; j >= 0; j-- ) {
				edgeNum = file->GetEdgeIndex( face->firstEdge + j );

				edge = &file->GetEdge( abs( edgeNum ) );
				v1 = file->GetVertex( edge->vertexNum[0] );
				v2 = file->GetVertex( edge->vertexNum[1] );
				d1 = v1 * pathPlane.Normal() - pathPlane.Dist();
				d2 = v2 * pathPlane.Normal() - pathPlane.Dist();

				//if ( (d1 < CM_CLIP_EPSILON && d2 < CM_CLIP_EPSILON) || (d1 > -CM_CLIP_EPSILON && d2 > -CM_CLIP_EPSILON) ) {
				if ( FLOATSIGNBITSET( d1 ) == FLOATSIGNBITSET( d2 ) ) {
					continue;
				}

				split = v1 + (d1 / (d1 - d2)) * (v2 - v1);
				dist = frontPlane.Distance( split );
				if ( dist > bestDist ) {
					bestDist = dist;
					bestSplit = split;
				}
			}
		}

		return ( bestDist > -0.1f );
	}
}
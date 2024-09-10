/*
====================
idSurface_Polytope::SplitPolytope
====================
*/
int idSurface_Polytope::SplitPolytope( const idPlane &plane, const float epsilon, idSurface_Polytope **front, idSurface_Polytope **back ) const {
	int side, i, j, s, v0, v1, v2, edgeNum;
	idSurface *surface[2];
	idSurface_Polytope *polytopeSurfaces[2], *surf;
	int *onPlaneEdges[2];

	onPlaneEdges[0] = (int *) _alloca( indexes.Num() / 3 * sizeof( int ) );
	onPlaneEdges[1] = (int *) _alloca( indexes.Num() / 3 * sizeof( int ) );

	side = Split( plane, epsilon, &surface[0], &surface[1], onPlaneEdges[0], onPlaneEdges[1] );

	*front = polytopeSurfaces[0] = new (TAG_IDLIB_SURFACE) idSurface_Polytope;
	*back = polytopeSurfaces[1] = new (TAG_IDLIB_SURFACE) idSurface_Polytope;

	for ( s = 0; s < 2; s++ ) {
		if ( surface[s] ) {
			polytopeSurfaces[s] = new idSurface_Polytope( *surface[s] );
			delete surface[s];
			surface[s] = NULL;
		}
	}

	*front = polytopeSurfaces[0];
	*back = polytopeSurfaces[1];

	if ( side != SIDE_CROSS ) {
		return side;
	}

	// add triangles to close off the front and back polytope
	for ( s = 0; s < 2; s++ ) {

		surf = polytopeSurfaces[s];

		edgeNum = surf->edgeIndexes[onPlaneEdges[s][0]];
		v0 = surf->edges[abs(edgeNum)].verts[INT32_SIGNBITSET(edgeNum)];
		v1 = surf->edges[abs(edgeNum)].verts[INT32_SIGNBITNOTSET(edgeNum)];

		for ( i = 1; onPlaneEdges[s][i] >= 0; i++ ) {
			for ( j = i+1; onPlaneEdges[s][j] >= 0; j++ ) {
				edgeNum = surf->edgeIndexes[onPlaneEdges[s][j]];
				if ( v1 == surf->edges[abs(edgeNum)].verts[INT32_SIGNBITSET(edgeNum)] ) {
					v1 = surf->edges[abs(edgeNum)].verts[INT32_SIGNBITNOTSET(edgeNum)];
					SwapValues( onPlaneEdges[s][i], onPlaneEdges[s][j] );
					break;
				}
			}
		}

		for ( i = 2; onPlaneEdges[s][i] >= 0; i++ ) {
			edgeNum = surf->edgeIndexes[onPlaneEdges[s][i]];
			v1 = surf->edges[abs(edgeNum)].verts[INT32_SIGNBITNOTSET(edgeNum)];
			v2 = surf->edges[abs(edgeNum)].verts[INT32_SIGNBITSET(edgeNum)];
			surf->indexes.Append( v0 );
			surf->indexes.Append( v1 );
			surf->indexes.Append( v2 );
		}

		surf->GenerateEdgeIndexes();
	}

	return side;
}
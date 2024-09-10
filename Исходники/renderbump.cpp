static float TraceToMeshFace( const srfTriangles_t *highMesh, int faceNum,
							 float minDist, float maxDist,
							const idVec3 &point, const idVec3 &normal, idVec3 &sampledNormal,
							byte sampledColor[4] ) {
	int		j;
	float	dist;
	const idVec3	*v[3];
	const idPlane	*plane;
	idVec3	edge;
	float	d;
	idVec3	dir[3];
	float	baseArea;
	float	bary[3];
	idVec3	testVert;

	v[0] = &highMesh->verts[ highMesh->indexes[ faceNum * 3 + 0 ] ].xyz;
	v[1] = &highMesh->verts[ highMesh->indexes[ faceNum * 3 + 1 ] ].xyz;
	v[2] = &highMesh->verts[ highMesh->indexes[ faceNum * 3 + 2 ] ].xyz;

	plane = highMesh->facePlanes + faceNum;

	// only test against planes facing the same direction as our normal
	d = plane->Normal() * normal;
	if ( d <= 0.0001f ) {
		return DIST_NO_INTERSECTION;
	}

	// find the point of impact on the plane
	dist = plane->Distance( point );
	dist /= -d;

	testVert = point + dist * normal;

	// if this would be beyond our requested trace distance,
	// don't even check it
	if ( dist > maxDist ) {
		return DIST_NO_INTERSECTION;
	}

	if ( dist < minDist ) {
		return DIST_NO_INTERSECTION;
	}

	// if normal is inside all edge planes, this face is hit
	VectorSubtract( *v[0], point, dir[0] );
	VectorSubtract( *v[1], point, dir[1] );
	edge = dir[0].Cross( dir[1] );
	d = DotProduct( normal, edge );
	if ( d > 0.0f ) {
		return DIST_NO_INTERSECTION;
	}
	VectorSubtract( *v[2], point, dir[2] );
	edge = dir[1].Cross( dir[2] );
	d = DotProduct( normal, edge );
	if ( d > 0.0f ) {
		return DIST_NO_INTERSECTION;
	}
	edge = dir[2].Cross( dir[0] );
	d = DotProduct( normal, edge );
	if ( d > 0.0f ) {
		return DIST_NO_INTERSECTION;
	}

	// calculate barycentric coordinates of the impact point
	// on the high poly triangle
	bary[0] = idWinding::TriangleArea( testVert, *v[1], *v[2] );
	bary[1] = idWinding::TriangleArea( *v[0], testVert, *v[2] );
	bary[2] = idWinding::TriangleArea( *v[0], *v[1], testVert );

	baseArea = idWinding::TriangleArea( *v[0], *v[1], *v[2] );
	bary[0] /= baseArea;
	bary[1] /= baseArea;
	bary[2] /= baseArea;

	if ( bary[0] + bary[1] + bary[2] > 1.1 ) {
		bary[0] = bary[0];
		return DIST_NO_INTERSECTION;
	}

	// triangularly interpolate the normals to the sample point
	sampledNormal = vec3_origin;
	for ( j = 0 ; j < 3 ; j++ ) {
		sampledNormal += bary[j] * highMesh->verts[ highMesh->indexes[ faceNum * 3 + j ] ].normal;
	}
	sampledNormal.Normalize();

	sampledColor[0] = sampledColor[1] = sampledColor[2] = sampledColor[3] = 0;
	for ( int i = 0 ; i < 4 ; i++ ) {
		float	color = 0.0f;
		for ( j = 0 ; j < 3 ; j++ ) {
			color += bary[j] * highMesh->verts[ highMesh->indexes[ faceNum * 3 + j ] ].color[i];
		}
		sampledColor[i] = color;
	}
	return dist;
}
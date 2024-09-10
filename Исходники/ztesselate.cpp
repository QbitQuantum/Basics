float zTesselatePlanarPoly( FVec3 *verts, int count, FVec3 normal, int *tris, int &triCount ) {
	// BUILD an index of verts so that we know which one's
	// we've eaten up as we gobble convex polys

	int i, j, k;
	float area = 0.f;

	int *index = (int *)alloca( sizeof(int) * count );
	int indexCount = count;
	for( i=0; i<count; i++ ) index[i] = i;

	int lastIndexCount = 999999999;
	while( indexCount>=3 && indexCount < lastIndexCount ) {
		lastIndexCount = indexCount;
		for( i=0, j=1, k=2; k<indexCount; ) {
			// ANALYZE the triangle formed by the three points
			// There are possibilities:
			// 1. It is wound facing the normal
			// 2. It is wound facing away from the normal

			// COMPUTE the facing:
			FVec3 a = verts[ index[i] ];
			FVec3 b = verts[ index[j] ];
			FVec3 c = verts[ index[k] ];
			FVec3 ab = b;
			ab.sub( a );
			FVec3 bc = c;
			bc.sub( b );
			ab.cross( bc );
			float wound = ab.dot( normal );

			if( wound > 0.f ) {
				// CHECK for verts that are inside of this triangle

				int anyPointInside = 0;

				for( int l=0; l<indexCount; l++ ) {
					if( (l<i || l>k) ) {
						FVec2 tri[3];
						tri[0] = FVec2( verts[index[i]].x, verts[index[i]].y );
						tri[1] = FVec2( verts[index[j]].x, verts[index[j]].y );
						tri[2] = FVec2( verts[index[k]].x, verts[index[k]].y );
						FVec2 p = FVec2( verts[index[l]].x, verts[index[l]].y );
						if( zTesselatePointInPoly( 3, tri, p ) ) {
							i = j;
							j = k;
							k++;
							anyPointInside = 1;
							break;
						}
					}
				}

				if( !anyPointInside ) {
					// This poly is wound correctly and doesn't have
					// any other points inside of it so it is a valid triangle

					tris[triCount * 3 + 0] = index[i];
					tris[triCount * 3 + 1] = index[j];
					tris[triCount * 3 + 2] = index[k];
					triCount++;

					FVec3 a1 = verts[index[i]];
					a1.sub( verts[index[k]] );
					
					FVec3 a2 = verts[index[j]];
					a2.sub( verts[index[k]] );

					a1.cross( a2 );
					area += a1.mag();

					assert( triCount <= count );

					// REMOVE the middle point from the consideration list by shifting
					indexCount--;
					memmove( &index[j], &index[j+1], sizeof(int)*(indexCount-j) );
				}
			}
			else {
				// This tri is wound the wrong way so advance
				i = j;
				j = k;
				k++;
			}
		}
	}

	return area;
}
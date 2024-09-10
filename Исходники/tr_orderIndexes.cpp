/*
====================
R_OrderIndexes

Reorganizes the indexes so they will take best advantage
of the internal GPU vertex caches
====================
*/
void R_OrderIndexes( int numIndexes, glIndex_t *indexes ) {
	bool	*triangleUsed;
	int			numTris;
	glIndex_t	*oldIndexes;
	glIndex_t	*base;
	int			numOldIndexes;
	int			tri;
	int			i;
	vertRef_t	*vref, **vrefs, *vrefTable;
	int			numVerts;
	int			v1, v2;
	int			c_starts;
	//int			c_cost;

	if ( !r_orderIndexes.GetBool() ) {
		return;
	}

	// save off the original indexes
	oldIndexes = (glIndex_t *)_alloca( numIndexes * sizeof( *oldIndexes ) );
	memcpy( oldIndexes, indexes, numIndexes * sizeof( *oldIndexes ) );
	numOldIndexes = numIndexes;

	// make a table to mark the triangles when they are emited
	numTris = numIndexes / 3;
	triangleUsed = (bool *)_alloca( numTris * sizeof( *triangleUsed ) );
	memset( triangleUsed, 0, numTris * sizeof( *triangleUsed ) );

	// find the highest vertex number
	numVerts = 0;
	for ( i = 0 ; i < numIndexes ; i++ ) {
		if ( indexes[i] > numVerts ) {
			numVerts = indexes[i];
		}
	}
	numVerts++;

	// create a table of triangles used by each vertex
	vrefs = (vertRef_t **)_alloca( numVerts * sizeof( *vrefs ) );
	memset( vrefs, 0, numVerts * sizeof( *vrefs ) );

	vrefTable = (vertRef_t *)_alloca( numIndexes * sizeof( *vrefTable ) );
	for ( i = 0 ; i < numIndexes ; i++ ) {
		tri = i / 3;

		vrefTable[i].tri = tri;
		vrefTable[i].next = vrefs[oldIndexes[i]];
		vrefs[oldIndexes[i]] = &vrefTable[i];
	}

	// generate new indexes
	numIndexes = 0;
	c_starts = 0;
	while ( numIndexes != numOldIndexes ) {
		// find a triangle that hasn't been used
		for ( tri = 0 ; tri < numTris ; tri++ ) {
			if ( !triangleUsed[tri] ) {
				break;
			}
		}
		if ( tri == numTris ) {
			common->Error( "R_OrderIndexes: ran out of unused tris" );
		}

		c_starts++;

		do {
			// emit this tri
			base = oldIndexes + tri * 3;
			indexes[numIndexes+0] = base[0];
			indexes[numIndexes+1] = base[1];
			indexes[numIndexes+2] = base[2];
			numIndexes += 3;

			triangleUsed[tri] = true;

			// try to find a shared edge to another unused tri
			for ( i = 0 ; i < 3 ; i++ ) {
				v1 = base[i];
				v2 = base[(i+1)%3];

				for ( vref = vrefs[v1] ; vref ; vref = vref->next ) {
					tri = vref->tri;
					if ( triangleUsed[tri] ) {
						continue;
					}

					// if this triangle also uses v2, grab it
					if ( oldIndexes[tri*3+0] == v2
						|| oldIndexes[tri*3+1] == v2
						|| oldIndexes[tri*3+2] == v2 ) {
						break;
					}
				}
				if ( vref ) {
					break;
				}
			}

			// if we couldn't chain off of any verts, we need to find a new one
			if ( i == 3 ) {
				break;
			}
		} while ( 1 );
	}

	//c_cost = R_MeshCost( numIndexes, indexes );

}
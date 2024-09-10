/*
=============
R_ChopWinding

Clips a triangle from one buffer to another, setting edge flags
The returned buffer may be the same as inNum if no clipping is done
If entirely clipped away, clipTris[returned].numVerts == 0

I have some worries about edge flag cases when polygons are clipped
multiple times near the epsilon.
=============
*/
static int R_ChopWinding( clipTri_t clipTris[2], int inNum, const idPlane &plane ) {
	clipTri_t	*in, *out;
	float	dists[MAX_CLIPPED_POINTS];
	int		sides[MAX_CLIPPED_POINTS];
	int		counts[3];
	float	dot;
	int		i, j;
	idVec3	*p1, *p2;
	idVec3	mid;

	in = &clipTris[inNum];
	out = &clipTris[inNum^1];
	counts[0] = counts[1] = counts[2] = 0;

	// determine sides for each point
	for ( i = 0 ; i < in->numVerts ; i++ ) {
		dot = plane.Distance( in->verts[i] );
		dists[i] = dot;
		if ( dot < -LIGHT_CLIP_EPSILON ) {
			sides[i] = SIDE_BACK;
		} else if ( dot > LIGHT_CLIP_EPSILON ) {
			sides[i] = SIDE_FRONT;
		} else {
			sides[i] = SIDE_ON;
		}
		counts[sides[i]]++;
	}

	// if none in front, it is completely clipped away
	if ( !counts[SIDE_FRONT] ) {
		in->numVerts = 0;
		return inNum;
	}
	if ( !counts[SIDE_BACK] ) {
		return inNum;		// inout stays the same
	}

	// avoid wrapping checks by duplicating first value to end
	sides[i] = sides[0];
	dists[i] = dists[0];
	in->verts[in->numVerts] = in->verts[0];
	in->edgeFlags[in->numVerts] = in->edgeFlags[0];

	out->numVerts = 0;
	for ( i = 0 ; i < in->numVerts ; i++ ) {
		p1 = &in->verts[i];

		if ( sides[i] != SIDE_BACK ) {
			out->verts[out->numVerts] = *p1;
			if ( sides[i] == SIDE_ON && sides[i+1] == SIDE_BACK ) {
				out->edgeFlags[out->numVerts] = 1;
			} else {
				out->edgeFlags[out->numVerts] = in->edgeFlags[i];
			}
			out->numVerts++;
		}

		if ( (sides[i] == SIDE_FRONT && sides[i+1] == SIDE_BACK)
			|| (sides[i] == SIDE_BACK && sides[i+1] == SIDE_FRONT) ) {
			// generate a split point
			p2 = &in->verts[i+1];
			
			dot = dists[i] / (dists[i]-dists[i+1]);
			for ( j=0 ; j<3 ; j++ ) {
				mid[j] = (*p1)[j] + dot*((*p2)[j]-(*p1)[j]);
			}
				
			out->verts[out->numVerts] = mid;

			// set the edge flag
			if ( sides[i+1] != SIDE_FRONT ) {
				out->edgeFlags[out->numVerts] = 1;
			} else {
				out->edgeFlags[out->numVerts] = in->edgeFlags[i];
			}

			out->numVerts++;
		}
	}

	return inNum ^ 1;
}
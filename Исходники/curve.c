/*
 * R_SubdividePatchToGrid
 */
srfGridMesh_t *
R_SubdividePatchToGrid(int width, int height,
		       Drawvert points[MAX_PATCH_SIZE*MAX_PATCH_SIZE])
{
	int i, j, k, l;
	drawVert_t_cleared(prev);
	drawVert_t_cleared(next);
	drawVert_t_cleared(mid);
	float len, maxLen;
	int dir;
	int t;
	Drawvert	ctrl[MAX_GRID_SIZE][MAX_GRID_SIZE];
	float		errorTable[2][MAX_GRID_SIZE];

	for(i = 0; i < width; i++)
		for(j = 0; j < height; j++)
			ctrl[j][i] = points[j*width+i];

	for(dir = 0; dir < 2; dir++){

		for(j = 0; j < MAX_GRID_SIZE; j++)
			errorTable[dir][j] = 0;

		/* horizontal subdivisions */
		for(j = 0; j + 2 < width; j += 2){
			/* check subdivided midpoints against control points */

			/* FIXME: also check midpoints of adjacent patches against the control points
			 * this would basically stitch all patches in the same LOD group together. */

			maxLen = 0;
			for(i = 0; i < height; i++){
				Vec3	midxyz;
				Vec3	midxyz2;
				Vec3	dir;
				Vec3	projected;
				float	d;

				/* calculate the point on the curve */
				for(l = 0; l < 3; l++)
					midxyz[l] = (ctrl[i][j].xyz[l] + ctrl[i][j+1].xyz[l] * 2
						     + ctrl[i][j+2].xyz[l]) * 0.25f;

				/* see how far off the line it is
				 * using dist-from-line will not account for internal
				 * texture warping, but it gives a lot less polygons than
				 * dist-from-midpoint */
				subv3(midxyz, ctrl[i][j].xyz, midxyz);
				subv3(ctrl[i][j+2].xyz, ctrl[i][j].xyz, dir);
				normv3(dir);

				d = dotv3(midxyz, dir);
				scalev3(dir, d, projected);
				subv3(midxyz, projected, midxyz2);
				len = lensqrv3(midxyz2);	/* we will do the sqrt later */
				if(len > maxLen){
					maxLen = len;
				}
			}

			maxLen = sqrt(maxLen);

			/* if all the points are on the lines, remove the entire columns */
			if(maxLen < 0.1f){
				errorTable[dir][j+1] = 999;
				continue;
			}

			/* see if we want to insert subdivided columns */
			if(width + 2 > MAX_GRID_SIZE){
				errorTable[dir][j+1] = 1.0f/maxLen;
				continue;	/* can't subdivide any more */
			}

			if(maxLen <= r_subdivisions->value){
				errorTable[dir][j+1] = 1.0f/maxLen;
				continue;	/* didn't need subdivision */
			}

			errorTable[dir][j+2] = 1.0f/maxLen;

			/* insert two columns and replace the peak */
			width += 2;
			for(i = 0; i < height; i++){
				LerpDrawVert(&ctrl[i][j], &ctrl[i][j+1], &prev);
				LerpDrawVert(&ctrl[i][j+1], &ctrl[i][j+2], &next);
				LerpDrawVert(&prev, &next, &mid);

				for(k = width - 1; k > j + 3; k--)
					ctrl[i][k] = ctrl[i][k-2];
				ctrl[i][j + 1]	= prev;
				ctrl[i][j + 2]	= mid;
				ctrl[i][j + 3]	= next;
			}

			/* back up and recheck this set again, it may need more subdivision */
			j -= 2;

		}

		Transpose(width, height, ctrl);
		t = width;
		width	= height;
		height	= t;
	}


	/* put all the aproximating points on the curve */
	PutPointsOnCurve(ctrl, width, height);

	/* cull out any rows or columns that are colinear */
	for(i = 1; i < width-1; i++){
		if(errorTable[0][i] != 999){
			continue;
		}
		for(j = i+1; j < width; j++){
			for(k = 0; k < height; k++)
				ctrl[k][j-1] = ctrl[k][j];
			errorTable[0][j-1] = errorTable[0][j];
		}
		width--;
	}

	for(i = 1; i < height-1; i++){
		if(errorTable[1][i] != 999){
			continue;
		}
		for(j = i+1; j < height; j++){
			for(k = 0; k < width; k++)
				ctrl[j-1][k] = ctrl[j][k];
			errorTable[1][j-1] = errorTable[1][j];
		}
		height--;
	}

#if 1
	/* flip for longest tristrips as an optimization
	 * the results should be visually identical with or
	 * without this step */
	if(height > width){
		Transpose(width, height, ctrl);
		InvertErrorTable(errorTable, width, height);
		t = width;
		width	= height;
		height	= t;
		InvertCtrl(width, height, ctrl);
	}
#endif

	/* calculate normals */
	MakeMeshNormals(width, height, ctrl);

	return R_CreateSurfaceGridMesh(width, height, ctrl, errorTable);
}
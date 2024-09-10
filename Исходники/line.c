/*!
  \brief Calculate line distance.
  
  Sets (if not null):
   - px, py - point on line,
   - dist   - distance to line,
   - spdist - distance to point on line from segment beginning,
   - sldist - distance to point on line form line beginning along line

  \param points pointer to line_pnts structure
  \param ux,uy,uz point coordinates
  \param with_z flag if to use z coordinate (3D calculation)
  \param[out] px,py,pz point on line
  \param[out] dist distance to line,
  \param[out] spdist distance of point from segment beginning
  \param[out] lpdist distance of point from line

  \return nearest segment (first is 1)
 */
int Vect_line_distance(const struct line_pnts *points,
		       double ux, double uy, double uz,
		       int with_z,
		       double *px, double *py, double *pz,
		       double *dist, double *spdist, double *lpdist)
{
    int i;
    double distance;
    double new_dist;
    double tpx, tpy, tpz, tdist, tspdist, tlpdist = 0;
    double dx, dy, dz;
    int n_points;
    int segment;

    n_points = points->n_points;

    if (n_points == 1) {
	distance =
	    dig_distance2_point_to_line(ux, uy, uz, points->x[0],
					points->y[0], points->z[0],
					points->x[0], points->y[0],
					points->z[0], with_z, NULL, NULL,
					NULL, NULL, NULL);
	tpx = points->x[0];
	tpy = points->y[0];
	tpz = points->z[0];
	tdist = sqrt(distance);
	tspdist = 0;
	tlpdist = 0;
	segment = 0;

    }
    else {

	distance =
	    dig_distance2_point_to_line(ux, uy, uz, points->x[0],
					points->y[0], points->z[0],
					points->x[1], points->y[1],
					points->z[1], with_z, NULL, NULL,
					NULL, NULL, NULL);
	segment = 1;

	for (i = 1; i < n_points - 1; i++) {
	    new_dist = dig_distance2_point_to_line(ux, uy, uz,
						   points->x[i], points->y[i],
						   points->z[i],
						   points->x[i + 1],
						   points->y[i + 1],
						   points->z[i + 1], with_z,
						   NULL, NULL, NULL, NULL,
						   NULL);
	    if (new_dist < distance) {
		distance = new_dist;
		segment = i + 1;
	    }
	}

	/* we have segment and now we can recalculate other values (speed) */
	new_dist = dig_distance2_point_to_line(ux, uy, uz,
					       points->x[segment - 1],
					       points->y[segment - 1],
					       points->z[segment - 1],
					       points->x[segment],
					       points->y[segment],
					       points->z[segment], with_z,
					       &tpx, &tpy, &tpz, &tspdist,
					       NULL);

	/* calculate distance from beginning of line */
	if (lpdist) {
	    tlpdist = 0;
	    for (i = 0; i < segment - 1; i++) {
		dx = points->x[i + 1] - points->x[i];
		dy = points->y[i + 1] - points->y[i];
		if (with_z)
		    dz = points->z[i + 1] - points->z[i];
		else
		    dz = 0;

		tlpdist += hypot(hypot(dx, dy), dz);
	    }
	    tlpdist += tspdist;
	}
	tdist = sqrt(distance);
    }

    if (px)
	*px = tpx;
    if (py)
	*py = tpy;
    if (pz && with_z)
	*pz = tpz;
    if (dist)
	*dist = tdist;
    if (spdist)
	*spdist = tspdist;
    if (lpdist)
	*lpdist = tlpdist;

    return (segment);
}
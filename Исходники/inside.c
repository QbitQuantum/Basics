SEXP shp_inside(SEXP slist, SEXP pxv, SEXP pyv, SEXP clockw, SEXP sAll) {
    SEXP xv, yv, pv, res;
    double *x, *y, *px, *py;
    int *p, up = 0, *r, np, ns, mp = 0, i,
	expected = (asInteger(clockw) == TRUE) ? 1 : -1,
	all = (asInteger(sAll) == TRUE) ? 1 : 0;
    if (TYPEOF(slist) != VECSXP || !inherits(slist, "shp"))
	Rf_error("input must be a list of shapes (shp object)");
    if (LENGTH(slist) == 0)
	return allocVector(INTSXP, 0);
    if (LENGTH(pxv) != LENGTH(pyv))
	Rf_error("point coordinates must have the same length");
    if (TYPEOF(pxv) != REALSXP) {
	pxv = PROTECT(coerceVector(pxv, REALSXP)); up++;
    }
    if (TYPEOF(pyv) != REALSXP) {
	pyv = PROTECT(coerceVector(pyv, REALSXP)); up++;
    }
    px = REAL(pxv);
    py = REAL(pyv);
    np = LENGTH(pxv);
    ns = LENGTH(slist);
    if (!all) { /* match-like behavior - find the first only */
	res = allocVector(INTSXP, np);
	r = INTEGER(res);
	memset(r, 0, sizeof(*r) * np);
	for (i = 0; i < ns; i++) {
	    int j;
	    double *bb;
	    SEXP shp = VECTOR_ELT(slist, i);
	    bb = REAL(VECTOR_ELT(shp, 2));
	    pv = VECTOR_ELT(shp, 3); p = INTEGER(pv);
	    xv = VECTOR_ELT(shp, 4); x = REAL(xv);
	    yv = VECTOR_ELT(shp, 5); y = REAL(yv);
	    for (j = 0; j < np; j++) {
		double X = px[j], Y = py[j];
		/* is the point inside the bounding box? */
		if (X >= bb[0] && X <= bb[2] && Y >= bb[1] && Y <= bb[3]) {
		    if (inside_(X, Y, x, y, LENGTH(xv), expected) && !r[j]) {
			mp++;
			r[j] = i + 1;
			if (mp >= np) { /* if all points got matched, get out */
			    i = ns;
			    break;
			}
		    }
		}
	    }
	}
	if (mp < np) /* replace 0 (no match) with NA */
	    for (i = 0; i < np; i++)
		if (r[i] == 0) r[i] = NA_INTEGER;
    } else { /* return a list of all matches - useful for heavily overlapping shapes */
	SEXP tmp = PROTECT(allocVector(INTSXP, ns)); /* temporary vector to store per-point matches */
	int *ti = INTEGER(tmp);
	memset(ti, 0, sizeof(ti[0]) * ns);
	res = PROTECT(allocVector(VECSXP, np)); /* result list */
	up += 2;
	for (i = 0; i < np; i++) {
	    double X = px[i], Y = py[i];
	    int j, k = 0;
	    for (j = 0; j < ns; j++) {
		double *bb;
		SEXP shp = VECTOR_ELT(slist, j);
		bb = REAL(VECTOR_ELT(shp, 2));
		if (X >= bb[0] && X <= bb[2] && Y >= bb[1] && Y <= bb[3]) {
		    pv = VECTOR_ELT(shp, 3); p = INTEGER(pv);
		    xv = VECTOR_ELT(shp, 4); x = REAL(xv);
		    yv = VECTOR_ELT(shp, 5); y = REAL(yv);
		    if (inside_(X, Y, x, y, LENGTH(xv), expected))
			ti[k++] = j + 1;
		}
	    }
	    if (k) {
		memcpy(INTEGER(SET_VECTOR_ELT(res, i, allocVector(INTSXP, k))), ti, sizeof(ti[0]) * k);
		memset(ti, 0, sizeof(ti[0]) * k);
	    }
	}	    
    }
    if (up) UNPROTECT(up);
    return res;
}
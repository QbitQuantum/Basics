/* Find eigenvalues of 3x3 symmetric system by solving cubic. */
void 
ch_evals3 (
    double H[3][3],		/* 3x3 sym matrix for lowest eigenvalue */
    double *eval1,		/* smallest eigenvalue */
    double *eval2,		/* middle eigenvalue */
    double *eval3		/* largest eigenvalue */
)
{
    double    mat[3][3];	/* scaled version of H */
    double    a1, a2, a3;	/* coefficents of cubic equation */
    double    q, r;		/* intermediate terms */
    double    q3, r2;		/* powers of q and r */
    double    theta;		/* angular parameter */
    double    root1, root2, root3;	/* three roots of cubic */
    double    tol = 1.0e-6;	/* allowed deviation */
    double    xmax;		/* largest matrix element for scaling */
    int       i, j;		/* loop indices */
    double    determinant();

    /* This first requires solving a cubic equation. */
    /* Normalize to avoid any numerical problems. */
    xmax = 0.0;
    for (i = 0; i < 3; i++) {
	for (j = i; j < 3; j++) {
	    if (fabs(H[i][j]) > xmax)
		xmax = fabs(H[i][j]);
	}
    }
    if (xmax != 0) {
	for (i = 0; i < 3; i++) {
	    for (j = 0; j < 3; j++)
		mat[i][j] = H[i][j] / xmax;
	}
    }


    a1 = -(mat[0][0] + mat[1][1] + mat[2][2]);
    a2 = (mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0]) +
       (mat[0][0] * mat[2][2] - mat[0][2] * mat[2][0]) +
       (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]);
    a3 = -determinant(mat, 3);

    if (a3 == 0) {
	root1 = 0;
	/* Solve quadratic. */
	q = -.5 * (a1 + sign(a1) * sqrt(a1 * a1 - 4 * a2));
	root2 = q;
	root3 = a2 / q;
    }

    else {			/* solve cubic */
	q = (a1 * a1 - 3 * a2) / 9;
	r = (2 * a1 * a1 * a1 - 9 * a1 * a2 + 27 * a3) / 54;
	q3 = q * q * q;
	r2 = r * r;

	/* To avoid missing a root, check for roundoff. */
	if ((q3 < r2) && fabs(q3 - r2) < tol * (fabs(q3) + fabs(r2))) {
	    q3 = r2;
	}

	if (q3 >= r2) {		/* Three real roots. */
	    if (r == 0)
		theta = HALFPI;
	    else {
		q3 = sqrt(q3);
		if (q3 < fabs(r))
		    q3 = fabs(r);
		theta = acos(r / q3);
	    }
	    q = -2 * sqrt(q);

	    root1 = q * cos(theta / 3) - a1 / 3;
	    root2 = q * cos((theta + TWOPI) / 3) - a1 / 3;
	    root3 = q * cos((theta + 2 * TWOPI) / 3) - a1 / 3;
	}
	else {			/* Only one real root. */
	    theta = sqrt(r2 - q3) + fabs(r);
	    theta = pow(theta, 1.0 / 3.0);

	    root1 = root2 = root3 = -sign(r) * (theta + q / theta) - a1 / 3;
	}
    }
    root1 *= xmax;
    root2 *= xmax;
    root3 *= xmax;
    *eval1 = min(root1, root2);
    *eval1 = min(*eval1, root3);
    *eval3 = max(root1, root2);
    *eval3 = max(*eval3, root3);
    if (root1 != *eval1 && root1 != *eval3)
	*eval2 = root1;
    else if (root2 != *eval1 && root2 != *eval3)
	*eval2 = root2;
    else
	*eval2 = root3;
}
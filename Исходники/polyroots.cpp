int SolveQuartic( double c[5], double s[4] )
{
    double  coeffs[ 4 ];
    double  z, u, v, sub;
    double  A, B, C, D;
    double  sq_A, p, q, r;
    int     i, num;

    /* normal form: x^4 + Ax^3 + Bx^2 + Cx + D = 0 */

    A = c[ 3 ] / c[ 4 ];
    B = c[ 2 ] / c[ 4 ];
    C = c[ 1 ] / c[ 4 ];
    D = c[ 0 ] / c[ 4 ];

    /*  substitute x = y - A/4 to eliminate cubic term:
	x^4 + px^2 + qx + r = 0 */

    sq_A = A * A;
    p = - 3.0/8 * sq_A + B;
    q = 1.0/8 * sq_A * A - 1.0/2 * A * B + C;
    r = - 3.0/256*sq_A*sq_A + 1.0/16*sq_A*B - 1.0/4*A*C + D;

    if (IsZero(r))
    {
	/* no absolute term: y(y^3 + py + q) = 0 */

	coeffs[ 0 ] = q;
	coeffs[ 1 ] = p;
	coeffs[ 2 ] = 0;
	coeffs[ 3 ] = 1;

	num = SolveCubic(coeffs, s);

	s[ num++ ] = 0;
    }
    else
    {
	/* solve the resolvent cubic ... */

	coeffs[ 0 ] = 1.0/2 * r * p - 1.0/8 * q * q;
	coeffs[ 1 ] = - r;
	coeffs[ 2 ] = - 1.0/2 * p;
	coeffs[ 3 ] = 1;

	(void) SolveCubic(coeffs, s);

	/* ... and take the one real solution ... */

	z = s[ 0 ];

	/* ... to build two quadric equations */

	u = z * z - r;
	v = 2 * z - p;

	if (IsZero(u))
	    u = 0;
	else if (u > 0)
	    u = sqrt(u);
	else
	    return 0;

	if (IsZero(v))
	    v = 0;
	else if (v > 0)
	    v = sqrt(v);
	else
	    return 0;

	coeffs[ 0 ] = z - u;
	coeffs[ 1 ] = q < 0 ? -v : v;
	coeffs[ 2 ] = 1;

	num = SolveQuadric(coeffs, s);

	coeffs[ 0 ]= z + u;
	coeffs[ 1 ] = q < 0 ? v : -v;
	coeffs[ 2 ] = 1;

	num += SolveQuadric(coeffs, s + num);
    }

    /* resubstitute */

    sub = 1.0/4 * A;

    for (i = 0; i < num; ++i)
	s[ i ] -= sub;

    return num;
}
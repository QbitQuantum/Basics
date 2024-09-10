void
rotate(obj *p, double phi, obj *q)
	/* double	phi;	in radians */
{
register double	x, y;
	double	M[6];

	M[3] =   M[0] = Cos(phi);
	M[2] = -(M[1] = Sin(phi));
	if (q == NULL)
		M[4] = M[5] = 0;
	else {
		x = Xformx(q, 1, q->o_x, q->o_y);
		y = Xformy(q, 0, q->o_x, q->o_y);
		M[4] = (1 - M[0]) * x + M[1] * y;
		M[5] = (1 - M[0]) * y - M[1] * x;
	}
	apply(p, M, 1);
}
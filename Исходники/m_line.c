/*
 * Compute the shortest line segment connecting two lines in R^3.
 * Adapted from Paul Bourke's example code:
 * http://paulbourke.net/geometry/lineline3d
 */
int
M_LineLineShortest3(M_Line3 L1, M_Line3 L2, M_Line3 *Ls)
{
	M_Vector3 p1 = M_LineInitPt3(L1);
	M_Vector3 p2 = M_LineTermPt3(L1);
	M_Vector3 p3 = M_LineInitPt3(L2);
	M_Vector3 p4 = M_LineTermPt3(L2);
	M_Vector3 p13, p43, p21;
	M_Real d1343, d4321, d1321, d4343, d2121;
	M_Real numer, denom;
	M_Real muA, muB;

	p13 = M_VecSub3(p1, p3);
	p43 = M_VecSub3(p4, p3);
	if (Fabs(p43.x) < M_MACHEP &&
	    Fabs(p43.y) < M_MACHEP &&
	    Fabs(p43.z) < M_MACHEP)
		return (0);

	p21 = M_VecSub3(p2, p1);
	if (Fabs(p21.x) < M_MACHEP &&
	    Fabs(p21.y) < M_MACHEP &&
	    Fabs(p21.z) < M_MACHEP)
		return (0);

	d1343 = M_VecDot3p(&p13, &p43);
	d4321 = M_VecDot3p(&p43, &p21);
	d4343 = M_VecDot3p(&p43, &p43);
	d2121 = M_VecDot3p(&p21, &p21);

	denom = d2121*d4343 - d4321*d4321;
	if (Fabs(denom) < M_MACHEP) {
		return (0);
	}
	numer = d1343*d4321 - d1321*d4343;

	muA = numer/denom;
	muB = (d1343 + d4321*muA) / d4343;

	if (Ls != NULL) {
		*Ls = M_LineFromPts3(
		    M_VecAdd3(p1, M_VecScale3(p21,muA)),
		    M_VecAdd3(p3, M_VecScale3(p43,muB)));
	}
	return (1);
}
/* Compute the intersection of two circles. */
M_GeomSet2
M_IntersectCircleCircle2(M_Circle2 C1, M_Circle2 C2)
{
	M_GeomSet2 Sint = M_GEOM_SET_EMPTY;
	M_Real d12 = M_VecDistance2(C1.p, C2.p);
	M_Real a, h, b;
	M_Vector2 p;
	M_Geom2 G1, G2;

	if (Fabs(C1.p.x - C2.p.x) <= M_MACHEP &&
	    Fabs(C1.p.x - C2.p.x) <= M_MACHEP &&
	    Fabs(C1.r - C2.r) <= M_MACHEP) {
		G1.type = M_CIRCLE;
		G1.g.circle = C1;
		M_GeomSetAdd2(&Sint, &G1);
		return (Sint);
	}

	if (d12 > (C1.r + C2.r) ||
	    d12 < Fabs(C1.r - C2.r)) {
		return (Sint);
	}

	a = (C1.r*C1.r - C2.r*C2.r + d12*d12) / (2.0*d12);
	h = Sqrt(C1.r*C1.r - a*a);
	p = M_VecLERP2(C1.p, C2.p, a/d12);
	b = h/d12;

	G1.type = M_POINT;
	G1.g.point.x = p.x - b*(C2.p.y - C1.p.y);
	G1.g.point.y = p.y + b*(C2.p.x - C1.p.x);
	G2.type = M_POINT;
	G2.g.point.x = p.x + b*(C2.p.y - C1.p.y);
	G2.g.point.y = p.y - b*(C2.p.x - C1.p.x);

	M_GeomSetAdd2(&Sint, &G1);
	if (M_VecDistance2(G1.g.point, G2.g.point) > M_MACHEP) {
		M_GeomSetAdd2(&Sint, &G2);
	}
	return (Sint);
}
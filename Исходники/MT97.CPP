/* and one CROSS has been moved out from the if-else if-else */
int intersect_triangle3(const RAYTRI *rt)
{
	double u, v;
	double edge1[3], edge2[3], tvec[3], pvec[3], qvec[3];
	double det,inv_det;

	/* find vectors for two edges sharing rt->v0 */
	SUB(edge1, rt->v1, rt->v0);
	SUB(edge2, rt->v2, rt->v0);

	/* begin calculating determinant - also used to calculate U parameter */
	CROSS(pvec, rt->dir, edge2);

	/* if determinant is near zero, ray lies in plane of triangle */
	det = DOT(edge1, pvec);

	/* calculate distance from rt->v0 to ray origin */
	SUB(tvec, rt->org, rt->v0);
	inv_det = 1.0 / det;

	CROSS(qvec, tvec, edge1);

	if (det > EPSILON)
	{
		u = DOT(tvec, pvec);
		if (u < 0.0 || u > det)
			return 0;

		/* calculate V parameter and test bounds */
		v = DOT(rt->dir, qvec);
		if (v < 0.0 || u + v > det)
			return 0;

	}
	else if(det < -EPSILON)
	{
		/* calculate U parameter and test bounds */
		u = DOT(tvec, pvec);
		if (u > 0.0 || u < det)
			return 0;

		/* calculate V parameter and test bounds */
		v = DOT(rt->dir, qvec) ;
		if (v > 0.0 || u + v < det)
			return 0;
	}
	else return 0;  /* ray is parallell to the plane of the triangle */

	double t = DOT(edge2, qvec) * inv_det;
	if(t<0.0 || t>1.0)	return 0;

	return 1;
}
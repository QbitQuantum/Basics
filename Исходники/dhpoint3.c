double
DHPt3Distance(point4 p0, point4 p1, int metric)
{
	double d0, d1;
	point4 diff;
    switch (metric)	{
	case DG_EUCLIDEAN:
	    VSUB3(p0,p1, diff);
	    return(MAGNITUDE3(diff));
	    break;
	case DG_HYPERBOLIC:
	    d0 =INPRO31(p0, p0);
	    d1 =INPRO31(p1, p1);
	    if (d0 >= 0.0 || d1 >= 0.0)	{
		fprintf(stderr,"Invalid points in dist_proj3\n");
		return(0.0);
		}
	    return(acosh( ABS( INPRO31(p0, p1) / sqrt(d0 * d1))));
	    break;
	case DG_SPHERICAL:
	    d0 =INPRO31(p0, p0);
	    d1 =INPRO31(p1, p1);
	    return(acos( ABS( INPRO4(p0, p1) / sqrt(d0 * d1))));
	    break;

	}
    return (double)0;
}
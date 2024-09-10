/**
 *@brief fold space to extend the domain over which we can take
 * noise values.
 *
 *@n x, y, z are set to the noise space location for the source point.
 *@n ix, iy, iz are the integer lattice point (integer portion of x, y, z)
 *@n fx, fy, fz are the fractional lattice distance above ix, iy, iz
 *
 * The noise function has a finite domain, which can be exceeded when
 * using fractal textures with very high frequencies.  This routine is
 * designed to extend the effective domain of the function, albeit by
 * introducing periodicity.	-FKM 4/93
 */
static void
filter_args(fastf_t *src, fastf_t *p, fastf_t *f, int *ip)
{
    register int i;
    point_t dst;
    static unsigned long max2x = ~((unsigned long)0);
    static unsigned long max = (~((unsigned long)0)) >> 1;

    for (i=0; i < 3; i++) {
	/* assure values are positive */
	if (src[i] < 0) dst[i] = -src[i];
	else dst[i] = src[i];


	/* fold space */
	while (dst[i] > max || dst[i]<0) {
	    if (dst[i] > max) {
		dst[i] = max2x - dst[i];
	    } else {
		dst[i] = -dst[i];
	    }
	}

    }

    p[X] = dst[0];	ip[X] = FLOOR(p[X]);	f[X] = p[X] - ip[X];
    p[Y] = dst[1];	ip[Y] = FLOOR(p[Y]);	f[Y] = p[Y] - ip[Y];
    p[Z] = dst[2];	ip[Z] = FLOOR(p[Z]);	f[Z] = p[Z] - ip[Z];
}
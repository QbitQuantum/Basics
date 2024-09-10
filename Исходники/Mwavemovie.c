static void init_wave(int init, 
		      int nx, float dx,
		      int nz, float dz,
		      sf_complex *pp /* [nx] */,
		      float wov, int nw, int iw)
{
    int ix;
    float x,x0,z0,phase,amp;
    
    x0 = nx*dx/3;
    z0 = nz*dz/3;

    switch(init) {
	case 1: /*  planar wave @ 15deg */
	    for (ix=0; ix < nx; ix++) {
		x = (ix+1)*dx - x0;
		phase  = wov*x*sinf(15*SF_PI/180.);
		pp[ix] = cexpf(sf_cmplx(0.,phase));
	    }
	    break;
	case 2: /* expanding spherical wave */
	    for (ix=0; ix < nx; ix++) {
		x = (ix+1)*dx - x0;
		phase  = wov*hypotf(z0,x);
		pp[ix] = cexpf(sf_cmplx(0.,phase));
	    }
	    break;
	case 3: /* point source */
	    for (ix=0; ix < nx; ix++) {
		pp[ix]=sf_cmplx(0.,0.);
	    }
	    pp[nx/3-1] = sf_cmplx(1.,0.);
	    break;
	case 4: /* collapsing spherical wave */
	    for (ix=0; ix < nx; ix++) {
		x = (ix+1)*dx - x0;
		phase  = -wov*hypotf(z0,x);
		pp[ix] = cexpf(sf_cmplx(0.,phase));
	    }
	    break;
	default:
	    sf_error("Unknown init=%d",init);
    }

    amp = (nw-iw+1.0)/nw;
    amp = cosf((1-amp)*(0.5*SF_PI));
    amp *= amp;

    for (ix=0; ix < nx; ix++) {
#ifdef SF_HAS_COMPLEX_H
	pp[ix] *= amp;
#else
	pp[ix] = sf_crmul(pp[ix],amp);
#endif
    }
}
void potential_double(int *ndim,double *pos,double *acc,double *pot,double *time)
{
    double apar, qpar, spar, ppar, lpar, rpar, rcyl;
    double i1,i2,i3;

// 20070312 bwillett added ppar - the plummer denominator: r + rc = sqrt(x^2+y^2+z^2) + rc
// 20070312 bwillett added lpar - the logarithmic argument: R^2 + (z/q)^2 + d^2
// 20070427 bwillett added rpar - the spherical radius: r + rc - rc = ppar - plu_rc
// 20070501 bwillett added apar - a + qpar
// 20070507 bwillett took out pow statements
// 20070507 bwillett used hypot from math.h

    rcyl = hypot(pos[X],pos[Y]);
    ppar = sqrt ((pos[X]*pos[X])+(pos[Y]*pos[Y])+(pos[Z]*pos[Z])) + plu_rc;
    rpar = ppar - plu_rc;
    lpar = (rcyl*rcyl) + ((pos[Z]/q)*(pos[Z]/q)) + (d*d);
	
// 20070312 bwillett added plummer sphere potential and logarithmic potential
    //*pot = (-(miya_mass)/spar) + (-(plu_mass)/ppar) + (vhalo*vhalo*log(lpar));

// 20070312 bwillett rest left unchanged
// 20070427 bwillett changed the acceleration field

// This is only valid for 3 dimensions, and is in (x,y,z)
// Recall F_mu = -grad_mu U
// So a_mu = -grad_mu Phi
// I did these derivatives in Mathematica, and will try to keep it consistent with the conventions written above

	acc[X] = - ( ( (2.0*vhalo*vhalo*pos[X])/(lpar) ) + ( (plu_mass*pos[X])/(rpar*ppar*ppar) ) );
	acc[Y] = - ( ( (2.0*vhalo*vhalo*pos[Y])/(lpar) ) + ( (plu_mass*pos[Y])/(rpar*ppar*ppar) ) );
	acc[Z] = - ( ( (2.0*vhalo*vhalo*pos[Z])/(lpar) ) + ( (plu_mass*pos[Z])/(rpar*ppar*ppar) ) );



// willeb 20080911 - do the integrals required for the ring potential
// X-integral

        double x,y,z;

        x = pos[X];
        y = pos[Y];
        z = pos[Z];

        double Mdisk = disk_mass;
	double R = disk_radius;
        double phi = 0, dphi = 0;
        double r = 0, dr = 0;
        double zp = 0, dzp = 0;
        double N = 50;
        double i,j,k;
        double resultx = 0, resulty = 0, resultz = 0;

        dphi = (2*PI)/N;
        dr = (R)/N;
        dzp = (h)/N;

	// X-integral
        for(phi=0;phi<=2*PI;phi+=(2*PI)/N) {
                for(r=0;r<=R;r+=R/N) {
                        for(zp=-h/2;zp<h/2;zp+=h/N) {
                                resultx += funcx(x,y,z,zp,r,phi,h)*r*dr*dphi*dzp;
                        }
                }
        }

        resultx *= -(Mdisk)/(PI*R*R*h);

	// Y-integral
        for(phi=0;phi<=2*PI;phi+=(2*PI)/N) {
                for(r=0;r<=R;r+=R/N) {
                        for(zp=-h/2;zp<h/2;zp+=h/N) {
                                resulty += funcy(x,y,z,zp,r,phi,h)*r*dr*dphi*dzp;
                        }
                }
        }

        resulty *= -(Mdisk)/(PI*R*R*h);

	// Z-integral
        for(phi=0;phi<=2*PI;phi+=(2*PI)/N) {
                for(r=0;r<=R;r+=R/N) {
                        for(zp=-h/2;zp<h/2;zp+=h/N) {
                                resultz += funcz(x,y,z,zp,r,phi,h)*r*dr*dphi*dzp;
                        }
                }
        }

        resultz *= -(Mdisk)/(PI*R*R*h);

	//printf("%f %f %f %f %f %f\n", x, y, z, resultx, resulty, resultz);

	acc[X] += resultx;
	acc[Y] += resulty;
	acc[Z] += resultz;
}
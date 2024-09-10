void poisson(real x[], int nmax, real w0, int& nprof, real& v20)

//       Self-contained 1-D (spherical) Poisson's equation solver.
//       Currently knows about normal and lowered King models.
//
//        Input:  nmax is the maximum number of points allowed
//                w0 is the dimensionless central potential
//                iout allows messages if nonzero

//        Output: x   is scaled radius (r/rc)
//                d   is scaled density (1 at center)
//                v2  is scaled velocity dispersion (1 at center)
//                psi is scaled potential (-W0 at center)
//                zm  is cumulative mass (scaling from x, d scalings)
//                nprof is the actual number of points generated
//                v20 is the central 3-D velocity dispersion (unit = sig^2)

{

  int i, iflag2; 
  real psi0, xn, xo, fac;
  real y[2];

  psi0 = - abs(w0);

  // Initialize at center of cluster.

  xn = 0;
  y[0] = 0;
  y[1] = psi0;
  x[0] = 0;
  psi[0] = psi0;
  v2[0] = 1;
  zm[0] = 0;

  // Establish density scaling factor.

  get_dens_and_vel(psi0, d[0], v2[0]);
  dc_inverse = 1./d[0];

  fac = pow(10, (log10(RMAX/RLIN) / (nmax-NLIN)));

// 	Poisson's equation is:
//
// 		(1/r^2) d/dr (r^2 dphi/dr)  =  4 pi G rho,
//
// 	where r is radius, phi is potential, and rho is density, given
// 	(for equal-mass stars) by
//
// 		rho	=  {integral (v < ve)} 4 pi v^2 f(v) dv,
//
// 	where ve is the escape velocity,
//
// 		ve^2	=  -2 phi.
//
// 	The (3-D) velocity distribution is
//
// 		f(v)	=  A (exp(-v^2 / 2 sig^2)
// 					 - exp(-ve^2 / 2 sig^2)),
//
// 	where sig^2 is a 1-D velocity dispersion (not quite the
// 	central velocity dispersion, except in the limit of infinite
// 	central potential).  In King's (1966) paper, he uses
// 	j^2 = 1 / (2 sig^2).
//
// 	Following King, we define the core radius rc by
//
// 		rc^2	=  9 sig^2 / (4 pi G rho0)
//
// 	and the dimensionless depth as
//
// 		W0	=  -phi0 / sig^2,
//
// 	where rho0 and phi0 are the central density and potential,
// 	respectively.
//
// 	We then scale as follows:
//
// 		x	=  r / rc
//
// 		d	=  rho / rho0
//
// 		psi	=  phi / sig^2,
//
// 	to obtain
//
// 		(x psi)''  =  9 x d,
//
// 	where ' = d/dx.
//
// 	We integrate this ODE from the cluster center (x = 0, d = 1,
// 	psi = -W0) to the tidal radius (d = 0) by defining
//
//		y(0)	=  (x psi)
//		y(1)	=  y(0)'
//
//	We cover the first RLIN core radii linearly with NLIN points;
//	the remaining coverage is logarithmic, out to RMAX core radii,
//	if necessary.  We stop when d <= 0.

  iflag2 = 0;

  for (i = 1; i <= nmax; i++) {

      xo = xn;
      if (i <= NLIN)
          xn = (RLIN * i) / NLIN;
      else
	  xn = fac * xo;

      real dx = 0.051*(xn-xo);

      rk4(xo, xn, y, 2, dx);

      //  N.B. Remember that y(1) is x*psi and xo is updated by step.

      xn = xo;

      x[i] = xn;
      psi[i] = y[0] / xn;

      v2[i] = 1;
      get_dens_and_vel(psi[i], d[i], v2[i]);

      if (d[i] < 0) {

 	// Density is negative, calculation is over.
 	// Interpolate to the tidal radius.

 	x[i] = x[i-1] + (x[i] - x[i-1]) / (0.1 - d[i]/d[i-1]);
 	d[i] = 0;
 	v2[i] = 0;

      }

      zm[i] = x[i] * y[1] - y[0];

      if (d[i] > 0) {

	  // Strange syntax because d = NaN (because of earlier error)
	  // will test FALSE in "if (d < 0)".

      } else {

          iflag2 = 1;
          break;

      }
  }

  if (iflag2 == 0) i = nmax;

  nprof = i;

  // Scale d and v2 to their central values.  Save v20 (unit = sig^2).

  v20 = v2[0];
  for (i = nprof; i >= 0; i--) {
      d[i] = d[i] / d[0];
      v2[i] = v2[i] / v2[0];
      zm[i] = (fourpi/9) * zm[i];
  }

}
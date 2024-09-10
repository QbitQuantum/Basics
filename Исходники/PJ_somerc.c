#define PROJ_PARMS__ \
	double	K, c, hlf_e, kR, cosp0, sinp0;
#define PJ_LIB__
#include	"projects.h"
PROJ_HEAD(somerc, "Swiss. Obl. Mercator") "\n\tCyl, Ell\n\tFor CH1903";
#define EPS	1.e-10
#define NITER 6
FORWARD(e_forward);
	double phip, lamp, phipp, lampp, sp, cp;

	sp = P->e * sin(lp.phi);
	phip = 2.* atan( exp( P->c * (
		log(tan(FORTPI + 0.5 * lp.phi)) - P->hlf_e * log((1. + sp)/(1. - sp)))
		+ P->K)) - HALFPI;
	lamp = P->c * lp.lam;
	cp = cos(phip);
	phipp = aasin(P->ctx,P->cosp0 * sin(phip) - P->sinp0 * cp * cos(lamp));
	lampp = aasin(P->ctx,cp * sin(lamp) / cos(phipp));
	xy.x = P->kR * lampp;
	xy.y = P->kR * log(tan(FORTPI + 0.5 * phipp));
	return (xy);
}
INVERSE(e_inverse); /* ellipsoid & spheroid */
	double phip, lamp, phipp, lampp, cp, esp, con, delp;
	int i;

	phipp = 2. * (atan(exp(xy.y / P->kR)) - FORTPI);
	lampp = xy.x / P->kR;
	cp = cos(phipp);
	phip = aasin(P->ctx,P->cosp0 * sin(phipp) + P->sinp0 * cp * cos(lampp));
	lamp = aasin(P->ctx,cp * sin(lampp) / cos(phip));
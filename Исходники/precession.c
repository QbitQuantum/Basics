/* Equ 20.3, 20.4 pg 126 
*/
void ln_get_equ_prec (struct ln_equ_posn * mean_position, double JD, struct ln_equ_posn * position)
{
	long double t, t2, t3, A, B, C, zeta, eta, theta, ra, dec, mean_ra, mean_dec;
	
	/* change original ra and dec to radians */
	mean_ra = ln_deg_to_rad (mean_position->ra);
	mean_dec = ln_deg_to_rad (mean_position->dec);

	/* calc t, zeta, eta and theta for J2000.0 Equ 20.3 */
	t = (JD - JD2000) / 36525.0;
	t *= 1.0 / 3600.0;
	t2 = t * t;
	t3 = t2 *t;
	zeta = 2306.2181 * t + 0.30188 * t2 + 0.017998 * t3;
	eta = 2306.2181 * t + 1.09468 * t2 + 0.041833 * t3;
	theta = 2004.3109 * t - 0.42665 * t2 - 0.041833 * t3;
	zeta = ln_deg_to_rad (zeta);
	eta = ln_deg_to_rad (eta);
	theta = ln_deg_to_rad (theta); 

	/* calc A,B,C equ 20.4 */
	A = cosl (mean_dec) * sinl (mean_ra + zeta);
	B = cosl (theta) * cosl (mean_dec) * cosl (mean_ra + zeta) - sinl (theta) * sinl (mean_dec);
	C = sinl (theta) * cosl (mean_dec) * cosl (mean_ra + zeta) + cosl (theta) * sinl (mean_dec);
	
	ra = atan2l (A,B) + eta;
	
	/* check for object near celestial pole */
	if (mean_dec > (0.4 * M_PI) || mean_dec < (-0.4 * M_PI)) {
		/* close to pole */
		dec = acosl (sqrt(A * A + B * B));
		if (mean_dec < 0.)
		  dec *= -1; /* 0 <= acos() <= PI */
	} else {
		/* not close to pole */
		dec = asinl (C);
	}

	/* change to degrees */
	position->ra = ln_range_degrees (ln_rad_to_deg (ra));
	position->dec = ln_rad_to_deg (dec);
}
static float
kepler(const float ecc, float mean_anom)
{
	float curr, err, thresh;
	int is_negative = 0, n_iter = 0;

	if( !mean_anom) {
		return( 0.);
	}

	if( ecc < .3) {   /* low-eccentricity formula from Meeus,  p. 195 */
		curr = atan2f( sinf( mean_anom), cosf( mean_anom) - ecc);
			/* one correction step,  and we're done */
		err = curr - ecc * sinf( curr) - mean_anom;
		curr -= err / (1. - ecc * cosf( curr));
	} else {
	    curr = mean_anom;
	}

	if( mean_anom < 0.) {
		mean_anom = -mean_anom;
		curr = - curr;
		is_negative = 1;
	}

	thresh = THRESH * fabsf( 1. - ecc);
	if( ecc > .8 && mean_anom < PI / 3. || ecc > 1.)    /* up to 60 degrees */ {
		float trial = mean_anom / fabsf( 1. - ecc);

		if( trial * trial > 6. * fabsf(1. - ecc))   /* cubic term is dominant */ {
			if( mean_anom < PI) {
				trial = CUBE_ROOT( 6. * mean_anom);
			} else {      /* hyperbolic w/ 5th & higher-order terms predominant */
				trial = asinhf( mean_anom / ecc);
			}
		}
		curr = trial;
	}

	if( ecc < 1.) {
		err = curr - ecc * sinf( curr) - mean_anom;
		while( fabsf( err) > thresh) {
			n_iter++;
			curr -= err / (1. - ecc * cosf( curr));
			err = curr - ecc * sinf( curr) - mean_anom;
		}
	} else {
		err = ecc * sinhf( curr) - curr - mean_anom;
		while( fabsf( err) > thresh) {
			n_iter++;
			curr -= err / (ecc * coshf( curr) - 1.);
			err = ecc * sinhf( curr) - curr - mean_anom;
		}
	}
	return( is_negative ? -curr : curr);
}
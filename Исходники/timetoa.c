/*
 * general fractional timestamp formatting
 *
 * Many pieces of ntpd require a machine with two's complement
 * representation of signed integers, so we don't go through the whole
 * rigamarole of creating fully portable code here. But we have to stay
 * away from signed integer overflow, as this might cause trouble even
 * with two's complement representation.
 */
const char *
format_time_fraction(
	time_t	secs,
	long	frac,
	int	prec
	)
{
	char *		cp;
	u_int		prec_u;
	u_time		secs_u;
	u_int		u;
	long		fraclimit;
	int		notneg;	/* flag for non-negative value	*/
	ldiv_t		qr;

	DEBUG_REQUIRE(prec != 0);

	LIB_GETBUF(cp);
	secs_u = (u_time)secs;
	
	/* check if we need signed or unsigned mode */
	notneg = (prec < 0);
	prec_u = abs(prec);
	/* fraclimit = (long)pow(10, prec_u); */
	for (fraclimit = 10, u = 1; u < prec_u; u++) {
		DEBUG_INSIST(fraclimit < fraclimit * 10);
		fraclimit *= 10;
	}

	/*
	 * Since conversion to string uses lots of divisions anyway,
	 * there's no big extra penalty for normalisation. We do it for
	 * consistency.
	 */
	if (frac < 0 || frac >= fraclimit) {
		qr = ldiv(frac, fraclimit);
		if (qr.rem < 0) {
			qr.quot--;
			qr.rem += fraclimit;
		}
		secs_u += (time_t)qr.quot;
		frac = qr.rem;
	}

	/* Get the absolute value of the split representation time. */
	notneg = notneg || ((time_t)secs_u >= 0);
	if (!notneg) {
		secs_u = ~secs_u;
		if (0 == frac)
			secs_u++;
		else
			frac = fraclimit - frac;
	}

	/* finally format the data and return the result */
	snprintf(cp, LIB_BUFLENGTH, "%s%" UTIME_FORMAT ".%0*ld",
	    notneg? "" : "-", secs_u, prec_u, frac);
	
	return cp;
}
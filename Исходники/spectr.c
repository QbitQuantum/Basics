static void
bandpass_setup(struct FilterBank *fb,
		double rate,
		double freq,
		double band,
		int    order
		) {

	/* must be an even number for the algorithm below */
	fb->filter_stages = order;

	assert (order > 0 && (order%2) == 0 && order <= MAXORDER);
	assert (band > 0);

	for (uint32_t i = 0; i < fb->filter_stages; ++i) {
		fb->f[i].z[z1] = fb->f[i].z[z2] = 0;
	}

	const double _wc = 2. * M_PI * freq / rate;
	const double _ww = 2. * M_PI * band / rate;

	double wl = _wc - (_ww / 2.);
	double wu = _wc + (_ww / 2.);

	if (wu > M_PI - 1e-9) {
		/* limit band to below nyquist */
		wu = M_PI - 1e-9;
		fprintf(stderr, "spectr.lv2: band f:%9.2fHz (%.2fHz -> %.2fHz) exceeds nysquist (%.0f/2)\n",
				freq, freq-band/2, freq+band/2, rate);
		fprintf(stderr, "spectr.lv2: shifted to f:%.2fHz (%.2fHz -> %.2fHz)\n",
				rate * (wu + wl) *.25 / M_PI,
				rate * wl * .5 / M_PI,
				rate * wu * .5 / M_PI);
	}
	if (wl < 1e-9) {
		/* this is just for completeness, it cannot happen with spectr.lv2 */
		wl = 1e-9;
		fprintf(stderr, "spectr.lv2: band f:%9.2fHz (%.2fHz -> %.2fHz) contains sub-bass frequencies\n",
				freq, freq-band/2, freq+band/2);
		fprintf(stderr, "spectr.lv2: shifted to f:%.2fHz (%.2fHz -> %.2fHz)\n",
				rate * (wu + wl) *.25 / M_PI,
				rate * wl * .5 / M_PI,
				rate * wu * .5 / M_PI);
	}

	wu *= .5; wl *= .5;
	assert (wu > wl);

	const double c_a =      cos (wu + wl) / cos (wu - wl);
	const double c_b = 1. / tan (wu - wl);
	const double w   = 2. * atan (sqrt (tan (wu) * tan(wl)));

	const double c_a2 = c_a * c_a;
	const double c_b2 = c_b * c_b;
	const double ab_2 = 2. * c_a * c_b;

	/* bilinear transform coefficients into z-domain */
	for (uint32_t i = 0; i < fb->filter_stages / 2; ++i) {
		const double omega =  M_PI_2 + (2 * i + 1) * M_PI / (2. * (double)fb->filter_stages);
		complex_t p = cos (omega) +  _I * sin (omega);

		const complex_t c = (1. + p) / (1. - p);
		const complex_t d = 2 * (c_b - 1) * c + 2 * (1 + c_b);
		complex_t v;

		v = (4 * (c_b2 * (c_a2 - 1) + 1)) * c;
		v += 8 * (c_b2 * (c_a2 - 1) - 1);
		v *= c;
		v += 4 * (c_b2 * (c_a2 - 1) + 1);
		v = csqrt (v);

		const complex_t u0 = ab_2 + creal(v * -1.) + ab_2 * creal(c) + _I * (cimag(v * -1.) + ab_2 * cimag(c));
		const complex_t u1 = ab_2 + creal( v) + ab_2 * creal(c) + _I * (cimag( v) + ab_2 * cimag(c));

#define ASSIGN_BP(FLT, PC, odd) \
	{ \
		const complex_t P = PC; \
		(FLT).W[a0] = 1.; \
		(FLT).W[a1] = -2 * creal(P); \
		(FLT).W[a2] = creal(P) * creal(P) + cimag(P) * cimag(P); \
		(FLT).W[b0] = 1.; \
		(FLT).W[b1] = (odd) ? -2. : 2.; \
		(FLT).W[b2] = 1.; \
	}
		ASSIGN_BP(fb->f[2*i],   u0/d, 0);
		ASSIGN_BP(fb->f[2*i+1], u1/d, 1);
#undef ASSIGN_BP
	}

	/* normalize */
	const double cos_w = cos (-w);
	const double sin_w = sin (-w);
	const double cos_w2 = cos (-2. * w);
	const double sin_w2 = sin (-2. * w);
	complex_t ch = 1;
	complex_t cb = 1;
	for (uint32_t i = 0; i < fb->filter_stages; ++i) {
		ch *= ((1 + fb->f[i].W[b1] * cos_w) + cos_w2)
			  + _I * ((fb->f[i].W[b1] * sin_w) + sin_w2);
		cb *= ((1 + fb->f[i].W[a1] * cos_w) + fb->f[i].W[a2] * cos_w2)
			  + _I * ((fb->f[i].W[a1] * sin_w) + fb->f[i].W[a2] * sin_w2);
	}

	const complex_t scale = cb / ch;
	fb->f[0].W[b0] *= creal(scale);
	fb->f[0].W[b1] *= creal(scale);
	fb->f[0].W[b2] *= creal(scale);

#ifdef DEBUG_SPECTR
	printf("SCALE (%g,  %g)\n", creal(scale), cimag(scale));
	for (uint32_t i = 0; i < fb->filter_stages; ++i) {
		struct Filter *flt = &fb->f[i];
		printf("%d: %g %g %g  %+g %+g %+g\n", i,
				flt->W[a0], flt->W[a1], flt->W[a2],
				flt->W[b0], flt->W[b1], flt->W[b2]);
	}
#endif
}
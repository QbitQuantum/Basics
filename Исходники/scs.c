static pfloat fastCalcPrimalResid(Data * d, Work * w, pfloat * nmAxs) {
	idxint i, n = d->n, m = d->m;
	pfloat pres = 0, scale, *pr = w->pr, *D = w->D, tau = ABS(w->u[n + m]);
	*nmAxs = 0;
	memcpy(pr, &(w->u[n]), m * sizeof(pfloat)); /* overwrite pr */
	addScaledArray(pr, &(w->u_prev[n]), m, d->ALPHA - 2);
	addScaledArray(pr, &(w->u_t[n]), m, 1 - d->ALPHA);
	addScaledArray(pr, d->b, m, w->u_t[n + m]); /* pr = Ax + s */
	for (i = 0; i < m; ++i) {
		scale = d->NORMALIZE ? D[i] / (w->sc_b * d->SCALE) : 1;
		scale = scale * scale;
		*nmAxs += (pr[i] * pr[i]) * scale;
		pres += (pr[i] - d->b[i] * tau) * (pr[i] - d->b[i] * tau) * scale;
	}
	*nmAxs = SQRTF(*nmAxs);
	return SQRTF(pres); /* norm(Ax + s - b * tau) */
}
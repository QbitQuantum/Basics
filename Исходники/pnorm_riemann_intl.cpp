double pnorm_riemann_intl(const double x, const double dx) {
    double pnorm_v = 0.0;
    double dn = 0.0;
    #pragma omp parallel for reduction(+:pnorm_v)
    for (int i = 0; i < (int) (x/dx); i++) {
	dn = i * dx;
	pnorm_v += exp(-0.5 * pow(dn, 2.0));
    }
    pnorm_v = dx * pnorm_v / (sqrt(2.0) * tgamma(0.5)) + 0.5; 
    return pnorm_v; 
}
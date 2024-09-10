double pnorm_taylor_expn(const double x,
			 const int N) {
    double pnorm_v = 0.0;
    #pragma omp parallel for reduction(+:pnorm_v)
    for (int n = 0; n < N; n++) {
	pnorm_v += pow(-0.5, n) * pow(x, 2*n+1) / (tgamma(n+1) * (2*n+1));
    }
    pnorm_v = pnorm_v / (sqrt(2.0) * tgamma(0.5)) + 0.5;
    return pnorm_v;
}
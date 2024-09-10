	double operator()(const double time, const Vect3d& r) {
		const double x = r[0];
		const double alpha = 1.0;
		const double beta = sqrt(alpha/D);
		const double exact = (mu/(D*beta)) * (
				exp(-beta*(1.0-x))
				- 0.5*exp(-beta*(1.0-x))*erfc((2.0*beta*D*time-(1.0-x))/sqrt(4.0*D*time))
				- 0.5*exp(beta*(1.0-x))*erfc((2.0*beta*D*time+(1.0-x))/sqrt(4.0*D*time))
		);

		return exact;
	}
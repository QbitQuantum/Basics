double z_time_from_redshiftinterval_flatuniverse(double h, double omega_m, double omega_l, double zmin, double zmax)
{
	double prefactor = 2./(3*h*100.*km_cm/Mpc_cm*sqrt(omega_l));
	double tmp = sqrt(omega_l/omega_m);
	
	return prefactor*(asinh(tmp*pow(1.+zmin, -1.5)) - asinh(tmp*pow(1.+zmax, -1.5)));
}
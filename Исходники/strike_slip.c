/*** contributions from the mirror image H0 ***/
static double
strikexH0 (MagComp component, const fault_params *fault, const magnetic_params *mag, double xi, double et, double qq, double y, double z)
{
	double val;
	double h = mag->dcurier;
	double qd = y * sd + (fault->fdepth - h) * cd;
	double K1_val = K1 (component, 1.0, xi, et, qq);
	double atan_xe_qr_val = atan_xe_qr (component, 1.0, xi, et, qq);
	double J1_val = J1 (component, 1.0, xi, et, qq);
	double M1_val = M1 (component, 1.0, xi, et, qq);
	double L1_val = L1 (component, 1.0, xi, et, qq);
	double M1y_val = M1y (component, 1.0, xi, et, qq);
	double M1z_val = M1z (component, 1.0, xi, et, qq);

	val = - (2.0 - alpha4) * K1_val
		- alpha1 * atan_xe_qr_val - alpha3 * J1_val
		- alpha3 * (qd * M1_val + (z - h) * L1_val * sd)
		- 2.0 * alpha4 * h * (M1_val * cd - L1_val * sd)
		- 4.0 * alpha1 * h * L1_val * sd
		+ 2.0 * alpha2 * h * ((qd + h * cd) * M1z_val - (z - 2.0 * h) * M1y_val * sd);

	return val;
}
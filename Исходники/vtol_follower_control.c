/**
 * Calculate the "cubic deadband" system parameters.
 * @param[in] The width of the deadband
 * @param[in] Slope of deadband at in=0, sane values between 0 and 1.
 * @param[out] m cubic weighting of function
 * @param[out] integrated response at in=w
 */
static void vtol_deadband_setup(float w, float b, float *m, float *r)
{
	/* So basically.. we want the function to be tangent to the
	** linear sections-- have a slope of 1-- at -w and w.  In the
	** middle we want a slope of b.   So the cube here does all the
	** work b isn't doing. */
	*m = cbrtf((1-b)/(3*powf(w,2)));

	*r = powf(*m*w, 3)+b*w;
}
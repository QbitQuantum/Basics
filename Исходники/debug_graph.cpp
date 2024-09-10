double t_to_e_AstronomyAnswers(double nu)
{
	double e = 2.0;
	if (e < 1.0)
	{
		return 2.0 * atan(tan(nu / 2.0) / sqrt((1.0 + e) / (1.0 - e)));
	}
	else if (e == 1.0)
	{
		return 0;
	}
	else
	{
		return 2.0 * atanh(tan(nu / 2.0) / sqrt((e + 1.0) / (e - 1.0)));
	}
}
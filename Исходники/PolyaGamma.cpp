double PolyaGamma::jj_m1(double b, double z) 
{
    z = fabs(z);
    double m1 = 0.0;
    if (z > 1e-12)
	m1 = b * tanh(z) / z;
    else
	m1 = b * (1 - (1.0/3) * pow(z,2) + (2.0/15) * pow(z,4) - (17.0/315) * pow(z,6));
    return m1;
}
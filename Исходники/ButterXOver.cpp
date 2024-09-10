void CButterXOver::settype(float t)
{
	const float amt = 4.f;
	const float tmp = 0.5f*amt;
	t = 0.5f*tanhf(amt*t - tmp)/tanhf(tmp) + 0.5f; //some empirical ch00ning
	float a = (float)cos(t*3.141592*0.5)*0.7f;
	float b = (float)sin(t*3.141592*0.5)*0.7f;
	m2 = (a - b)*0.5f;
	m1 = (a + b)*0.5f;
}
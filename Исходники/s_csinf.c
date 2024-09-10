static void
cchshf(float xx, float *c, float *s)
{
	float x, e, ei;

	x = xx;
	if(fabsf(x) <= 0.5f) {
		*c = coshf(x);
		*s = sinhf(x);
	}
	else {
		e = expf(x);
		ei = 0.5f/e;
		e = 0.5f * e;
		*s = e - ei;
		*c = e + ei;
	}
}
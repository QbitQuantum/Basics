static float nearest_neighbor_interpolation_at(float *x,
        int w, int h, float p, float q)
{
	int ip = rintf(p);
	int iq = rintf(q);
	float r = getpixel_1(x, w, h, ip, iq);
    if (r < -1000) return NAN;
	return r;
}
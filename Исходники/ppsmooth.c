// evaluate an image at a sub-pixel position, using bilinear interpolation
static float bilinear_interpolation(float *x, int w, int h, float p, float q)
{
	int ip = p;
	int iq = q;
	float a = getpixel(x, w, h, ip  , iq  );
	float b = getpixel(x, w, h, ip+1, iq  );
	float c = getpixel(x, w, h, ip  , iq+1);
	float d = getpixel(x, w, h, ip+1, iq+1);
	float r = evaluate_bilinear_cell(a, b, c, d, p-ip, q-iq);
	return r;
}
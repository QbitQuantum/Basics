void
compute_gradient(float **src, int w, int h, float **g_mag, float **g_ang)
{
	// Sobel mask values
	const float mx0[] = {-0.25f, 0.f, 0.25f};
	const float mx1[] = {-0.5f , 0.f, 0.5f };
	const float mx2[] = {-0.25f, 0.f, 0.25f};
	const float *mx[] = {mx0, mx1, mx2};
	const float my0[] = {-0.25f,-0.5f,-0.25f};
	const float my1[] = { 0.f  , 0.f , 0.f  };
	const float my2[] = { 0.25f, 0.5f, 0.25f};
	const float *my[] = {my0, my1, my2};

	int y, x, i, j, r, c;
#pragma omp parallel for private(x)
	for (y = 0; y < h; y++)
	#pragma omp parallel for private(i, j, r, c)
	for (x = 0; x < w; x++)
	{
		float gx = 0.f, gy = 0.f;
		for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
		{
			r = y+i-1; if(r<0)r=0; else if(r>=h)r=h-1;
			c = x+j-1; if(c<0)c=0; else if(c>=w)c=w-1;
			
			gx += src[r][c] * mx[i][j];
			gy += src[r][c] * my[i][j];
		}
		g_mag[y][x] = hypotf(gy, gx);
		g_ang[y][x] = atan2f(gy, gx);
	}
}
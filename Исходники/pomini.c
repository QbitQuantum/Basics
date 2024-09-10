static float laplacian(float *x, int w, int h, int i, int j)
{
	return  -4 * getpixel(x, w, h, i  , j  )
		     + getpixel(x, w, h, i+1, j  )
		     + getpixel(x, w, h, i  , j+1)
		     + getpixel(x, w, h, i-1, j  )
		     + getpixel(x, w, h, i  , j-1);
}
inline __m128 _mm_cosf(__m128 x)
{
	float X[4];
	_mm_store_ps(X,x);
	X[0] = cosf(X[0]);
	X[1] = cosf(X[1]);
	X[2] = cosf(X[2]);
	X[3] = cosf(X[3]);
	return _mm_load_ps(X);
}
void CAllPassFilterPair::processBlock(double* data, int numSamples)
{
	jassert((((size_t) data) & 0xF) == 0);
	jassert((_mm_getcsr() & 0x8040) == 0x8040);

	__m128d coeff = _mm_load_pd(md.getPtr(0));
	__m128d x1 = _mm_load_pd(md.getPtr(1));
	__m128d x2 = _mm_load_pd(md.getPtr(2));
	__m128d y1 = _mm_load_pd(md.getPtr(3));
	__m128d y2 = _mm_load_pd(md.getPtr(4));

	for (int i=0; i<numSamples; ++i)
	{
		__m128d x0 = _mm_load_pd(&(data[i+i]));
		__m128d tmp = _mm_sub_pd(x0, y2);
		tmp = _mm_mul_pd(tmp, coeff);
		__m128d y0 = _mm_add_pd(x2, tmp);

		_mm_store_pd(&(data[i+i]), y0);

		x2=x1;
		x1=x0;

		y2=y1;
		y1=y0;
	}

	_mm_store_pd(md.getPtr(1), x1);
	_mm_store_pd(md.getPtr(2), x2);
	_mm_store_pd(md.getPtr(3), y1);
	_mm_store_pd(md.getPtr(4), y2);

};
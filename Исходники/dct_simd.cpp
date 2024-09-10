void fDCT2D8x4_and_threshold_keep00_32f(const float* x, float* y, float thresh)
{
	const int __declspec(align(16)) v32f_absmask[] = { 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff };
	const __m128 mth = _mm_set1_ps(thresh);
	const __m128 zeros = _mm_setzero_ps();

	__m128 c0 = _mm_load_ps(x);
	__m128 c1 = _mm_load_ps(x + 56);
	__m128 t0 = _mm_add_ps(c0, c1);
	__m128 t7 = _mm_sub_ps(c0, c1);

	c1 = _mm_load_ps(x + 48);
	c0 = _mm_load_ps(x + 8);
	__m128 t1 = _mm_add_ps(c0, c1);
	__m128 t6 = _mm_sub_ps(c0, c1);

	c1 = _mm_load_ps(x + 40);
	c0 = _mm_load_ps(x + 16);
	__m128 t2 = _mm_add_ps(c0, c1);
	__m128 t5 = _mm_sub_ps(c0, c1);

	c0 = _mm_load_ps(x + 24);
	c1 = _mm_load_ps(x + 32);
	__m128 t3 = _mm_add_ps(c0, c1);
	__m128 t4 = _mm_sub_ps(c0, c1);

	/*
	c1 = x[0]; c2 = x[7]; t0 = c1 + c2; t7 = c1 - c2;
	c1 = x[1]; c2 = x[6]; t1 = c1 + c2; t6 = c1 - c2;
	c1 = x[2]; c2 = x[5]; t2 = c1 + c2; t5 = c1 - c2;
	c1 = x[3]; c2 = x[4]; t3 = c1 + c2; t4 = c1 - c2;
	*/

	c0 = _mm_add_ps(t0, t3);
	__m128 c3 = _mm_sub_ps(t0, t3);
	c1 = _mm_add_ps(t1, t2);
	__m128 c2 = _mm_sub_ps(t1, t2);

	/*
	c0 = t0 + t3; c3 = t0 - t3;
	c1 = t1 + t2; c2 = t1 - t2;
	*/

	const __m128 invsqrt2h = _mm_set_ps1(0.353554f);

	__m128 v = _mm_mul_ps(_mm_add_ps(c0, c1), invsqrt2h);
	__m128 msk = _mm_cmpgt_ps(_mm_and_ps(v, *(const __m128*)v32f_absmask), mth);
	// keep 00 coef.
	__m128 v2 = _mm_blendv_ps(zeros, v, msk);
	v2 = _mm_blend_ps(v2, v, 1);
	_mm_store_ps(y, v2);

	v = _mm_mul_ps(_mm_sub_ps(c0, c1), invsqrt2h);
	msk = _mm_cmpgt_ps(_mm_and_ps(v, *(const __m128*)v32f_absmask), mth);
	v = _mm_blendv_ps(zeros, v, msk);
	_mm_store_ps(y + 32, v);

	/*y[0] = c0 + c1;
	y[4] = c0 - c1;*/

	__m128 w0 = _mm_set_ps1(0.541196f);
	__m128 w1 = _mm_set_ps1(1.306563f);
	v = _mm_mul_ps(_mm_add_ps(_mm_mul_ps(w0, c2), _mm_mul_ps(w1, c3)), invsqrt2h);
	msk = _mm_cmpgt_ps(_mm_and_ps(v, *(const __m128*)v32f_absmask), mth);
	v = _mm_blendv_ps(zeros, v, msk);
	_mm_store_ps(y + 16, v);

	v = _mm_mul_ps(_mm_sub_ps(_mm_mul_ps(w0, c3), _mm_mul_ps(w1, c2)), invsqrt2h);
	msk = _mm_cmpgt_ps(_mm_and_ps(v, *(const __m128*)v32f_absmask), mth);
	v = _mm_blendv_ps(zeros, v, msk);
	_mm_store_ps(y + 48, v);
	/*
	y[2] = c2 * r[6] + c3 * r[2];
	y[6] = c3 * r[6] - c2 * r[2];
	*/

	w0 = _mm_set_ps1(1.175876f);
	w1 = _mm_set_ps1(0.785695f);
	c3 = _mm_add_ps(_mm_mul_ps(w0, t4), _mm_mul_ps(w1, t7));
	c0 = _mm_sub_ps(_mm_mul_ps(w0, t7), _mm_mul_ps(w1, t4));
	/*
	c3 = t4 * r[3] + t7 * r[5];
	c0 = t7 * r[3] - t4 * r[5];
	*/

	w0 = _mm_set_ps1(1.387040f);
	w1 = _mm_set_ps1(0.275899f);
	c2 = _mm_add_ps(_mm_mul_ps(w0, t5), _mm_mul_ps(w1, t6));
	c1 = _mm_sub_ps(_mm_mul_ps(w0, t6), _mm_mul_ps(w1, t5));
	/*
	c2 = t5 * r[1] + t6 * r[7];
	c1 = t6 * r[1] - t5 * r[7];
	*/

	v = _mm_mul_ps(_mm_sub_ps(c0, c2), invsqrt2h);
	msk = _mm_cmpgt_ps(_mm_and_ps(v, *(const __m128*)v32f_absmask), mth);
	v = _mm_blendv_ps(zeros, v, msk);

	_mm_store_ps(y + 24, v);

	v = _mm_mul_ps(_mm_sub_ps(c3, c1), invsqrt2h);
	msk = _mm_cmpgt_ps(_mm_and_ps(v, *(const __m128*)v32f_absmask), mth);
	v = _mm_blendv_ps(zeros, v, msk);
	_mm_store_ps(y + 40, v);
	//y[5] = c3 - c1; y[3] = c0 - c2;

	const __m128 invsqrt2 = _mm_set_ps1(0.707107f);
	c0 = _mm_mul_ps(_mm_add_ps(c0, c2), invsqrt2);
	c3 = _mm_mul_ps(_mm_add_ps(c3, c1), invsqrt2);
	//c0 = (c0 + c2) * invsqrt2;
	//c3 = (c3 + c1) * invsqrt2;

	v = _mm_mul_ps(_mm_add_ps(c0, c3), invsqrt2h);
	msk = _mm_cmpgt_ps(_mm_and_ps(v, *(const __m128*)v32f_absmask), mth);
	v = _mm_blendv_ps(zeros, v, msk);
	_mm_store_ps(y + 8, v);

	v = _mm_mul_ps(_mm_sub_ps(c0, c3), invsqrt2h);
	msk = _mm_cmpgt_ps(_mm_and_ps(v, *(const __m128*)v32f_absmask), mth);
	v = _mm_blendv_ps(zeros, v, msk);

	_mm_store_ps(y + 56, v);
	//y[1] = c0 + c3; y[7] = c0 - c3;

	/*for(i = 0;i < 8;i++)
	{
	y[i] *= invsqrt2h;
	}*/
}
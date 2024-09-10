//same thing, but processes 4 pixels simultaneously using SSE2 intrinsics
//probably can be made faster, but I'm no expert at low level code :)
void mandelbrotKernelSSE2(__m128 re, __m128 im, unsigned char *out_color)
{
	const __m128 escape = _mm_set_ps(9.0f, 9.0f, 9.0f, 9.0f);
	__m128i iter_inc = _mm_set_epi32(1, 1, 1, 1);

	__m128 z_re = _mm_set_ps(0.0f, 0.0f, 0.0f, 0.0f);
	__m128 z_im = _mm_set_ps(0.0f, 0.0f, 0.0f, 0.0f);
	__m128 z_re2 = _mm_set_ps(0.0f, 0.0f, 0.0f, 0.0f);
	__m128 z_im2 = _mm_set_ps(0.0f, 0.0f, 0.0f, 0.0f);
	__m128i iter_mask = _mm_set_epi32(0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff);
	__m128i iter = _mm_set_epi32(0, 0, 0, 0);
	int i = 0;
	int iter_mask_v[4];
	for(i=0; i < 32; i++)
	{
		z_im = _mm_mul_ps(z_re, z_im);
		z_im = _mm_add_ps(z_im, z_im);
		z_im = _mm_add_ps(z_im, im);
		z_re = _mm_sub_ps(z_re2, z_im2);
		z_re = _mm_add_ps(z_re, re);
		z_re2 = _mm_mul_ps(z_re, z_re);
		z_im2 = _mm_mul_ps(z_im, z_im);
		__m128 iter_mask_new=_mm_cmplt_ps(_mm_add_ps(z_re2, z_im2), escape);
		iter_mask = _mm_castps_si128(_mm_and_ps(_mm_castsi128_ps(iter_mask), iter_mask_new));
		iter_inc = _mm_castps_si128(_mm_and_ps(_mm_castsi128_ps(iter_inc), _mm_castsi128_ps(iter_mask)));
		iter = _mm_add_epi32(iter, iter_inc);
        //not sure if it really speeds up the code, we are doing conditional based on
        //SSE2 register, probably there's much better way to do it
		_mm_storeu_ps((float*)iter_mask_v, _mm_castsi128_ps(iter_mask));
		if(!(iter_mask_v[0] || iter_mask_v[1] || iter_mask_v[2] || iter_mask_v[3]))
		{
			break;
		}
	}
	int iters[4];
	_mm_storeu_ps((float*)iters, _mm_castsi128_ps(iter));
	for(i=0;i<4;i++)
	{
		unsigned char col = (iters[3 - i] == 32) ? 255 : (iters[3 - i] * 8);
		*out_color ++= col;
		*out_color ++= col;
		*out_color ++= col;
		*out_color ++= 255;
	}
}
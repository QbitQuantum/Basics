void
M_MatrixRotateAxis44_SSE(M_Matrix44 *M, M_Real theta, M_Vector3 A)
{
	float s = sinf((float)theta);
	float c = cosf((float)theta);
	float t = 1.0f - c;
	M_Matrix44 R;
	__m128 a = A.m128, r1;
#ifdef HAVE_SSE3
	__m128 rC1 = _mm_set_ps(-c,    s*A.z, 0.0f,  +c);	/* 1,3 1,2 3 2 */
	__m128 rC2 = _mm_set_ps(0.0f, -s*A.y, s*A.y, -s*A.x);	/* 1,2 3 1 2,3 */
#endif
	
	/* m1: [t*AxAx + c,    t*AxAy + sAz,    t*AxAz - sAy,    0] */
	r1 = _mm_mul_ps(_mm_set1_ps(t), a);
	r1 = _mm_mul_ps(r1, _mm_shuffle_ps(a,a,_MM_SHUFFLE(0,0,0,0)));
#ifdef HAVE_SSE3
	R.m1 = _mm_addsub_ps(r1, _mm_shuffle_ps(rC1,rC2,_MM_SHUFFLE(3,1,2,3)));
#else
	R.m1 = _mm_add_ps(r1, _mm_set_ps(0.0f, -s*A.y, s*A.z, c));
#endif

	/* m2: [t*AxAy - sAz,    t*AyAy + c,    t*AyAz + sAx,    0] */
	r1 = _mm_mul_ps(_mm_set1_ps(t), _mm_shuffle_ps(a,a,_MM_SHUFFLE(3,1,1,0)));
	r1 = _mm_mul_ps(r1, _mm_shuffle_ps(a,a,_MM_SHUFFLE(3,2,1,1)));
#ifdef HAVE_SSE3
	R.m2 = _mm_addsub_ps(r1, _mm_shuffle_ps(rC1,rC2,_MM_SHUFFLE(3,0,0,2)));
#else
	R.m2 = _mm_add_ps(r1, _mm_set_ps(0.0f, +s*A.x, c, -s*A.z));
#endif

	/* m3: [t*AxAz + sAy,    t*AyAz - sAx,    t*AzAz + c,    0] */
	r1 = _mm_mul_ps(_mm_set1_ps(t), a);
	r1 = _mm_mul_ps(r1, _mm_shuffle_ps(a,a,_MM_SHUFFLE(0,2,2,2)));
#ifdef HAVE_SSE3
	R.m3 = _mm_addsub_ps(r1, _mm_shuffle_ps(rC2,rC1,_MM_SHUFFLE(1,3,0,2)));
#else
	R.m3 = _mm_add_ps(r1, _mm_set_ps(0.0f, c, -s*A.x, +s*A.y));
#endif
	/* m4: [0,    0,    0,    1] */
	R.m4 = _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f);

	M_MatrixMult44v_SSE(M, &R);
}
// --------------------------------------------------------------
vuint32 mandelbrot_simd(vfloat32 a, vfloat32 b, size_t max_iter)
// --------------------------------------------------------------
{
	vuint32 num_iter = _mm_set1_epi32(0);
	vfloat32 zero=_mm_set1_ps(0);
    vfloat32 one=_mm_set1_ps(1);
	vfloat32 two=_mm_set1_ps(2);
	vfloat32 x=_mm_setzero_ps();
	vfloat32 y=_mm_setzero_ps();
	vfloat32 tmp;
	vfloat32 z;
	for(int i=0;i<max_iter;i++){	
	tmp=x;
	x=_mm_add_ps(a,_mm_sub_ps(_mm_mul_ps(x,x),_mm_mul_ps(y,y)));
	y=_mm_add_ps(b,_mm_mul_ps(_mm_mul_ps(y,tmp),two));	
	z=_mm_sqrt_ps(_mm_add_ps(_mm_mul_ps(x,x),_mm_mul_ps(y,y)));
	num_iter=_mm_add_epi32(num_iter,_mm_cvtps_epi32(_mm_and_ps(_mm_cmplt_ps(z,two),one)));
    }
	return num_iter;
}
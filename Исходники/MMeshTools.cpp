static void blendMatrices(MMatrix4x4 * matrix, const MMatrix4x4 * skinMatrix, const float weight)
{
	__m128 w = _mm_set1_ps(weight);
				
	for(int i=0; i<16; i+=4)
	{
		__m128 a = _mm_loadu_ps(matrix->entries + i);
		__m128 b = _mm_loadu_ps(skinMatrix->entries + i);
		__m128 c = _mm_mul_ps(b, w);
		__m128 d = _mm_add_ps(a, c);
		_mm_storeu_ps(matrix->entries + i, d);
	}
}
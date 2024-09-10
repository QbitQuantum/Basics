void somap::train(const imgdata & obj)
{
	if (this->weight <= 0.0)return;
	__m256 tmp;
	__m256 *v1 = (__m256*)(this->fvex);
	const __m256 *v2 = (__m256*)(obj.fvex);
	const __m256 ws = _mm256_set1_ps(this->weight);
	for (int i = 0; i < f; i++) {
		tmp = _mm256_sub_ps(v2[i], v1[i]);
		tmp = _mm256_mul_ps(tmp, ws);
		v1[i] = _mm256_add_ps(v1[i], tmp);
	}
}
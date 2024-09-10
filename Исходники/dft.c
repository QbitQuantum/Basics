void m16_256(int16_t *x, int16_t *y, int16_t *z, int N){
	__m256i *x256, *y256, *z256;
	x256 = (__m256i *)x;
	y256 = (__m256i *)y;
	z256 = (__m256i *)z;
	int i;
	for(i=0; i<(N>>3); i++){
		z256[i] = _mm256_mulhi_epi16(x256[i], y256[i]);
	}
	
}
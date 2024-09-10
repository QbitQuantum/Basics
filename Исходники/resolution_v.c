// Résolution de matrices vectorisées inférieures
void resolutionInf (mat M, vectf B, vectf Res) {
	int i, j;
	int somme;

	__m128 v1, v2, v3, v4, v5; 

	for(i=0; i<N; i++) {
		somme = 0;
		for(j=0; j<i; j+=4) {
			v1 = _mm_load_ps (M[i]+j) ;
			v2 = _mm_load_ps (B+j) ;
			v3 = _mm_load_ps(Res+j);
      v4 = _mm_mul_ps(v1,v3);

			v5 = _mm_dp_ps(v4,v2, 0xFF);

			somme += v5[0];
		}

		Res[i] = (B[i]-somme) / M[i][i];
	}
}
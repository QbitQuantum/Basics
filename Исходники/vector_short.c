float	vector_cos_short (const short* pa,const short* pb,size_t n)
{
    size_t k;
    double norm;
    size_t q = n / 16;
    size_t r = n % 16;
    int ps,na,nb;
    if (q > 0) {
        __m128i acc;
	__m128i acc_ps1 = _mm_setzero_si128();
	__m128i acc_ps2 = _mm_setzero_si128();
	__m128i acc_na1 = _mm_setzero_si128();
	__m128i acc_na2 = _mm_setzero_si128();
	__m128i acc_nb1 = _mm_setzero_si128();
	__m128i acc_nb2 = _mm_setzero_si128();
	if (ALGEBRA_IS_ALIGNED(pa) && ALGEBRA_IS_ALIGNED(pb)) {
	    for (k=0;k<q;k++) {
		/* Charge 16 mots dans chaque tableau */
		__m128i a1 = _mm_load_si128((__m128i*)pa);
		__m128i b1 = _mm_load_si128((__m128i*)pb);
		__m128i a2 = _mm_load_si128((__m128i*)(pa+8));
		__m128i b2 = _mm_load_si128((__m128i*)(pb+8));
		/* Multiple, somme et converti en double word */
		__m128i ps1 = _mm_madd_epi16(a1,b1);
		__m128i ps2 = _mm_madd_epi16(a2,b2);
		__m128i na1 = _mm_madd_epi16(a1,a1);
		__m128i na2 = _mm_madd_epi16(a2,a2);
		__m128i nb1 = _mm_madd_epi16(b1,b1);
		__m128i nb2 = _mm_madd_epi16(b2,b2);
		pa += 16;
		pb += 16;
		/* Accumule */
		acc_ps1 = _mm_add_epi32(acc_ps1,ps1);
		acc_ps2 = _mm_add_epi32(acc_ps2,ps2);
		acc_na1 = _mm_add_epi32(acc_na1,na1);
		acc_na2 = _mm_add_epi32(acc_na2,na2);
		acc_nb1 = _mm_add_epi32(acc_nb1,nb1);
		acc_nb2 = _mm_add_epi32(acc_nb2,nb2);
	    }
	}
	else {
	    for (k=0;k<q;k++) {
	    }
	}
	/* Somme finale */
	acc = _mm_add_epi32(acc_ps1,acc_ps2);
	acc = _mm_hadd_epi32(acc,acc);
	acc = _mm_hadd_epi32(acc,acc);
	ps = _mm_extract_epi32(acc,0);

	acc = _mm_add_epi32(acc_na1,acc_na2);
	acc = _mm_hadd_epi32(acc,acc);
	acc = _mm_hadd_epi32(acc,acc);
	na = _mm_extract_epi32(acc,0);

	acc = _mm_add_epi32(acc_nb1,acc_nb2);
	acc = _mm_hadd_epi32(acc,acc);
	acc = _mm_hadd_epi32(acc,acc);
	nb = _mm_extract_epi32(acc,0);
    }
    else {
	ps = 0;
	na = 0;
	nb = 0;
    }
    for (k=0;k<r;k++) {
	int a = *pa++;
	int b = *pb++;
	ps += a*b;
	na += a*a;
	nb += b*b;
    }
    norm = sqrt( ((double)na) * ((double)nb) );
    if (norm < 1E-5f)
	return 0;
    return ps / norm;
}
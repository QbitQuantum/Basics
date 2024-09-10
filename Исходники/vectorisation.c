int main (int argc, char **argv)
{

	int i;
	float prod_scalaire_res = 0;

	vectf a ; initVf(a);
	vectf b ; initVf(b);
	vectf c ;

	print_vector_float(a);

	printf("================================================\n");

	print_vector_float(b);

	printf("================================================\n");

	__m128 v1, v2, v3 ;
	__m128i iV1, iV2, iV3 ;

	for(i=0; i<N; i+=4) {
		v1 = _mm_load_ps (a+i) ;
		v2 = _mm_load_ps (b+i) ;
		v3 = _mm_dp_ps (v1, v2, 0xFF) ;
		//_mm_store_ps (c+i, v3) ;
		prod_scalaire_res += v3[0];
	}

	printf("Produit scalaire des deux vecteurs : %f\n", prod_scalaire_res);

	exit (0) ;
}
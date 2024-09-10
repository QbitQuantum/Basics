void go(SGLVData *data, int nbiter){
	int i;
	mpz_t  k_rd, ZZ, tmp;
	mpz_inits (k_rd, ZZ, tmp, NULL);
	
	gmp_randstate_t rand_gen;
	unsigned long seed = time(NULL); 
	gmp_randinit_default(rand_gen);
	gmp_randseed_ui(rand_gen, seed);
	
	
	SGLVScalar k;
	JacPoint jp;
	
	struct timespec start1,start2;
    struct timespec end1,end2;
    uint64_t diff1,diff2, diff3;
	
	
	printf("\nSGLV 256 bits benchmark, running...\n\n");
	
	
	diff1 = 0;
	diff2 = 0;
	
	init_jacPoint(&jp);
	
	
	
	for (i = 0; i < nbiter; i++) {
		
		mpz_urandomb (k_rd, rand_gen, BIT_SIZE);
		mpz_mod (k_rd, k_rd,  data->efp);
		
		
		apply_endo(((data->PP)+1), (data->PP), beta); /* Point PHI_P */
		add_aff_aff(((data->PP)+1), (data->PP));      /* Point P+PHI_P */
		
		
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start1);
		
		init_glvScalar(&k);
		build_glvScalar(&k, k_rd, data->aa, data->bb, data->Na);
		
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end1);
		diff1 += BILLION * (end1.tv_sec - start1.tv_sec) + end1.tv_nsec - start1.tv_nsec; 
		
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start1);
		
		point_from_SGLVScalar(&jp, &k, data->PP);
		
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end1);
		diff2 += BILLION * (end1.tv_sec - start1.tv_sec) + end1.tv_nsec - start1.tv_nsec; 
		
		mpz_invert (ZZ, jp.Z, p);
		mpz_mul (tmp, ZZ, ZZ); // tmp = ZZ^2
		//~ P is transformed in affine coordinates for next iteration
		mpz_mul (data->PP[0].X, jp.X, tmp);
		mpz_mod (data->PP[0].X, data->PP[0].X, p);
		
		mpz_mul (data->PP[0].Y, jp.Y, tmp);
		mpz_mul (data->PP[0].Y, data->PP[0].Y, ZZ);
		mpz_mod (data->PP[0].Y, data->PP[0].Y, p);
	}
	diff3 = diff1 + diff2;
	
	
	if (is_on_curve_jac(&jp, ca, cb)){ 
		printf("\nMULT: kP OK\n");
		print_jacPoint(&jp);
		printf("Elapsed time = %llu %llu %llu nanoseconds\n", (long long unsigned int) diff1, (long long unsigned int) diff2, (long long unsigned int) diff3);
	}
	else
		printf("MULT: kP non OK\n");
	
	
	mpz_clears (k_rd, ZZ, tmp, NULL);
	free_jacPoint(&jp);
	gmp_randclear(rand_gen);
}
/*------------------------------------------------------------------*/
void relation_batch_init(msieve_obj *obj, relation_batch_t *rb,
			uint32 min_prime, uint32 max_prime,
			uint32 lp_cutoff_r, uint32 lp_cutoff_a, 
			savefile_t *savefile,
			print_relation_t print_relation) {

	prime_sieve_t sieve;
	uint32 num_primes, p;

	/* count the number of primes to multiply. Knowing this
	   in advance makes the recursion a lot easier, at the cost
	   of a small penalty in runtime */

	init_prime_sieve(&sieve, min_prime + 1, max_prime);
	p = min_prime;
	num_primes = 0;
	while (p < max_prime) {
		p = get_next_prime(&sieve);
		num_primes++;
	}
	free_prime_sieve(&sieve);

	/* compute the product of primes */

	logprintf(obj, "multiplying %u primes from %u to %u\n",
			num_primes, min_prime, max_prime);

	init_prime_sieve(&sieve, min_prime, max_prime);
	mpz_init(rb->prime_product);
	multiply_primes(0, num_primes - 2, &sieve, rb->prime_product);
	logprintf(obj, "multiply complete, product has %u bits\n", 
				(uint32)mpz_sizeinbase(rb->prime_product, 2));
					
	rb->savefile = savefile;
	rb->print_relation = print_relation;

	/* compute the cutoffs used by the recursion base-case. Large
	   primes have a maximum size specified as input arguments, 
	   but numbers that can be passed to the SQUFOF routine are
	   limited to size 2^62 */

	rb->lp_cutoff_r = lp_cutoff_r;
	lp_cutoff_r = MIN(lp_cutoff_r, 0x7fffffff);
	mp_clear(&rb->lp_cutoff_r2);
	rb->lp_cutoff_r2.nwords = 1;
	rb->lp_cutoff_r2.val[0] = lp_cutoff_r;
	mp_mul_1(&rb->lp_cutoff_r2, lp_cutoff_r, &rb->lp_cutoff_r2);

	rb->lp_cutoff_a = lp_cutoff_a;
	lp_cutoff_a = MIN(lp_cutoff_a, 0x7fffffff);
	mp_clear(&rb->lp_cutoff_a2);
	rb->lp_cutoff_a2.nwords = 1;
	rb->lp_cutoff_a2.val[0] = lp_cutoff_a;
	mp_mul_1(&rb->lp_cutoff_a2, lp_cutoff_a, &rb->lp_cutoff_a2);

	mp_clear(&rb->max_prime2);
	rb->max_prime2.nwords = 1;
	rb->max_prime2.val[0] = max_prime;
	mp_mul_1(&rb->max_prime2, max_prime, &rb->max_prime2);

	/* allocate lists for relations and their factors */

	rb->target_relations = 500000;
	rb->num_relations = 0;
	rb->num_relations_alloc = 1000;
	rb->relations = (cofactor_t *)xmalloc(rb->num_relations_alloc *
						sizeof(cofactor_t));

	rb->num_factors = 0;
	rb->num_factors_alloc = 10000;
	rb->factors = (uint32 *)xmalloc(rb->num_factors_alloc *
						sizeof(uint32));
}
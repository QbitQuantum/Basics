mp_err mpp_make_prime(mp_int *start, mp_size nBits, mp_size strong,
		      unsigned long * nTries)
{
  mp_digit      np;
  mp_err        res;
  int           i	= 0;
  mp_int        trial;
  mp_int        q;
  mp_size       num_tests;
  unsigned char *sieve;
  
  ARGCHK(start != 0, MP_BADARG);
  ARGCHK(nBits > 16, MP_RANGE);

  sieve = malloc(SIEVE_SIZE);
  ARGCHK(sieve != NULL, MP_MEM);

  MP_DIGITS(&trial) = 0;
  MP_DIGITS(&q) = 0;
  MP_CHECKOK( mp_init(&trial) );
  MP_CHECKOK( mp_init(&q)     );
  /* values taken from table 4.4, HandBook of Applied Cryptography */
  if (nBits >= 1300) {
    num_tests = 2;
  } else if (nBits >= 850) {
    num_tests = 3;
  } else if (nBits >= 650) {
    num_tests = 4;
  } else if (nBits >= 550) {
    num_tests = 5;
  } else if (nBits >= 450) {
    num_tests = 6;
  } else if (nBits >= 400) {
    num_tests = 7;
  } else if (nBits >= 350) {
    num_tests = 8;
  } else if (nBits >= 300) {
    num_tests = 9;
  } else if (nBits >= 250) {
    num_tests = 12;
  } else if (nBits >= 200) {
    num_tests = 15;
  } else if (nBits >= 150) {
    num_tests = 18;
  } else if (nBits >= 100) {
    num_tests = 27;
  } else
    num_tests = 50;

  if (strong) 
    --nBits;
  MP_CHECKOK( mpl_set_bit(start, nBits - 1, 1) );
  MP_CHECKOK( mpl_set_bit(start,         0, 1) );
  for (i = mpl_significant_bits(start) - 1; i >= nBits; --i) {
    MP_CHECKOK( mpl_set_bit(start, i, 0) );
  }
  /* start sieveing with prime value of 3. */
  MP_CHECKOK(mpp_sieve(start, prime_tab + 1, prime_tab_size - 1, 
		       sieve, SIEVE_SIZE) );

#ifdef DEBUG_SIEVE
  res = 0;
  for (i = 0; i < SIEVE_SIZE; ++i) {
    if (!sieve[i])
      ++res;
  }
  fprintf(stderr,"sieve found %d potential primes.\n", res);
#define FPUTC(x,y) fputc(x,y)
#else
#define FPUTC(x,y) 
#endif

  res = MP_NO;
  for(i = 0; i < SIEVE_SIZE; ++i) {
    if (sieve[i])	/* this number is composite */
      continue;
    MP_CHECKOK( mp_add_d(start, 2 * i, &trial) );
    FPUTC('.', stderr);
    /* run a Fermat test */
    res = mpp_fermat(&trial, 2);
    if (res != MP_OKAY) {
      if (res == MP_NO)
	continue;	/* was composite */
      goto CLEANUP;
    }
      
    FPUTC('+', stderr);
    /* If that passed, run some Miller-Rabin tests	*/
    res = mpp_pprime(&trial, num_tests);
    if (res != MP_OKAY) {
      if (res == MP_NO)
	continue;	/* was composite */
      goto CLEANUP;
    }
    FPUTC('!', stderr);

    if (!strong) 
      break;	/* success !! */

    /* At this point, we have strong evidence that our candidate
       is itself prime.  If we want a strong prime, we need now
       to test q = 2p + 1 for primality...
     */
    MP_CHECKOK( mp_mul_2(&trial, &q) );
    MP_CHECKOK( mp_add_d(&q, 1, &q)  );

    /* Test q for small prime divisors ... */
    np = prime_tab_size;
    res = mpp_divis_primes(&q, &np);
    if (res == MP_YES) { /* is composite */
      mp_clear(&q);
      continue;
    }
    if (res != MP_NO) 
      goto CLEANUP;

    /* And test with Fermat, as with its parent ... */
    res = mpp_fermat(&q, 2);
    if (res != MP_YES) {
      mp_clear(&q);
      if (res == MP_NO)
	continue;	/* was composite */
      goto CLEANUP;
    }

    /* And test with Miller-Rabin, as with its parent ... */
    res = mpp_pprime(&q, num_tests);
    if (res != MP_YES) {
      mp_clear(&q);
      if (res == MP_NO)
	continue;	/* was composite */
      goto CLEANUP;
    }

    /* If it passed, we've got a winner */
    mp_exch(&q, &trial);
    mp_clear(&q);
    break;

  } /* end of loop through sieved values */
  if (res == MP_YES) 
    mp_exch(&trial, start);
CLEANUP:
  mp_clear(&trial);
  mp_clear(&q);
  if (nTries)
    *nTries += i;
  if (sieve != NULL) {
  	memset(sieve, 0, SIEVE_SIZE);
  	free (sieve);
  }
  return res;
}
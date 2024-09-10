static int ssleay_rand_bytes(unsigned char *buf, int num, int pseudo)
	{
	static volatile int stirred_pool = 0;
	int i,j,k,st_num,st_idx;
	int num_ceil;
	int ok;
	long md_c[2];
	unsigned char local_md[MD_DIGEST_LENGTH];
	EVP_MD_CTX m;
#ifndef GETPID_IS_MEANINGLESS
	pid_t curr_pid = getpid();
#endif
	time_t curr_time = time(NULL);
	int do_stir_pool = 0;
/* time value for various platforms */
#ifdef OPENSSL_SYS_WIN32
	FILETIME tv;
# ifdef _WIN32_WCE
	SYSTEMTIME t;
	GetSystemTime(&t);
	SystemTimeToFileTime(&t, &tv);
# else
	GetSystemTimeAsFileTime(&tv);
# endif
#elif defined(OPENSSL_SYS_VXWORKS)
	struct timespec tv;
	clock_gettime(CLOCK_REALTIME, &ts);
#elif defined(OPENSSL_SYSNAME_DSPBIOS)
	unsigned long long tv, OPENSSL_rdtsc();
	tv = OPENSSL_rdtsc();
#else
	struct timeval tv;
	gettimeofday(&tv, NULL);
#endif

#ifdef PREDICT
	if (rand_predictable)
		{
		static unsigned char val=0;

		for (i=0; i<num; i++)
			buf[i]=val++;
		return(1);
		}
#endif

	if (num <= 0)
		return 1;

	EVP_MD_CTX_init(&m);
	/* round upwards to multiple of MD_DIGEST_LENGTH/2 */
	num_ceil = (1 + (num-1)/(MD_DIGEST_LENGTH/2)) * (MD_DIGEST_LENGTH/2);

	/*
	 * (Based on the rand(3) manpage:)
	 *
	 * For each group of 10 bytes (or less), we do the following:
	 *
	 * Input into the hash function the local 'md' (which is initialized from
	 * the global 'md' before any bytes are generated), the bytes that are to
	 * be overwritten by the random bytes, and bytes from the 'state'
	 * (incrementing looping index). From this digest output (which is kept
	 * in 'md'), the top (up to) 10 bytes are returned to the caller and the
	 * bottom 10 bytes are xored into the 'state'.
	 * 
	 * Finally, after we have finished 'num' random bytes for the
	 * caller, 'count' (which is incremented) and the local and global 'md'
	 * are fed into the hash function and the results are kept in the
	 * global 'md'.
	 */

	CRYPTO_w_lock(CRYPTO_LOCK_RAND);

	/* prevent ssleay_rand_bytes() from trying to obtain the lock again */
	CRYPTO_w_lock(CRYPTO_LOCK_RAND2);
	CRYPTO_THREADID_current(&locking_threadid);
	CRYPTO_w_unlock(CRYPTO_LOCK_RAND2);
	crypto_lock_rand = 1;

	if (!initialized)
		{
		RAND_poll();
		initialized = 1;
		}
	
	if (!stirred_pool)
		do_stir_pool = 1;
	
	ok = (entropy >= ENTROPY_NEEDED);
	if (!ok)
		{
		/* If the PRNG state is not yet unpredictable, then seeing
		 * the PRNG output may help attackers to determine the new
		 * state; thus we have to decrease the entropy estimate.
		 * Once we've had enough initial seeding we don't bother to
		 * adjust the entropy count, though, because we're not ambitious
		 * to provide *information-theoretic* randomness.
		 *
		 * NOTE: This approach fails if the program forks before
		 * we have enough entropy. Entropy should be collected
		 * in a separate input pool and be transferred to the
		 * output pool only when the entropy limit has been reached.
		 */
		entropy -= num;
		if (entropy < 0)
			entropy = 0;
		}

	if (do_stir_pool)
		{
		/* In the output function only half of 'md' remains secret,
		 * so we better make sure that the required entropy gets
		 * 'evenly distributed' through 'state', our randomness pool.
		 * The input function (ssleay_rand_add) chains all of 'md',
		 * which makes it more suitable for this purpose.
		 */

		int n = STATE_SIZE; /* so that the complete pool gets accessed */
		while (n > 0)
			{
#if MD_DIGEST_LENGTH > 20
# error "Please adjust DUMMY_SEED."
#endif
#define DUMMY_SEED "...................." /* at least MD_DIGEST_LENGTH */
			/* Note that the seed does not matter, it's just that
			 * ssleay_rand_add expects to have something to hash. */
			ssleay_rand_add(DUMMY_SEED, MD_DIGEST_LENGTH, 0.0);
			n -= MD_DIGEST_LENGTH;
			}
		if (ok)
			stirred_pool = 1;
		}

	st_idx=state_index;
	st_num=state_num;
	md_c[0] = md_count[0];
	md_c[1] = md_count[1];
	memcpy(local_md, md, sizeof md);

	state_index+=num_ceil;
	if (state_index > state_num)
		state_index %= state_num;

	/* state[st_idx], ..., state[(st_idx + num_ceil - 1) % st_num]
	 * are now ours (but other threads may use them too) */

	md_count[0] += 1;

	/* before unlocking, we must clear 'crypto_lock_rand' */
	crypto_lock_rand = 0;
	CRYPTO_w_unlock(CRYPTO_LOCK_RAND);

	while (num > 0)
		{
		/* num_ceil -= MD_DIGEST_LENGTH/2 */
		j=(num >= MD_DIGEST_LENGTH/2)?MD_DIGEST_LENGTH/2:num;
		num-=j;
		if (!MD_Init(&m))
			goto err;
#ifndef GETPID_IS_MEANINGLESS
		if (curr_pid) /* just in the first iteration to save time */
			{
			if (!MD_Update(&m,(unsigned char*)&curr_pid,
				       sizeof curr_pid))
				goto err;
			curr_pid = 0;
			}
#endif
		if (curr_time) /* just in the first iteration to save time */
			{
			if (!MD_Update(&m,(unsigned char*)&curr_time,
				       sizeof curr_time))
				goto err;
			if (!MD_Update(&m,(unsigned char*)&tv,
				       sizeof tv))
				goto err;
			curr_time = 0;
			rand_hw_seed(&m);
			}
		if (!MD_Update(&m,local_md,MD_DIGEST_LENGTH))
			goto err;
		if (!MD_Update(&m,(unsigned char *)&(md_c[0]),sizeof(md_c)))
			goto err;

#ifndef PURIFY /* purify complains */
		/* The following line uses the supplied buffer as a small
		 * source of entropy: since this buffer is often uninitialised
		 * it may cause programs such as purify or valgrind to
		 * complain. So for those builds it is not used: the removal
		 * of such a small source of entropy has negligible impact on
		 * security.
		 */
		if (!MD_Update(&m,buf,j))
			goto err;
#endif

		k=(st_idx+MD_DIGEST_LENGTH/2)-st_num;
		if (k > 0)
			{
			if (!MD_Update(&m,&(state[st_idx]),MD_DIGEST_LENGTH/2-k))
				goto err;
			if (!MD_Update(&m,&(state[0]),k))
				goto err;
			}
		else
			if (!MD_Update(&m,&(state[st_idx]),MD_DIGEST_LENGTH/2))
				goto err;
		if (!MD_Final(&m,local_md))
			goto err;

		for (i=0; i<MD_DIGEST_LENGTH/2; i++)
			{
			state[st_idx++]^=local_md[i]; /* may compete with other threads */
			if (st_idx >= st_num)
				st_idx=0;
			if (i < j)
				*(buf++)=local_md[i+MD_DIGEST_LENGTH/2];
			}
		}

	if (!MD_Init(&m)
		|| !MD_Update(&m,(unsigned char *)&(md_c[0]),sizeof(md_c))
		|| !MD_Update(&m,local_md,MD_DIGEST_LENGTH))
		goto err;
	CRYPTO_w_lock(CRYPTO_LOCK_RAND);
	if (!MD_Update(&m,md,MD_DIGEST_LENGTH) || !MD_Final(&m,md))
		{
		CRYPTO_w_unlock(CRYPTO_LOCK_RAND);
		goto err;
		}
	CRYPTO_w_unlock(CRYPTO_LOCK_RAND);

	EVP_MD_CTX_cleanup(&m);
	if (ok)
		return(1);
	else if (pseudo)
		return 0;
	else 
		{
		RANDerr(RAND_F_SSLEAY_RAND_BYTES,RAND_R_PRNG_NOT_SEEDED);
		ERR_add_error_data(1, "You need to read the OpenSSL FAQ, "
			"http://www.openssl.org/support/faq.html");
		return(0);
		}
	err:
	EVP_MD_CTX_cleanup(&m);
	RANDerr(RAND_F_SSLEAY_RAND_BYTES,ERR_R_EVP_LIB);
	return 0;

	}
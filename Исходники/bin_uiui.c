void
mpz_bin_uiui (mpz_ptr r, unsigned long int n, unsigned long int k)
{
    unsigned long int  i, j;
    mp_limb_t          nacc, kacc;
    unsigned long int  cnt;
    mp_size_t          rsize, ralloc;
    mp_ptr             rp;

    /* bin(n,k) = 0 if k>n. */
    if (n < k)
    {
        SIZ(r) = 0;
        return;
    }

    rp = PTR(r);

    /* Rewrite bin(n,k) as bin(n,n-k) if that is smaller. */
    k = MIN (k, n-k);

    /* bin(n,0) = 1 */
    if (k == 0)
    {
        SIZ(r) = 1;
        rp[0] = 1;
        return;
    }

    j = n - k + 1;
    rp[0] = j;
    rsize = 1;
    ralloc = ALLOC(r);

    /* Initialize accumulators.  */
    nacc = 1;
    kacc = 1;

    cnt = 0;
    for (i = 2; i <= k; i++)
    {
        mp_limb_t n1, n0, k0;

        j++;
#if 0
        /* Remove common multiples of 2.  This will allow us to accumulate
           more in nacc and kacc before we need a bignum step.  It would make
           sense to cancel factors of 3, 5, etc too, but this would be best
           handled by sieving out factors.  Alternatively, we could perform a
           gcd of the accumulators just as they have overflown, and keep
           accumulating until the gcd doesn't remove a significant factor.  */
        while (((nacc | kacc) & 1) == 0)
        {
            nacc >>= 1;
            kacc >>= 1;
        }
#else
        cnt = ((nacc | kacc) & 1) ^ 1;
        nacc >>= cnt;
        kacc >>= cnt;
#endif
        /* Accumulate next multiples.  */
        umul_ppmm (n1, n0, nacc, (mp_limb_t) j << GMP_NAIL_BITS);
        k0 = kacc * i;
        n0 >>= GMP_NAIL_BITS;
        if (n1 != 0)
        {
            /* Accumulator overflow.  Perform bignum step. */
            MULDIV (32);
            nacc = j;
            kacc = i;
        }
        else
        {
            /* k<=n, so should have no overflow from k0 = kacc*i */
            ASSERT (kacc <= GMP_NUMB_MAX / i);

            /* Save new products in accumulators to keep accumulating.  */
            nacc = n0;
            kacc = k0;
        }
    }

    /* Take care of whatever is left in accumulators.  */
    MULDIV (1);

    ALLOC(r) = ralloc;
    SIZ(r) = rsize;
    PTR(r) = rp;
}
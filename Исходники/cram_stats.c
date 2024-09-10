/*
 * Computes entropy from integer frequencies for various encoding methods and
 * picks the best encoding.
 *
 * FIXME: we could reuse some of the code here for the actual encoding
 * parameters too. Eg the best 'k' for SUBEXP or the code lengths for huffman.
 *
 * Returns the best codec to use.
 */
enum cram_encoding cram_stats_encoding(cram_fd *fd, cram_stats *st) {
    enum cram_encoding best_encoding = E_NULL;
    int best_size = INT_MAX, bits;
    int nvals, i, ntot = 0, max_val = 0, min_val = INT_MAX, k;
    int *vals = NULL, *freqs = NULL, vals_alloc = 0, *codes;

    //cram_stats_dump(st);

    /* Count number of unique symbols */
    for (nvals = i = 0; i < MAX_STAT_VAL; i++) {
	if (!st->freqs[i])
	    continue;
	if (nvals >= vals_alloc) {
	    vals_alloc = vals_alloc ? vals_alloc*2 : 1024;
	    vals  = realloc(vals,  vals_alloc * sizeof(int));
	    freqs = realloc(freqs, vals_alloc * sizeof(int));
	    if (!vals || !freqs) {
		if (vals)  free(vals);
		if (freqs) free(freqs);
		return E_HUFFMAN; // Cannot do much else atm
	    }
	}
	vals[nvals] = i;
	freqs[nvals] = st->freqs[i];
	ntot += freqs[nvals];
	if (max_val < i) max_val = i;
	if (min_val > i) min_val = i;
	nvals++;
    }
    if (st->h) {
	HashIter *iter=  HashTableIterCreate();
	HashItem *hi;
	int i;

	while ((hi = HashTableIterNext(st->h, iter))) {
	    if (nvals >= vals_alloc) {
		vals_alloc = vals_alloc ? vals_alloc*2 : 1024;
		vals  = realloc(vals,  vals_alloc * sizeof(int));
		freqs = realloc(freqs, vals_alloc * sizeof(int));
		if (!vals || !freqs)
		    return E_HUFFMAN; // Cannot do much else atm
	    }
	    i = (size_t)hi->key;
	    vals[nvals]=i;
	    freqs[nvals] = hi->data.i;
	    ntot += freqs[nvals];
	    if (max_val < i) max_val = i;
	    if (min_val > i) min_val = i;
	    nvals++;
	}
	HashTableIterDestroy(iter);
    }

    st->nvals = nvals;
    assert(ntot == st->nsamp);

#if 0
    // RANDOMISER
    switch(random()%10) {
    case 0:  return E_HUFFMAN;
    case 1:  return E_HUFFMAN;
    //case 1:  return E_BETA; // Java doesn't support E_BETA for BYTE vals
    default: return E_EXTERNAL;
    }
#endif

    if (nvals <= 1) {
	free(vals);
	free(freqs);

	if (fd->verbose > 1)
	    fprintf(stderr, "0 values => 0 bits\n");

	return E_HUFFMAN;
    }

    if (fd->verbose > 1)
	fprintf(stderr, "Range = %d..%d, nvals=%d, ntot=%d\n",
		min_val, max_val, nvals, ntot);

    /* Theoretical entropy */
    if (fd->verbose > 1) {
	double dbits = 0;
	for (i = 0; i < nvals; i++) {
	    dbits += freqs[i] * log((double)freqs[i]/ntot);
	}
	dbits /= -log(2);
	if (fd->verbose > 1)
	    fprintf(stderr, "Entropy = %f\n", dbits);
    }

    if (nvals > 1 && ntot > 256) {
#if 0
	/*
	 * CRUDE huffman estimator. Round to closest and round up from 0
	 * to 1 bit.
	 *
	 * With and without ITF8 incase we have a few discrete values but with
	 * large magnitude.
	 *
	 * Note rans0/arith0 and Z_HUFFMAN_ONLY vs internal huffman can be
	 * compared in this way, but order-1 (eg rans1) or maybe LZ77 modes
	 * may detect the correlation of high bytes to low bytes in multi-
	 * byte values. So this predictor breaks down.
	 */
	double dbits = 0;  // entropy + ~huffman
	double dbitsH = 0;
	double dbitsE = 0; // external entropy + ~huffman
	double dbitsEH = 0;
	int F[256] = {0}, n = 0;
	double e = 0; // accumulated error bits
	for (i = 0; i < nvals; i++) {
	    double x; int X;
	    unsigned int v = vals[i];

	    //Better encoding would cope with sign.
	    //v = ABS(vals[i])*2+(vals[i]<0);

	    if (!(v & ~0x7f)) {
		F[v]             += freqs[i], n+=freqs[i];
	    } else if (!(v & ~0x3fff)) {
		F[(v>>8) |0x80] += freqs[i];
		F[ v     &0xff] += freqs[i], n+=2*freqs[i];
	    } else if (!(v & ~0x1fffff)) {
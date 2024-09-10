static void memset_bigalloc(bigalloc_num_t *begin, bigalloc_num_t num, 
	bigalloc_num_t old_num, size_t n)
{
	assert(1ull<<(8*sizeof(bigalloc_num_t)) >= NBIGALLOCS - 1);
	assert(sizeof (wchar_t) == 2 * sizeof (bigalloc_num_t));

	/* We use wmemset with special cases at the beginning and end */
	if (n > 0 && (uintptr_t) begin % sizeof (wchar_t) != 0)
	{
#ifndef NDEBUG
		if (old_num != (bigalloc_num_t) -1 && *begin != old_num) abort();
#endif
		*begin++ = num;
		--n;
	}
	assert(n == 0 || (uintptr_t) begin % sizeof (wchar_t) == 0);
	
	// double up the value
	wchar_t wchar_val     = ((wchar_t) num)     << (8 * sizeof(bigalloc_num_t)) | num;
	wchar_t wchar_old_val = ((wchar_t) old_num) << (8 * sizeof(bigalloc_num_t)) | old_num;
	
	// do the memset
	wchar_t accept[] = { wchar_old_val, '\0' };
	// PROBLEM: if our accept val is 0, 
#ifndef NDEBUG
	ssize_t max_len = (ssize_t) -1;
	if (old_num != (bigalloc_num_t) -1 && old_num) // FIXME: also check when old_num is zero
	{
		max_len = wcsspn((wchar_t *) begin, accept);
		if (max_len < n/2) abort();
	}
#endif
	if (n != 0) wmemset((wchar_t *) begin, wchar_val, n / 2);
	
	// if we missed one off the end, do it now
	if (n % 2 == 1)
	{
#ifndef NDEBUG
		if (old_num != (bigalloc_num_t) -1 && *(begin + (n-1)) != old_num) abort();
#endif
		*(begin + (n-1)) = num;
	}
}
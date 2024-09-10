__strspn_sse42 (const char *s, const char *a)
{
  if (*a == 0)
    return 0;

  const char *aligned;
  __m128i mask;
  int offset = (int) ((size_t) a & 15);
  if (offset != 0)
    {
      /* Load masks.  */
      aligned = (const char *) ((size_t) a & -16L);
      __m128i mask0 = _mm_load_si128 ((__m128i *) aligned);

      mask = __m128i_shift_right (mask0, offset);

      /* Find where the NULL terminator is.  */
      int length = _mm_cmpistri (mask, mask, 0x3a);
      if (length == 16 - offset)
	{
	  /* There is no NULL terminator.  */
	  __m128i mask1 = _mm_load_si128 ((__m128i *) (aligned + 16));
	  int index = _mm_cmpistri (mask1, mask1, 0x3a);
	  length += index;

	  /* Don't use SSE4.2 if the length of A > 16.  */
	  if (length > 16)
	    return __strspn_sse2 (s, a);

	  if (index != 0)
	    {
	      /* Combine mask0 and mask1.  We could play games with
		 palignr, but frankly this data should be in L1 now
		 so do the merge via an unaligned load.  */
	      mask = _mm_loadu_si128 ((__m128i *) a);
	    }
	}
    }
  else
    {
      /* A is aligned.  */
      mask = _mm_load_si128 ((__m128i *) a);

      /* Find where the NULL terminator is.  */
      int length = _mm_cmpistri (mask, mask, 0x3a);
      if (length == 16)
	{
	  /* There is no NULL terminator.  Don't use SSE4.2 if the length
	     of A > 16.  */
	  if (a[16] != 0)
	    return __strspn_sse2 (s, a);
	}
    }

  offset = (int) ((size_t) s & 15);
  if (offset != 0)
    {
      /* Check partial string.  */
      aligned = (const char *) ((size_t) s & -16L);
      __m128i value = _mm_load_si128 ((__m128i *) aligned);

      value = __m128i_shift_right (value, offset);

      int length = _mm_cmpistri (mask, value, 0x12);
      /* No need to check CFlag since it is always 1.  */
      if (length < 16 - offset)
	return length;
      /* Find where the NULL terminator is.  */
      int index = _mm_cmpistri (value, value, 0x3a);
      if (index < 16 - offset)
	return length;
      aligned += 16;
    }
  else
    aligned = s;

  while (1)
    {
      __m128i value = _mm_load_si128 ((__m128i *) aligned);
      int index = _mm_cmpistri (mask, value, 0x12);
      int cflag = _mm_cmpistrc (mask, value, 0x12);
      if (cflag)
	return (size_t) (aligned + index - s);
      aligned += 16;
    }
}
size_t
mpz_inp_raw (mpz_ptr x, FILE *fp)
{
  unsigned char  csize_bytes[4];
  mp_size_t      csize, abs_xsize, i;
  size_t         abs_csize;
  char           *cp;
  mp_ptr         xp, sp, ep;
  mp_limb_t      slimb, elimb;

  if (fp == 0)
    fp = stdin;

  /* 4 bytes for size */
  if (fread (csize_bytes, sizeof (csize_bytes), 1, fp) != 1)
    return 0;

  csize =
    (  (mp_size_t) csize_bytes[0] << 24)
    + ((mp_size_t) csize_bytes[1] << 16)
    + ((mp_size_t) csize_bytes[2] << 8)
    + ((mp_size_t) csize_bytes[3]);

  /* Sign extend if necessary.
     Could write "csize -= ((csize & 0x80000000L) << 1)", but that tickles a
     bug in gcc 3.0 for powerpc64 on AIX.  */
  if (sizeof (csize) > 4 && csize & 0x80000000L)
    csize -= 0x80000000L << 1;

  abs_csize = ABS (csize);

  /* round up to a multiple of limbs */
  abs_xsize = BITS_TO_LIMBS (abs_csize*8);

  if (abs_xsize != 0)
    {
      xp = MPZ_NEWALLOC (x, abs_xsize);

      /* Get limb boundaries right in the read, for the benefit of the
	 non-nails case.  */
      xp[0] = 0;
      cp = (char *) (xp + abs_xsize) - abs_csize;
      if (fread (cp, abs_csize, 1, fp) != 1)
	return 0;

      if (GMP_NAIL_BITS == 0)
	{
	  /* Reverse limbs to least significant first, and byte swap.  If
	     abs_xsize is odd then on the last iteration elimb and slimb are
	     the same.  It doesn't seem extra code to handle that case
	     separately, to save an NTOH.  */
	  sp = xp;
	  ep = xp + abs_xsize-1;
	  for (i = 0; i < (abs_xsize+1)/2; i++)
	    {
	      NTOH_LIMB_FETCH (elimb, ep);
	      NTOH_LIMB_FETCH (slimb, sp);
	      *sp++ = elimb;
	      *ep-- = slimb;
	    }
	}
      else
	{
	  /* It ought to be possible to do the transformation in-place, but
	     for now it's easier to use an extra temporary area.  */
	  mp_limb_t  byte, limb;
	  int	     bits;
	  mp_size_t  tpos;
	  mp_ptr     tp;
	  TMP_DECL;

	  TMP_MARK;
	  tp = TMP_ALLOC_LIMBS (abs_xsize);
	  limb = 0;
	  bits = 0;
	  tpos = 0;
	  for (i = abs_csize-1; i >= 0; i--)
	    {
	      byte = (unsigned char) cp[i];
	      limb |= (byte << bits);
	      bits += 8;
	      if (bits >= GMP_NUMB_BITS)
		{
		  ASSERT (tpos < abs_xsize);
		  tp[tpos++] = limb & GMP_NUMB_MASK;
		  bits -= GMP_NUMB_BITS;
		  ASSERT (bits < 8);
		  limb = byte >> (8 - bits);
		}
	    }
	  if (bits != 0)
	    {
	      ASSERT (tpos < abs_xsize);
	      tp[tpos++] = limb;
	    }
	  ASSERT (tpos == abs_xsize);

	  MPN_COPY (xp, tp, abs_xsize);
	  TMP_FREE;
	}
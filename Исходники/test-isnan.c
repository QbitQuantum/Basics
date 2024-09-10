static void
test_long_double (void)
{
  #define NWORDSL \
    ((sizeof (long double) + sizeof (unsigned int) - 1) / sizeof (unsigned int))
  typedef union { unsigned int word[NWORDSL]; long double value; }
          memory_long_double;

  /* Finite values.  */
  ASSERT (!isnan (3.141L));
  ASSERT (!isnan (3.141e30L));
  ASSERT (!isnan (3.141e-30L));
  ASSERT (!isnan (-2.718L));
  ASSERT (!isnan (-2.718e30L));
  ASSERT (!isnan (-2.718e-30L));
  ASSERT (!isnan (0.0L));
  ASSERT (!isnan (minus_zerol));
  /* Infinite values.  */
  ASSERT (!isnan (Infinityl ()));
  ASSERT (!isnan (- Infinityl ()));
  /* Quiet NaN.  */
  ASSERT (isnan (NaNl ()));

#if defined LDBL_EXPBIT0_WORD && defined LDBL_EXPBIT0_BIT
  /* A bit pattern that is different from a Quiet NaN.  With a bit of luck,
     it's a Signalling NaN.  */
  {
#if defined __powerpc__ && LDBL_MANT_DIG == 106
    /* This is PowerPC "double double", a pair of two doubles.  Inf and Nan are
       represented as the corresponding 64-bit IEEE values in the first double;
       the second is ignored.  Manipulate only the first double.  */
    #undef NWORDSL
    #define NWORDSL \
      ((sizeof (double) + sizeof (unsigned int) - 1) / sizeof (unsigned int))
#endif

    memory_long_double m;
    m.value = NaNl ();
# if LDBL_EXPBIT0_BIT > 0
    m.word[LDBL_EXPBIT0_WORD] ^= (unsigned int) 1 << (LDBL_EXPBIT0_BIT - 1);
# else
    m.word[LDBL_EXPBIT0_WORD + (LDBL_EXPBIT0_WORD < NWORDSL / 2 ? 1 : - 1)]
      ^= (unsigned int) 1 << (sizeof (unsigned int) * CHAR_BIT - 1);
# endif
    m.word[LDBL_EXPBIT0_WORD + (LDBL_EXPBIT0_WORD < NWORDSL / 2 ? 1 : - 1)]
      |= (unsigned int) 1 << LDBL_EXPBIT0_BIT;
    ASSERT (isnan (m.value));
  }
#endif

#if ((defined __ia64 && LDBL_MANT_DIG == 64) || (defined __x86_64__ || defined __amd64__) || (defined __i386 || defined __i386__ || defined _I386 || defined _M_IX86 || defined _X86_)) && !HAVE_SAME_LONG_DOUBLE_AS_DOUBLE
/* Representation of an 80-bit 'long double' as an initializer for a sequence
   of 'unsigned int' words.  */
# ifdef WORDS_BIGENDIAN
#  define LDBL80_WORDS(exponent,manthi,mantlo) \
     { ((unsigned int) (exponent) << 16) | ((unsigned int) (manthi) >> 16), \
       ((unsigned int) (manthi) << 16) | (unsigned int) (mantlo) >> 16),    \
       (unsigned int) (mantlo) << 16                                        \
     }
# else
#  define LDBL80_WORDS(exponent,manthi,mantlo) \
     { mantlo, manthi, exponent }
# endif
  { /* Quiet NaN.  */
    static memory_long_double x =
      { LDBL80_WORDS (0xFFFF, 0xC3333333, 0x00000000) };
    ASSERT (isnan (x.value));
  }
  {
    /* Signalling NaN.  */
    static memory_long_double x =
      { LDBL80_WORDS (0xFFFF, 0x83333333, 0x00000000) };
    ASSERT (isnan (x.value));
  }
  /* The isnan function should recognize Pseudo-NaNs, Pseudo-Infinities,
     Pseudo-Zeroes, Unnormalized Numbers, and Pseudo-Denormals, as defined in
       Intel IA-64 Architecture Software Developer's Manual, Volume 1:
       Application Architecture.
       Table 5-2 "Floating-Point Register Encodings"
       Figure 5-6 "Memory to Floating-Point Register Data Translation"
   */
  { /* Pseudo-NaN.  */
    static memory_long_double x =
      { LDBL80_WORDS (0xFFFF, 0x40000001, 0x00000000) };
    ASSERT (isnan (x.value));
  }
  { /* Pseudo-Infinity.  */
    static memory_long_double x =
      { LDBL80_WORDS (0xFFFF, 0x00000000, 0x00000000) };
    ASSERT (isnan (x.value));
  }
  { /* Pseudo-Zero.  */
    static memory_long_double x =
      { LDBL80_WORDS (0x4004, 0x00000000, 0x00000000) };
    ASSERT (isnan (x.value));
  }
  { /* Unnormalized number.  */
    static memory_long_double x =
      { LDBL80_WORDS (0x4000, 0x63333333, 0x00000000) };
    ASSERT (isnan (x.value));
  }
  { /* Pseudo-Denormal.  */
    static memory_long_double x =
      { LDBL80_WORDS (0x0000, 0x83333333, 0x00000000) };
    ASSERT (isnan (x.value));
  }
#endif
}
int
main ()
{
  /* Finite values.  */
  ASSERT (!isnanf (3.141f));
  ASSERT (!isnanf (3.141e30f));
  ASSERT (!isnanf (3.141e-30f));
  ASSERT (!isnanf (-2.718f));
  ASSERT (!isnanf (-2.718e30f));
  ASSERT (!isnanf (-2.718e-30f));
  ASSERT (!isnanf (0.0f));
  ASSERT (!isnanf (-0.0f));
  /* Infinite values.  */
  ASSERT (!isnanf (1.0f / 0.0f));
  ASSERT (!isnanf (-1.0f / 0.0f));
  /* Quiet NaN.  */
  ASSERT (isnanf (NaN ()));
#if defined FLT_EXPBIT0_WORD && defined FLT_EXPBIT0_BIT
  /* Signalling NaN.  */
  {
    #define NWORDS \
      ((sizeof (float) + sizeof (unsigned int) - 1) / sizeof (unsigned int))
    typedef union { float value; unsigned int word[NWORDS]; } memory_float;
    memory_float m;
    m.value = NaN ();
# if FLT_EXPBIT0_BIT > 0
    m.word[FLT_EXPBIT0_WORD] ^= (unsigned int) 1 << (FLT_EXPBIT0_BIT - 1);
# else
    m.word[FLT_EXPBIT0_WORD + (FLT_EXPBIT0_WORD < NWORDS / 2 ? 1 : - 1)]
      ^= (unsigned int) 1 << (sizeof (unsigned int) * CHAR_BIT - 1);
# endif
    if (FLT_EXPBIT0_WORD < NWORDS / 2)
      m.word[FLT_EXPBIT0_WORD + 1] |= (unsigned int) 1 << FLT_EXPBIT0_BIT;
    else
      m.word[0] |= (unsigned int) 1;
    ASSERT (isnanf (m.value));
  }
#endif
  return 0;
}
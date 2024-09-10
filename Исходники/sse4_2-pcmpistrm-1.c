static void
TEST (void)
{
  union
    {
      __m128i x[NUM];
      char c[NUM *16];
    } src1, src2;
  __m128i res, correct;
  int i;

  for (i = 0; i < NUM *16; i++)
    {
      src1.c[i] = rand ();
      src2.c[i] = rand ();
    }

  for (i = 0; i < NUM; i++)
    {
      switch((rand() % 4))
	{
	case 0:
	  res  = _mm_cmpistrm (src1.x[i], src2.x[i], IMM_VAL0);
	  correct = cmp_im (&src1.x[i], &src2.x[i], IMM_VAL0, NULL);
	  break;

	case 1:
	  res  = _mm_cmpistrm (src1.x[i], src2.x[i], IMM_VAL1);
	  correct = cmp_im (&src1.x[i], &src2.x[i], IMM_VAL1, NULL);
	  break;

	case 2:
	  res  = _mm_cmpistrm (src1.x[i], src2.x[i], IMM_VAL2);
	  correct = cmp_im (&src1.x[i], &src2.x[i], IMM_VAL2, NULL);
	  break;

	default:
	  res  = _mm_cmpistrm (src1.x[i], src2.x[i], IMM_VAL3);
	  correct = cmp_im (&src1.x[i], &src2.x[i], IMM_VAL3, NULL);
	  break;
        }

      if (memcmp (&correct, &res, sizeof (res)))
	abort ();
    }
}
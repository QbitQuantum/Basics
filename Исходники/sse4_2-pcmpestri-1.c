static void
sse4_2_test (void)
{
  union
    {
      __m128i x[NUM];
      char c[NUM *16];
    } src1, src2;
  int res, correct, l1, l2;
  int i;

  for (i = 0; i < NUM *16; i++)
    {
      src1.c[i] = rand ();
      src2.c[i] = rand ();
    }

  for (i = 0; i < NUM; i++)
    {
      l1 = rand () % 18;
      l2 = rand () % 18;

      switch ((rand () % 4))
	{
	case 0:
	  res = _mm_cmpestri (src1.x[i], l1, src2.x[i], l2, IMM_VAL0);
	  correct = cmp_ei (&src1.x[i], l1, &src2.x[i], l2, IMM_VAL0,
			    NULL);
	  break;

	case 1:
	  res = _mm_cmpestri (src1.x[i], l1, src2.x[i], l2, IMM_VAL1);
	  correct = cmp_ei (&src1.x[i], l1, &src2.x[i], l2, IMM_VAL1,
			    NULL);
	  break;

	case 2:
	  res = _mm_cmpestri (src1.x[i], l1, src2.x[i], l2, IMM_VAL2);
	  correct = cmp_ei (&src1.x[i], l1, &src2.x[i], l2, IMM_VAL2,
			    NULL);
	  break;

	default:
	  res = _mm_cmpestri (src1.x[i], l1, src2.x[i], l2, IMM_VAL3);
	  correct = cmp_ei (&src1.x[i], l1, &src2.x[i], l2, IMM_VAL3,
			    NULL);
	  break;
        }

      if (correct != res)
	abort ();
    }
}
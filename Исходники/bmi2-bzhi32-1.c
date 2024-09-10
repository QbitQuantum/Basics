static void
bmi2_test ()
{
  unsigned i;
  unsigned src = 0xce7ace0f;
  unsigned res, res_ref;

  for (i = 0; i < 5; ++i) {
    src = src * (i + 1);

    res_ref = calc_bzhi_u32 (src, i * 2);
    res = _bzhi_u32 (src, i * 2);

    if (res != res_ref)
      abort();
  }
}
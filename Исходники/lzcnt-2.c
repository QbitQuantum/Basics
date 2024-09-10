static void
lzcnt_test ()
{
  unsigned i;
  short src = 0x7ace;
  short res, res_ref;

  for (i=0; i<5; ++i) {
    src = src >> i;

    res_ref = calc_lzcnt_u16 (src);
    res = __lzcnt16 (src);

    if (res != res_ref)
      abort();
  }
}
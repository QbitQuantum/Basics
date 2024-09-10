int
main (int argc, char **argv)
{
  mp_ptr r1p, r2p, s1p, s2p;
  double t;
  mp_size_t n;

  n = strtol (argv[1], 0, 0);

  r1p = malloc (n * BYTES_PER_MP_LIMB);
  r2p = malloc (n * BYTES_PER_MP_LIMB);
  s1p = malloc (n * BYTES_PER_MP_LIMB);
  s2p = malloc (n * BYTES_PER_MP_LIMB);
  TIME (t,(mpn_add_n(r1p,s1p,s2p,n),mpn_sub_n(r1p,s1p,s2p,n)));
  printf ("              separate add and sub: %.3f\n", t);
  TIME (t,mpn_addsub_n(r1p,r2p,s1p,s2p,n));
  printf ("combined addsub separate variables: %.3f\n", t);
  TIME (t,mpn_addsub_n(r1p,r2p,r1p,s2p,n));
  printf ("        combined addsub r1 overlap: %.3f\n", t);
  TIME (t,mpn_addsub_n(r1p,r2p,r1p,s2p,n));
  printf ("        combined addsub r2 overlap: %.3f\n", t);
  TIME (t,mpn_addsub_n(r1p,r2p,r1p,r2p,n));
  printf ("          combined addsub in-place: %.3f\n", t);

  return 0;
}
static void
test_special2z (int (*mpfr_func)(mpfr_ptr, mpz_srcptr, mpfr_srcptr, mpfr_rnd_t),
               void (*mpz_func)(mpz_ptr, mpz_srcptr, mpz_srcptr),
               const char *op)
{
  mpfr_t x1, x2;
  mpz_t  z1, z2;
  int res;

  mpfr_inits2 (128, x1, x2, (mpfr_ptr) 0);
  mpz_init (z1); mpz_init(z2);
  mpz_fac_ui (z1, 19); /* 19!+1 fits perfectly in a 128 bits mantissa */
  mpz_add_ui (z1, z1, 1);
  mpz_fac_ui (z2, 20); /* 20!+1 fits perfectly in a 128 bits mantissa */
  mpz_add_ui (z2, z2, 1);

  res = mpfr_set_z(x1, z1, MPFR_RNDN);
  if (res)
    {
      printf("Special2z %s: set_z1 error\n", op);
      exit(1);
    }
  mpfr_set_z (x2, z2, MPFR_RNDN);
  if (res)
    {
      printf("Special2z %s: set_z2 error\n", op);
      exit(1);
    }

  /* (19!+1) * (20!+1) fits in a 128 bits number */
  res = mpfr_func(x1, z1, x2, MPFR_RNDN);
  if (res)
    {
      printf("Special2z %s: wrong inexact flag.\n", op);
      exit(1);
    }
  mpz_func(z1, z1, z2);
  res = mpfr_set_z (x2, z1, MPFR_RNDN);
  if (res)
    {
      printf("Special2z %s: set_z2 error\n", op);
      exit(1);
    }
  if (mpfr_cmp(x1, x2))
    {
      printf("Special2z %s: results differ.\nx1=", op);
      mpfr_dump (x1);
      printf ("x2=");
      mpfr_dump (x2);
      printf ("Z2=");
      mpz_out_str (stdout, 2, z1);
      putchar('\n');
      exit(1);
    }

  mpz_set_ui (z1, 0);
  mpz_set_ui (z2, 1);
  mpfr_set_ui (x2, 1, MPFR_RNDN);
  res = mpfr_func(x1, z1, x2, MPFR_RNDN);
  mpz_func (z1, z1, z2);
  mpfr_set_z (x2, z1, MPFR_RNDN);
  if (mpfr_cmp(x1, x2))
    {
      printf("Special2z %s: results differ(2).\nx1=", op);
      mpfr_dump (x1);
      printf ("x2=");
      mpfr_dump (x2);
      exit(1);
    }

  mpz_clear (z1); mpz_clear(z2);
  mpfr_clears (x1, x2, (mpfr_ptr) 0);
}
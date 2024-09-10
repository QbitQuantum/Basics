void
testmain (int argc, char **argv)
{
  unsigned i;
  mpz_t x;

  for (i = 0; values[i].s; i++)
    {
      char *s;
      mpz_init_set_d (x, values[i].d);
      s = mpz_get_str (NULL, 16, x);
      if (strcmp (s, values[i].s) != 0)
	{
	  fprintf (stderr, "mpz_set_d failed:\n"
		   "d = %.20g\n"
		   "s = %s\n"
		   "r = %s\n",
		   values[i].d, s, values[i].s);
	  abort ();
	}
      testfree (s);
      mpz_clear (x);
    }

  mpz_init (x);

  for (i = 0; i < COUNT; i++)
    {
      /* Use volatile, to avoid extended precision in floating point
	 registers, e.g., on m68k and 80387. */
      volatile double d, f;
      unsigned long m;
      int e;

      mini_rrandomb (x, GMP_LIMB_BITS);
      m = mpz_get_ui (x);
      mini_urandomb (x, 8);
      e = mpz_get_ui (x) - 100;

      d = ldexp ((double) m, e);
      mpz_set_d (x, d);
      f = mpz_get_d (x);
      if (f != floor (d))
	{
	  fprintf (stderr, "mpz_set_d/mpz_get_d failed:\n");
	  goto dumperror;
	}
      if ((f == d) ? (mpz_cmp_d (x, d) != 0) : (mpz_cmp_d (x, d) >= 0))
	{
	  fprintf (stderr, "mpz_cmp_d (x, d) failed:\n");
	  goto dumperror;
	}
      f = d + 1.0;
      if (f > d && ! (mpz_cmp_d (x, f) < 0))
	{
	  fprintf (stderr, "mpz_cmp_d (x, f) failed:\n");
	  goto dumperror;
	}

      d = - d;

      mpz_set_d (x, d);
      f = mpz_get_d (x);
      if (f != ceil (d))
	{
	  fprintf (stderr, "mpz_set_d/mpz_get_d failed:\n");
	dumperror:
	  dump ("x", x);
	  fprintf (stderr, "m = %lx, e = %i\n", m, e);
	  fprintf (stderr, "d = %.15g\n", d);
	  fprintf (stderr, "f = %.15g\n", f);
	  fprintf (stderr, "f - d = %.5g\n", f - d);
	  abort ();
	}
      if ((f == d) ? (mpz_cmp_d (x, d) != 0) : (mpz_cmp_d (x, d) <= 0))
	{
	  fprintf (stderr, "mpz_cmp_d (x, d) failed:\n");
	  goto dumperror;
	}
      f = d - 1.0;
      if (f < d && ! (mpz_cmp_d (x, f) > 0))
	{
	  fprintf (stderr, "mpz_cmp_d (x, f) failed:\n");
	  goto dumperror;
	}
    }

  mpz_clear (x);
}
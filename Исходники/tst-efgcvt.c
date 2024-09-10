static void
special (void)
{
  int decpt, sign, res;
  char *p;
  char buf [1024];

  p = ecvt (NAN, 10, &decpt, &sign);
  if (sign != 0 || strcmp (p, "nan") != 0)
    output_error ("ecvt", NAN, 10, "nan", 0, 0, p, decpt, sign);

  p = ecvt (INFINITY, 10, &decpt, &sign);
  if (sign != 0 || strcmp (p, "inf") != 0)
    output_error ("ecvt", INFINITY, 10, "inf", 0, 0, p, decpt, sign);

  /* Simply make sure these calls with large NDIGITs don't crash.  */
  (void) ecvt (123.456, 10000, &decpt, &sign);
  (void) fcvt (123.456, 10000, &decpt, &sign);

  /* Some tests for the reentrant functions.  */
  /* Use a too small buffer.  */
  res = ecvt_r (123.456, 10, &decpt, &sign, buf, 1);
  if (res == 0)
    {
      printf ("ecvt_r with a too small buffer was succesful.\n");
      ++error_count;
    }
  res = fcvt_r (123.456, 10, &decpt, &sign, buf, 1);
  if (res == 0)
    {
      printf ("fcvt_r with a too small buffer was succesful.\n");
      ++error_count;
    }
}
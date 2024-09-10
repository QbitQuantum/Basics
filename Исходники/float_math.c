/* Test NaN-resulting library calls. */
int test_errs() {
  int errs = 0;

  printf("Checking well-defined library errors\n");
  errs += CHECK_NAN(pow(-3.0, 4.4));
  errs += CHECK_NAN(log(-3.0));
  errs += CHECK_NAN(sqrt(-0.001));
  errs += CHECK_NAN(asin(1.0001));
  errs += CHECK_NAN(sin(INFINITY));
  errs += CHECK_NAN(cos(INFINITY));
  errs += CHECK_NAN(acosh(0.999));
  errs += CHECK_NAN(remainder(3.3, 0.0));
  errs += CHECK_NAN(remainder(INFINITY, 3.3));
  return errs;
}
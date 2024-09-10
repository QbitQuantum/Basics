int main()
{
  double a, r;

  a = __VERIFIER_nondet_double();
  __VERIFIER_assume(a >= -1e10 && a <= 1e10);

  r = SIN(a);
  return 0;
}
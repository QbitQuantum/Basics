literalt boolector_propt::lnot(literalt a)
{
  a.invert();
  return a;
}
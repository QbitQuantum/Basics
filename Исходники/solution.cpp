R1_R1::operator Real()
{
   if (!xSet) Throw(SolutionException("Value of X not set"));
   Real y = operator()();
   return y;
}
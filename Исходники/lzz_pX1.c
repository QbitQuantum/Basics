void ShiftSub(zz_pX& U, const zz_pX& V, long n)
// assumes input does not alias output
{
   if (IsZero(V))
      return;

   long du = deg(U);
   long dv = deg(V);

   long d = max(du, n+dv);

   U.rep.SetLength(d+1);
   long i;

   for (i = du+1; i <= d; i++)
      clear(U.rep[i]);

   for (i = 0; i <= dv; i++)
      sub(U.rep[i+n], U.rep[i+n], V.rep[i]);

   U.normalize();
}
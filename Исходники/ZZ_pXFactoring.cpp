static
void RandomBasisElt(ZZ_pX& g, const vec_long& D, const vec_ZZVec& M)
{
   ZZ t1, t2;

   long n = D.length();

   long i, j, s;

   g.rep.SetLength(n);

   vec_ZZ_p& v = g.rep;

   for (j = n-1; j >= 0; j--) {
      if (D[j] == -1)
         random(v[j]);
      else {
         i = D[j];

         // v[j] = sum_{s=j+1}^{n-1} v[s]*M[i,s]

         clear(t1);

         for (s = j+1; s < n; s++) {
            mul(t2, rep(v[s]), M[i][s]);
            add(t1, t1, t2);
         }

         conv(v[j], t1);
      }
   }

   g.normalize();
}
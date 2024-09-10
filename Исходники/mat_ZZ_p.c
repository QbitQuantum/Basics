void kernel(mat_ZZ_p& X, const mat_ZZ_p& A)
{
   long m = A.NumRows();
   long n = A.NumCols();

   mat_ZZ_p M;
   long r;

   transpose(M, A);
   r = gauss(M);

   X.SetDims(m-r, m);

   long i, j, k, s;
   ZZ t1, t2;

   ZZ_p T3;

   vec_long D;
   D.SetLength(m);
   for (j = 0; j < m; j++) D[j] = -1;

   vec_ZZ_p inverses;
   inverses.SetLength(m);

   j = -1;
   for (i = 0; i < r; i++) {
      do {
         j++;
      } while (IsZero(M[i][j]));

      D[j] = i;
      inv(inverses[j], M[i][j]); 
   }

   for (k = 0; k < m-r; k++) {
      vec_ZZ_p& v = X[k];
      long pos = 0;
      for (j = m-1; j >= 0; j--) {
         if (D[j] == -1) {
            if (pos == k)
               set(v[j]);
            else
               clear(v[j]);
            pos++;
         }
         else {
            i = D[j];

            clear(t1);

            for (s = j+1; s < m; s++) {
               mul(t2, rep(v[s]), rep(M[i][s]));
               add(t1, t1, t2);
            }

            conv(T3, t1);
            mul(T3, T3, inverses[j]);
            negate(v[j], T3);
         }
      }
   }
}
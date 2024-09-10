int *adat_symbolic(int m, int n, int P_per[], int A_ptr[], int A_ind[],
      int S_ptr[])
{     int i, j, t, ii, jj, tt, k, size, len;
      int *S_ind, *AT_ptr, *AT_ind, *ind, *map, *temp;
      /* build the pattern of A', which is a matrix transposed to A, to
         efficiently access A in column-wise manner */
      AT_ptr = xcalloc(1+n+1, sizeof(int));
      AT_ind = xcalloc(A_ptr[m+1], sizeof(int));
      transpose(m, n, A_ptr, A_ind, NULL, AT_ptr, AT_ind, NULL);
      /* allocate the array S_ind */
      size = A_ptr[m+1] - 1;
      if (size < m) size = m;
      S_ind = xcalloc(1+size, sizeof(int));
      /* allocate and initialize working arrays */
      ind = xcalloc(1+m, sizeof(int));
      map = xcalloc(1+m, sizeof(int));
      for (jj = 1; jj <= m; jj++) map[jj] = 0;
      /* compute pattern of S; note that symbolically S = B*B', where
         B = P*A, B' is matrix transposed to B */
      S_ptr[1] = 1;
      for (ii = 1; ii <= m; ii++)
      {  /* compute pattern of ii-th row of S */
         len = 0;
         i = P_per[ii]; /* i-th row of A = ii-th row of B */
         for (t = A_ptr[i]; t < A_ptr[i+1]; t++)
         {  k = A_ind[t];
            /* walk through k-th column of A */
            for (tt = AT_ptr[k]; tt < AT_ptr[k+1]; tt++)
            {  j = AT_ind[tt];
               jj = P_per[m+j]; /* j-th row of A = jj-th row of B */
               /* a[i,k] != 0 and a[j,k] != 0 ergo s[ii,jj] != 0 */
               if (ii < jj && !map[jj]) ind[++len] = jj, map[jj] = 1;
            }
         }
         /* now (ind) is pattern of ii-th row of S */
         S_ptr[ii+1] = S_ptr[ii] + len;
         /* at least (S_ptr[ii+1] - 1) locations should be available in
            the array S_ind */
         if (S_ptr[ii+1] - 1 > size)
         {  temp = S_ind;
            size += size;
            S_ind = xcalloc(1+size, sizeof(int));
            memcpy(&S_ind[1], &temp[1], (S_ptr[ii] - 1) * sizeof(int));
            xfree(temp);
         }
         xassert(S_ptr[ii+1] - 1 <= size);
         /* (ii-th row of S) := (ind) */
         memcpy(&S_ind[S_ptr[ii]], &ind[1], len * sizeof(int));
         /* clear the row pattern map */
         for (t = 1; t <= len; t++) map[ind[t]] = 0;
      }
      /* free working arrays */
      xfree(AT_ptr);
      xfree(AT_ind);
      xfree(ind);
      xfree(map);
      /* reallocate the array S_ind to free unused locations */
      temp = S_ind;
      size = S_ptr[m+1] - 1;
      S_ind = xcalloc(1+size, sizeof(int));
      memcpy(&S_ind[1], &temp[1], size * sizeof(int));
      xfree(temp);
      return S_ind;
}
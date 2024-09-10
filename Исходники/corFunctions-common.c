void prepareColCor(double * x, size_t nr, int cosine, double * res, size_t * nNAentries, int * NAmean)
{
  *nNAentries = 0;
  size_t count = 0;
  LDOUBLE mean = 0, sum = 0;
  for (size_t k = 0; k < nr; k++)
    if (!ISNAN(x[k]))
    {
      mean += x[k];
      sum += ((LDOUBLE) x[k])*( (LDOUBLE) x[k]);
      count ++;
    }
  if (count > 0)
  {
    *NAmean = 0;
    *nNAentries = nr-count;
    if (cosine) mean = 0; else mean = mean/count;
    sum = sqrtl(sum - count * mean*mean);
    if (sum > 0)
    {
      // Rprintf("sum: %Le\n", sum);
       for (size_t k=0; k<nr; k++)
         if (!ISNAN(x[k]))
            res[k] = (x[k] - mean)/sum;
         else
            res[k] = 0;
    } else {
       // Rprintf("prepareColCor: have zero variance.\n");
       *NAmean = 1;
       for (size_t k=0; k<nr; k++) res[k] = 0;
    }
  } else {
    *NAmean = 1;
    *nNAentries = nr;
    for (size_t k=0; k<nr; k++)
       res[k] = 0;
  }
}
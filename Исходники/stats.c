/* print a sparse array distribution */
  void
print_sdist(struct stat_stat_t *stat,	/* stat variable */
    FILE *fd)			/* output stream */
{
  unsigned int i, bcount;
  md_addr_t imax, imin;
  double btotal, bsum, bvar, bavg, bsqsum;
  struct bucket_t *bucket;
  int pf = stat->variant.for_sdist.pf;

  /* count and sum entries */
  bcount = 0; btotal = 0.0; bvar = 0.0; bsqsum = 0.0;
  imax = 0; imin = UINT_MAX;
  for (i=0; i<HTAB_SZ; i++)
  {
    for (bucket = stat->variant.for_sdist.sarr[i];
        bucket != NULL;
        bucket = bucket->next)
    {
      bcount++;
      btotal += bucket->count;
      /* on-line variance computation, tres cool, no!?! */
      bsqsum += ((double)bucket->count * (double)bucket->count);
      bavg = btotal / (double)bcount;
      bvar = (bsqsum - ((double)bcount * bavg * bavg)) / 
        (double)(((bcount - 1) > 0) ? (bcount - 1) : 1);
      if (bucket->index < imin)
        imin = bucket->index;
      if (bucket->index > imax)
        imax = bucket->index;
    }
  }

  /* print header */

  fprintf(fd, "\n");
  fprintf(fd, "%-28s # %s\n", stat->name, stat->desc);
  fprintf(fd, "%s.count = %u\n", stat->name, bcount);
  fprintf(fd, "%s.total = %.0f\n", stat->name, btotal);
  if (bcount > 0)
  {
    myfprintf(fd, "%s.imin = 0x%p\n", stat->name, imin);
    myfprintf(fd, "%s.imax = 0x%p\n", stat->name, imax);
  }
  else
  {
    fprintf(fd, "%s.imin = %d\n", stat->name, -1);
    fprintf(fd, "%s.imax = %d\n", stat->name, -1);
  }
  fprintf(fd, "%s.average = %8.4f\n", stat->name, btotal/bcount);
  fprintf(fd, "%s.std_dev = %8.4f\n", stat->name, sqrt(bvar));
  fprintf(fd, "%s.overflows = 0\n", stat->name);

  fprintf(fd, "# pdf == prob dist fn, cdf == cumulative dist fn\n");
  fprintf(fd, "# %14s ", "index");
  if (pf & PF_COUNT)
    fprintf(fd, "%10s ", "count");
  if (pf & PF_PDF)
    fprintf(fd, "%6s ", "pdf");
  if (pf & PF_CDF)
    fprintf(fd, "%6s ", "cdf");
  fprintf(fd, "\n");

  fprintf(fd, "%s.start_dist\n", stat->name);

  if (bcount > 0)
  {
    unsigned int bindex;
    struct bucket_t **barr;

    /* collect all buckets */
    barr = (struct bucket_t **)calloc(bcount, sizeof(struct bucket_t *));
    if (!barr)
      fatal("out of virtual memory");
    for (bindex=0,i=0; i<HTAB_SZ; i++)
    {
      for (bucket = stat->variant.for_sdist.sarr[i];
          bucket != NULL;
          bucket = bucket->next)
      {
        barr[bindex++] = bucket;
      }
    }

    /* sort the array by index */
    qsort(barr, bcount, sizeof(struct bucket_t *), (int (*)(const void*, const void*))compare_fn);

    /* print the array */
    bsum = 0.0;
    for (i=0; i<bcount; i++)
    {
      bsum += (double)barr[i]->count;
      if (stat->variant.for_sdist.print_fn)
      {
        stat->variant.for_sdist.print_fn(stat,
            barr[i]->index,
            barr[i]->count,
            bsum,
            btotal);
      }
      else
      {
        if (stat->format == NULL)
        {
          myfprintf(fd, "0x%p ", barr[i]->index);
          if (pf & PF_COUNT)
            fprintf(fd, "%10u ", barr[i]->count);
          if (pf & PF_PDF)
            fprintf(fd, "%6.2f ",
                (double)barr[i]->count/MAX(btotal, 1.0) * 100.0);
          if (pf & PF_CDF)
            fprintf(fd, "%6.2f ", bsum/MAX(btotal, 1.0) * 100.0);
        }
        else
        {
          if (pf == (PF_COUNT|PF_PDF|PF_CDF))
          {
            myfprintf(fd, stat->format,
                barr[i]->index, barr[i]->count,
                (double)barr[i]->count/MAX(btotal, 1.0)*100.0,
                bsum/MAX(btotal, 1.0) * 100.0);
          }
          else if (pf == (PF_COUNT|PF_PDF))
          {
            myfprintf(fd, stat->format,
                barr[i]->index, barr[i]->count,
                (double)barr[i]->count/MAX(btotal, 1.0)*100.0);
          }
          else if (pf == PF_COUNT)
          {
            myfprintf(fd, stat->format,
                barr[i]->index, barr[i]->count);
          }
          else
            fatal("distribution format not yet implemented");
        }
        fprintf(fd, "\n");
      }
    }

    /* all done, release bucket pointer array */
    free(barr);
  }

//  fprintf(fd, "%s.end_dist\n", stat->name);
}
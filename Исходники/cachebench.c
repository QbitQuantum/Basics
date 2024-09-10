double benchmark_cache_ronly(REGISTER DATATYPE *x, REGISTER long limit, long *oloops, double *ous)
{
  REGISTER long index = 0, loops = 0;
  REGISTER DATATYPE sum = (DATATYPE)0;

  FLUSHALL(1);
  keepgoing = 1;
  assert(signal(SIGALRM,handler) != SIG_ERR);

  alarm(duration);
  TIMER_START;

#ifdef SOLARIS
  while (go(-1))
#else
  while (keepgoing)
#endif  
    {
      for  (index = 0; index < limit; index++)
	{
	  sum += x[index];
	}
      loops++;
    }

  TIMER_STOP;

  x[0] = (DATATYPE)sum;
  x[1] = (DATATYPE)index;
  fake_out_optimizations(x,2*sizeof(DATATYPE));

  *oloops = loops;
  *ous = TIMER_ELAPSED;
  {
    double refcnt = ((double)loops*(double)limit);
    DBG(fprintf(stderr,"T: %ld loops at limit %ld took %f us, %f refs.\n",loops,limit,*ous,refcnt));
    return(refcnt);
  }
}
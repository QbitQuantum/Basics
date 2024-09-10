/** synchronises sizea and content of output histograms */
int mpi_sync_maxminlen_final(void)
{
  long i, j, len, dlen ;
  double gap ;
  long *tmp = NULL ;
  long  total;

  pp_max = NULL ;
  pp_min = NULL ;
  pp_o_len = NULL;
  
  if ((pp_max = (double*)malloc(num_ovars*sizeof(double)))==NULL) { goto memFree; }
  if ((pp_min = (double*)malloc(num_ovars*sizeof(double)))==NULL) { goto memFree; }
  if ((pp_o_len = (long*)malloc(num_ovars*sizeof(long)))==NULL) { goto memFree; }

  for (i=0; i<num_ovars; i++)
  {
    o_tst_min[i] = o_his[i].min;
    o_tst_max[i] = o_his[i].max;
    o_tst_len[i] = o_his[i].len;
  }

  MPI_Allreduce(o_tst_min, pp_min, num_ovars,MPI_DOUBLE,MPI_MIN,MPI_COMM_WORLD);
  MPI_Allreduce(o_tst_max, pp_max, num_ovars,MPI_DOUBLE,MPI_MAX,MPI_COMM_WORLD);
  MPI_Allreduce(o_tst_len, pp_o_len, num_ovars,MPI_LONG,MPI_MAX,MPI_COMM_WORLD);

  for (i=0; i<num_ovars; i++)
  {
    if (o_tst_type[i] > H_OUT_NONE)
    {
      if ((o_tst_type[i] != H_OUT_AUTO)
        && (o_tst_type[i] != H_OUT_AUTO_NUM)
        && (o_tst_type[i] != H_OUT_LIMS))
      {
      
#if 1
      if ((pp_o_len[i] != o_his[i].len)
        ||(pp_min[i] != o_his[i].min)
        ||(pp_max[i] != o_his[i].max))
#endif
        {
          gap = (o_his[i].max-o_his[i].min) / ((double)o_his[i].len) ;
#ifdef REPLACE_RINTL
          len = monte_round( ((pp_max[i]-pp_min[i]) / gap), M_ROUND) ;
#else
          len = rintl((pp_max[i]-pp_min[i]) / gap) ;
#endif
        
          /* reallocate to this size, fill this size */
          if ((tmp = ((long *)malloc(len*sizeof(long))))==NULL) {continue;}
          for (j=0; j<len; j++) {tmp[j] = 0;}

          if (pp_min[i] < o_his[i].min)
#ifdef REPLACE_RINTL
              { dlen = monte_round( (fabs((pp_min[i]-o_his[i].min)/gap)), M_ROUND) ; }
#else
              { dlen = rintl(fabs((pp_min[i]-o_his[i].min)/gap)) ; }
#endif
          else { dlen = 0 ; }

          for (j=0; j<o_his[i].len; j++)
          {
            tmp[j+dlen] = o_his[i].data[j] ;
          }
          free(o_his[i].data) ;
          o_his[i].data = tmp ;
          tmp = NULL ;

          o_his[i].max = pp_max[i];
          o_his[i].min = pp_min[i];
          o_his[i].len = len ;
        }
      }

      tmp = NULL;
      /* for all types of histograms: */
      if ((tmp = ((long *)malloc(o_his[i].len*sizeof(long))))==NULL) {continue;}
      for (j=0; j<o_his[i].len; j++) {tmp[j] = o_his[i].data[j];}

      MPI_Reduce(tmp, o_his[i].data,o_his[i].len,MPI_LONG,MPI_SUM,0,MPI_COMM_WORLD);
      free(tmp); tmp=NULL;
      total = o_his[i].total;
      MPI_Reduce(&total, &o_his[i].total,1,MPI_LONG,MPI_SUM,0,MPI_COMM_WORLD);
    }
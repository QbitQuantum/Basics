void rf3_pg(double *po, double *pr, int npeaks, double lfm, double l_ult, double uc_mult)
{
  // assumes po has storage for the 5 by npeaks array
  // pr are the peaks, is length npeaks
    double a[16384], range, mean, adj_range, lfmargin, adj_zero_mean_range;
    int tot_num, index, j, cNr;

    lfmargin = l_ult - fabs(lfm);
    tot_num = npeaks;
    //    printf ("in rf3_pg, tot_num = %d\n", tot_num);

    j = -1;
    cNr = 1;
    for (index=0; index<tot_num; index++) 
      {
        a[++j]=*pr++;
        while ( (j >= 2) && (fabs(a[j-1]-a[j-2]) <= fabs(a[j]-a[j-1])) ) 
	  {
            range=fabs(a[j-1]-a[j-2]);
            switch(j)
	      {
	      case 0: { break; }
	      case 1: { break; }
	      case 2: {
		mean=(a[0]+a[1])/2;
		adj_range = range * lfmargin / ( l_ult - fabs(mean) );
		adj_zero_mean_range = range * l_ult / ( l_ult - fabs(mean) );
		a[0]=a[1];
		a[1]=a[2];
		j=1;
		if (range > 0) {
		  *po++=range;
		  *po++=mean;
		  *po++=adj_range;
		  *po++=uc_mult;
		  *po++=adj_zero_mean_range;
		}
		break;
	      }
	      default: {
		mean=(a[j-1]+a[j-2])/2;
		adj_range = range * lfmargin / ( l_ult - fabs(mean) );
		adj_zero_mean_range = range * l_ult / ( l_ult - fabs(mean) );
		a[j-2]=a[j];
		j=j-2;
		if (range > 0) {
		  *po++=range;
		  *po++=mean;
		  *po++=adj_range;
		  *po++=1.00;
		  *po++=adj_zero_mean_range;
		  cNr++;
		}
		break;
	      }
	      }
	  }
      }
    for (index=0; index<j; index++) 
      {
	range=fabs(a[index]-a[index+1]);
	mean=(a[index]+a[index+1])/2;
	adj_range = range * lfmargin / ( l_ult - fabs(mean) );
	adj_zero_mean_range = range * l_ult / ( l_ult - fabs(mean) );
	if (range > 0)
	  {
	    *po++=range;
	    *po++=mean;
	    *po++=adj_range;
	    *po++=uc_mult;
	    *po++=adj_zero_mean_range;
	  }
      }
    //    printf ("exiting rf3_pg\n");
}
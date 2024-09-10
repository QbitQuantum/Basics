void score_setup()
{
	int i,u;
    //weight_time_setup();
	if(load_model) {
		fpV=fopen(fnameV,"rb");
		fpU=fopen(fnameU,"rb");
		if(fpV || fpU) {
			lg("Loading %s and %s\n",fnameV,fnameU);
			if(!fpV || !fpU)
				error("Cant open both files");
		}
	}

    int day0[NMOVIES];
    ZERO(day0);
    // It is OK to look on all data for day0 because it is always known
    for(i=0;i<NENTRIES;i++) {
        int m=userent[i]&USER_MOVIEMASK;
        int day=userent[i]>>(USER_LMOVIEMASK+3);
        if(!day0[m] || day0[m]>day) day0[m]=day;
    }
    DEVuHat = (float *) malloc(NENTRIES*sizeof(float));
    sdbU    = (float *) malloc(NENTRIES*sizeof(float));
    sdsU    = (float *) malloc(((unsigned int)NENTRIES)*((unsigned int)NFEATURES)*sizeof(float));
	memset(DEVuHat,0,NENTRIES*sizeof(float));
	memset(sdbU,0,NENTRIES*sizeof(float));
	memset(sdsU,0,((unsigned int)NENTRIES)*((unsigned int)NFEATURES)*sizeof(float));
	ZERO(sdbin);

	int tcount[100000];
	ZERO(tcount);
	ZERO(avgdate);
	ZERO(avgdevu);
	ZERO(ucnt);
	int j;
    for(u=0;u<NUSERS;u++) {
        int base=useridx[u][0];
        int d012=UNALL(u);
        int d0=UNTRAIN(u);
        // compute explanatory variable
        for(j=0;j<d012;j++) {
            int m=userent[base+j]&USER_MOVIEMASK;
            int day=userent[base+j]>>(USER_LMOVIEMASK+3);
			if ( day < minday ) 
				minday = day;
			if ( day > maxday ) 
				maxday = day;
            //usertime[j]=DTIME(day-day0[m]);
			if ( day < 0 )
				;//toosmall++;
			else if ( day < 100000-1 )
			    tcount[day]++;
			else 
				;//toobig++;
			ucnt[u]++;
			avgdate[u] += day;
        }
    }
	printf("minday: %d, maxday: %d\n", minday, maxday);
	fflush(stdout);
    for(u=0;u<NUSERS;u++) {
        // 1) Find the average date of rating for every customer. In this step I include the probe dates also in the calculation of the average.
		avgdate[u] /= ucnt[u];
	    //printf("U: %d, avgdate: %f, ucnt: %d\n", u, avgdate[u], ucnt[u]);
		//fflush(stdout);
	}
    for(u=0;u<NUSERS;u++) {
        int base=useridx[u][0];
        int d012=UNALL(u);
        int d0=UNTRAIN(u);
        int j;
        for(j=0;j<d012;j++) {
            int m=userent[base+j]&USER_MOVIEMASK;
            int day=userent[base+j]>>(USER_LMOVIEMASK+3);
  			//2) For every rating [i] in the data set (including probe) I calculate DEVu[i]:
      		//   DEVu[i] = sign(t[i] - t_mean_for_customer) * powf(abs(t[i] - t_mean_for_customer), 0.4);
			double DEVu = sign(day - avgdate[u]) * powf(abs(day - avgdate[u]), 0.4);
			avgdevu[u] += DEVu;
	        //printf("U: %d, M: %d, day: %d, uavg: %f, DEVu: %f\n", u, m, day, avgdate[u], DEVu);
		    //fflush(stdout);

        }
    }
    for(u=0;u<NUSERS;u++) {
        //3) Find the average DEVu[i] for every customer. His/hers probe DEVu[i] values are also included.
		avgdevu[u] /= ucnt[u];
	    //printf("U: %d, avgdevu: %f, avgdate: %f, ucnt: %d\n", u, avgdevu[u], avgdate[u], ucnt[u]);
		//fflush(stdout);
	}
	ZERO(maxDEVuHat);
    for(u=0;u<NUSERS;u++) {
        int base=useridx[u][0];
        int d012=UNALL(u);
        int d0=UNTRAIN(u);
        int j;
        for(j=0;j<d012;j++) {
            int m=userent[base+j]&USER_MOVIEMASK;
            int day=userent[base+j]>>(USER_LMOVIEMASK+3);

  			//  2) For every rating [i] in the data set (including probe) I calculate DEVu[i]:
      		//     DEVu[i] = sign(t[i] - t_mean_for_customer) * powf(abs(t[i] - t_mean_for_customer), 0.4);
			double DEVu = sign(day - avgdate[u]) * powf(abs(day - avgdate[u]), 0.4);

            //  4) Subtract every customer's average DEVu_avg value from every time deviation:
            //     DEVu_hat[i] = DEVu[i] - DEVu_avg_for_customer;
            double DEVuHat = DEVu - avgdevu[u];

	        //printf("U: %d, M: %d, ndevu: %f, day: %d, uavg: %f, DEVu: %f\n", u, m, DEVuHat, day, avgdate[u], DEVu);
		    //fflush(stdout);

	    	// Get the max absolute value of a user's devu_hat values...maxDevu_hat...
			double tDEVu = fabs(DEVuHat);
			if ( tDEVu > maxDEVuHat[u] )
				maxDEVuHat[u] = tDEVu;
        }
    }
	
	// Compute and store DEVuHats and create single day bin numbering per user
	int daysBinValue[maxday+1];
    for(u=0;u<NUSERS;u++) {
        int base=useridx[u][0];
        int d012=UNALL(u);
        int d0=UNTRAIN(u);
        int j;
		ZERO(daysBinValue);
		int dcount=0;
        for(j=0;j<d012;j++) {
            int m=userent[base+j]&USER_MOVIEMASK;
            int day=userent[base+j]>>(USER_LMOVIEMASK+3);

            DEVuHat[base+j] = devuHat(day,u);

			if ( daysBinValue[day] == 0 ) {
				sdbin[base+j] = base+j;
			    daysBinValue[day] = base+j;
				if ( daysBinValue[day] > NENTRIES ) {
					printf("Days bin v: %d\n", daysBinValue[day]);
					fflush(stdout);
				}
				dcount++;
			} else {
				if ( daysBinValue[day] > NENTRIES ) {
					printf("Days bin v: %d\n", daysBinValue[day]);
					fflush(stdout);
				}
				sdbin[base+j] = daysBinValue[day];
			}
        }
    }

	//for (i=minday; i < maxday; i++ ) {
	    //printf("day: %d, count: %d\n", i, tcount[i]);
		//fflush(stdout);
	//}

}
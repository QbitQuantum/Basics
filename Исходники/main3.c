void *cal_thread(void *p)
{
	/*
	int *ips = (int *)p;
	sscanf(p->id, "%d", ip);
	*/
	int ic;
	int jc;
	int kc;
	int ip;
	int ii;
	int im;
	unsigned int WriteLen;
	unsigned long looptmp;
	unsigned long loop;
	unsigned long maxi;
	int counter=0;
	THREADS_STRUCT *pt = (THREADS_STRUCT *)p;
	double sum=0.0;
	double Totalrealsec=0.0;
	double Totaliorealsec=0.0;
	double Totalsec=0.0;
	double Totalmemsize=0.0;
	double *b;
	struct timeval startTime, endTime, ioTime;
	clock_t startClock, endClock, ioClock;

	ip      = pt->id;
	looptmp = pt->loop;
	maxi    = pt->maxi;
#ifdef DEBUG
	printf(" looptmp = %ld , ip = %d \n",looptmp,ip);
	printf(" maxi    = %ld , ip = %d \n",maxi,ip);
	printf(" maxi pt = %ld , ip = %d \n",pt->maxi,ip);
#endif
	Totalrealsec   = 0.0;
	Totaliorealsec = 0.0;
	Totalsec       = 0.0;
	Totalmemsize   = 0.0;

	if(looptmp == 0){
		loop = 10000000;
	} else {
		loop = looptmp;
	}
	for(ii = 0 ;ii < loop ; ii++){

#ifdef DEBUG
	printf(" ii = %d ,ip = %d \n",ii,ip);
	printf(" loop = %ld ,ip = %d \n",loop,ip);
	printf(" maxi = %ld ,ip = %d \n",maxi,ip);
#endif
		sum = 0.0;

		gettimeofday(&startTime, NULL);
		startClock = clock();

		if(maxi < 3){
			maxi = 4;
		}
		for(im = (maxi-1);im<maxi;im++){
			b = (double *)malloc((sizeof(double))*im*im*im);
			if( b == NULL) {
				err(EXIT_FAILURE, "can not create thread 2" );
			}
				
			for(ic=0;ic<im;ic++){
				for(jc=0;jc<im;jc++){
					for(kc=0;kc<im;kc++){
						b[ic*jc*kc] = 0.0; 
					}
				}
			}
			for(ic=0;ic<im;ic++){
				b[ic] = 1.0; 
			}
			for(ic=1;ic<(im-1);ic++){
				for(jc=1;jc<(im-1);jc++){
					for(kc=1;kc<(im-1);kc++){
						sum = sum + (b[ic*jc*kc] + b[(ic-1)*jc*kc] + b[(ic+1)*jc*kc] 
						                     	+ b[ic*(jc-1)*kc] + b[ic*(jc+1)*kc] 
                                                                     	+ b[ic*jc*(kc-1)] + b[ic*jc*(kc+1)] 
                                                    	)/7.0; 
					}
				}
			}
			for(ic=0;ic<im;ic++){
				b[ic] = sum; 
			}
	
			gettimeofday(&ioTime, NULL);
			ioClock = clock();
	
			if(pt->arg1 == 1){
				WriteLen = (int)((im*im*im)-1);
				fwrite((char *)b,sizeof(char),WriteLen,pt->fp);
				fseek(pt->fp,  0L, SEEK_SET);
			}

			free(b);
		}
		gettimeofday(&endTime, NULL);
		endClock = clock();
	
		time_t diffsec = difftime(endTime.tv_sec, startTime.tv_sec);
		suseconds_t diffsub = endTime.tv_usec - startTime.tv_usec;
		if (diffsub < 0) {
			diffsec -= 1;
			diffsub = 1000000 + diffsub;
		}
		double realsec = diffsec+diffsub*1e-6;
		double cpusec = (endClock - startClock)/(double)CLOCKS_PER_SEC;
		double percent = 100.0*cpusec/realsec;
	
		time_t iodiffsec = difftime(endTime.tv_sec, ioTime.tv_sec);
		suseconds_t iodiffsub = endTime.tv_usec - ioTime.tv_usec;
		if (iodiffsub < 0) {
			iodiffsec -= 1;
			iodiffsub = 1000000 + iodiffsub;
		}
		double iorealsec = iodiffsec+iodiffsub*1e-6;
		double iocpusec = (endClock - ioClock)/(double)CLOCKS_PER_SEC;
		double iopercent = 100.0*iocpusec/iorealsec;

		Totalrealsec   += realsec;
		Totaliorealsec += iorealsec;
		Totalsec       += realsec+ iorealsec;
		Totalmemsize   += im;

		counter++;
	}
	printf("******************************** \n");
	printf("**** Real Time  %f      s\n", Totalrealsec);
	printf("**** I/O  Time  %f byte/s\n", Totalmemsize*Totalmemsize*Totalmemsize/Totaliorealsec);
	printf("**** Ave.       %f      s\n", Totalrealsec/counter);
	printf("******************************** \n");

#ifdef DEBUG
	printf(" write start WriteLen = %d ,ip = %d \n",pt->WriteLen,ip);
#endif
	return 0;
}
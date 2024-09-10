//uint64_t spIndex=0;
int generateSP(void **arg)
{
	char *bin=(char *)arg[0];
	uint64_t THREAD_NUM=(uint64_t )arg[1];
	spSplit=(uint64_t *)calloc(THREAD_NUM,sizeof(uint64_t));
	spSplitCapacity=(uint64_t *)calloc(THREAD_NUM,sizeof(uint64_t));
	fusionNode=(uint64_t *)calloc(THREAD_NUM,sizeof(uint64_t));
	fusionMod=(uint64_t *)calloc(THREAD_NUM,sizeof(uint64_t));
	tempSP=(uint64_t **)calloc(THREAD_NUM,sizeof(uint64_t*));
	printf("the case3num is %lu\n", case3num);
	printf("the blueBoundNum is %lu\n", blueBoundNum);
	printf("the redCapacity is %lu\n", redCapacity);
	printf("the blueCapacity is %lu\n", blueCapacity);
	redSeq=(uint64_t *)calloc(redCapacity,sizeof(uint64_t));
	redPoint=(uint64_t *)calloc(redCapacity,sizeof(uint64_t));
	blueTable=(uint64_t *)calloc(blueCapacity,sizeof(uint64_t));
	char *redSeqPath=getPath(bin,"/redSeq");
	FILE *fpredSeq=fopen(redSeqPath,"rb");
	char *redPointPath=getPath(bin,"/redPoint");
	FILE *fpredPoint=fopen(redPointPath,"rb");
	if(fpredSeq==NULL||fpredPoint==NULL)
	{
		printf("fail to open the red file!\n");
		exit(1);
	}
	fread(redSeq,sizeof(uint64_t),redCapacity,fpredSeq);
	fread(redPoint,sizeof(uint64_t),redCapacity,fpredPoint);
	fclose(fpredSeq);
	fclose(fpredPoint);
	remove(redPointPath);
	remove(redSeqPath);
	free(redPointPath);
	free(redSeqPath);
	uint64_t i;
	for(i=1;i<BLACKCAPACITY;i++)
	{
		if(blackTable[i]==0)
		{
			blackTable[i]=blackTable[i-1];
		}
	}	
	//////////////////////////////go through reference////////////////////////////////////
	char *refPath=getPath(bin,"/reference");
	FILE *fpRef=fopen(refPath,"rb");
	if(fpRef==NULL)
	{
		printf("fail to open the ref file\n");
		exit(1);	
	}
	reference=(uint64_t *)calloc(compress_length,sizeof(uint64_t)); 
	fread(reference,sizeof(uint64_t),compress_length,fpRef);
	fclose(fpRef);
	remove(refPath);
	free(refPath);
	////////////////////////////////////////////////////////////////////////////////////////////////
	char *specialBranchPath=getPath(bin,"/specialBranch");
	FILE *fpSB=fopen(specialBranchPath,"rb");
	specialBranch=(uint64_t *)calloc(specialBranchNum,sizeof(uint64_t));
	if(fpSB==NULL)
	{
		printf("fail to open the specialBranch file\n");
		exit(1);	
	}
	/* replaced by binary file
	for(i=0;i<specialBranchNum;i++)
	{
		fscanf(fpSB,"%lu",&specialBranch[i]);
	}
	*/
	fread(specialBranch,sizeof(uint64_t),specialBranchNum,fpSB);
	fclose(fpSB);
	remove(specialBranchPath);
	free(specialBranchPath);
	qsort(specialBranch,specialBranchNum,sizeof(uint64_t),ascend);
	specialSA=(uint64_t *)calloc(countRead,sizeof(uint64_t));
	char *specialSAPath=getPath(bin,"/specialSA");
	FILE *fpSpecialSA=fopen(specialSAPath,"rb");
	if(fpSpecialSA==NULL)
	{
		printf("fail to open the specialBranch file\n");
		exit(1);	
	}
	fread(specialSA,sizeof(uint64_t),countRead,fpSpecialSA);
	fclose(fpSpecialSA);
	remove(specialSAPath);
	free(specialSAPath);
	///////////////////////////////////split the ref first//////////////////////////////////////////
	splitIndex=(uint64_t *)calloc(THREAD_NUM+1,sizeof(uint64_t));
	splitIndex[0]=0;
	splitIndex[THREAD_NUM]=BWTLEN;
	pthread_t myThread[THREAD_NUM];
	for(i=1;i<THREAD_NUM;i++)
	{
		void **tt=(void **)calloc(2,sizeof(void *));
		tt[0]=(void *)i;
		tt[1]=(void *)THREAD_NUM;
		int check=pthread_create( &myThread[i-1], NULL, multiGenerateSplit, (void*)tt);
		if(check)
    	{
        	fprintf(stderr,"threadNum:%lu, Error - pthread_create() return code: %d\n",i,check);
        	exit(EXIT_FAILURE);
    	}
	}
	for(i=1;i<THREAD_NUM;i++)
	{
		pthread_join( myThread[i-1], NULL);
	}
	//////////////////////////////////multi-thread generate spcode////////////////////////////////////
	rwlockRed=(pthread_rwlock_t*)calloc(redCapacity,sizeof(pthread_rwlock_t));
	for(i=0;i<redCapacity;i++)
	{
		if(pthread_rwlock_init(&rwlockRed[i], NULL))
		{
			printf("fail to create rwlock %lu\n",i);
			exit(1);
		}	
	}
	for(i=0;i<THREAD_NUM;i++)
	{
		void **tt=(void **)calloc(2,sizeof(void *));
		tt[0]=(void *)i;
		tt[1]=(void *)bin;
		int check=pthread_create( &myThread[i], NULL, multiGenerateSP, (void*)tt);
		if(check)
    	{
        	fprintf(stderr,"threadNum:%lu, Error - pthread_create() return code: %d\n",i,check);
        	exit(EXIT_FAILURE);
    	}	
	}
	for(i=0;i<THREAD_NUM;i++)
	{
		pthread_join( myThread[i], NULL);
	}
	spSplitCapacity[0]=spSplit[0];
	for(i=1;i<THREAD_NUM;i++)
	{
		spSplitCapacity[i]=spSplit[i];
		spSplit[i]=spSplit[i]+spSplit[i-1];
	}
	free(rwlockRed);
	free(reference);
	free(specialSA);
	free(specialBranch);
	free(redSeq);
	free(redPoint);
	free(blackTable);
	/////////////////////////////////add seg to the blue table and special sp index////////////////////
	for(i=1;i<THREAD_NUM;i++)
	{
		void **tt=(void **)calloc(2,sizeof(void *));
		tt[0]=(void *)i;
		tt[1]=(void *)bin;
		int check=pthread_create( &myThread[i], NULL, multiAddSeg, (void*)tt);
		if(check)
    	{
        	fprintf(stderr,"threadNum:%lu, Error - pthread_create() return code: %d\n",i,check);
        	exit(EXIT_FAILURE);
    	}	
    	//pthread_join( myThread[i], NULL);
	}
	for(i=1;i<THREAD_NUM;i++)
	{
		pthread_join( myThread[i], NULL);
	}
	char *spSpecialIndexPath=getPath(bin,"/spSpecialIndex");
	FILE *fpspSpecial=fopen(spSpecialIndexPath,"wb");
	free(spSpecialIndexPath);
	spSpecialIndexPath=getPath(bin,"/spSpecialIndex0");
	FILE *fpspSpecial0=fopen(spSpecialIndexPath,"rb");
	uint64_t *readBuf=(uint64_t *)calloc(BUFFERSIZE,sizeof(uint64_t)),bufReadNum;
	while((bufReadNum=fread(readBuf,sizeof(uint64_t),BUFFERSIZE,fpspSpecial0))>0)
	{
		fwrite(readBuf,sizeof(uint64_t),bufReadNum,fpspSpecial);
	}
	remove(spSpecialIndexPath);
	free(spSpecialIndexPath);
	fclose(fpspSpecial0);
	for(i=1;i<THREAD_NUM;i++)
	{
		char cNum[4];
		sprintf(cNum,"%lu",i);
		char spSpecialName[30]="/spSpecialIndexAdded";
		strcat(spSpecialName,cNum);
		spSpecialIndexPath=getPath(bin,spSpecialName);
		fpspSpecial0=fopen(spSpecialIndexPath,"rb");
		while((bufReadNum=fread(readBuf,sizeof(uint64_t),BUFFERSIZE,fpspSpecial0))>0)
		{
			fwrite(readBuf,sizeof(uint64_t),bufReadNum,fpspSpecial);
		}
		remove(spSpecialIndexPath);
		free(spSpecialIndexPath);
		fclose(fpspSpecial0);
	}
	fclose(fpspSpecial);
	free(readBuf);
       	//////////////////////////connect the sp codes///////////////////////////////////////////////
	spCodeLen=spSplit[THREAD_NUM-1];
	spCodeLen+=32;
    uint64_t spCodeSpace=spCodeLen>>5;
    uint64_t spLenMod=spCodeLen&MOD32;
    if(spLenMod) spCodeSpace++;
    spCode=(uint64_t *)calloc(spCodeSpace,sizeof(uint64_t));
	spSpecialIndexPath=getPath(bin,"/SPcode0");
	fpspSpecial=fopen(spSpecialIndexPath,"rb");//just used as temp paramater.
	uint64_t capacity0=spSplitCapacity[0];
	uint64_t space0=capacity0>>5;
	if((capacity0&MOD32)!=0) space0++;
	bufReadNum=fread(spCode,sizeof(uint64_t),space0,fpspSpecial);
	remove(spSpecialIndexPath);
	free(spSpecialIndexPath);
	if(bufReadNum!=space0) fprintf(stderr,"alert! bufReadNum=%lu, space0=%lu\n",bufReadNum,space0 ),exit(1);
	fclose(fpspSpecial);
	fusionNode[0]=spCode[space0-1];
	fusionMod[0]=capacity0&MOD32;
	for(i=1;i<THREAD_NUM;i++)
	{
		void **tt=(void **)calloc(2,sizeof(void *));
		tt[0]=(void *)i;
		tt[1]=(void *)bin;
		int check=pthread_create( &myThread[i], NULL, multiCatSP, (void*)tt);
		if(check)
    	{
        	fprintf(stderr,"threadNum:%lu, Error - pthread_create() return code: %d\n",i,check);
        	exit(EXIT_FAILURE);
    	}	
	}
	for(i=1;i<THREAD_NUM;i++)
	{
		pthread_join( myThread[i], NULL);
	}
	for(i=1;i<THREAD_NUM;i++)
	{
		void **tt=(void **)calloc(2,sizeof(void *));
		tt[0]=(void *)i;
		tt[1]=(void *)bin;
		int check=pthread_create( &myThread[i], NULL, multiConnect, (void*)tt);
		if(check)
    	{
        	fprintf(stderr,"threadNum:%lu, Error - pthread_create() return code: %d\n",i,check);
        	exit(EXIT_FAILURE);
    	}
	}
	for(i=1;i<THREAD_NUM;i++)
	{
		pthread_join( myThread[i], NULL);
	}
	uint64_t space=spSplit[THREAD_NUM-1]>>5;
	spCode[space]=fusionNode[THREAD_NUM-1];	
	free(spSplit);
	free(spSplitCapacity);
	free(fusionNode);
	free(fusionMod);
	return 1;
}
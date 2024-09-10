void  nandflash_sb_setup(struct nandflash_device* dev)
{
	uint8 flag=0xFF;
	int len,start,needinit=0;
	struct stat statbuf;
	struct nandflash_sb_status *nf;
	int i;
	nf=(struct nandflash_sb_status *)malloc(sizeof(struct nandflash_sb_status));
	if (nf==NULL) 
	{
		printf("error malloc nandflash_sb_status!\n");
       	skyeye_exit(-1);
	}
	dev->poweron=nandflash_sb_poweron;
	dev->readdata=nandflash_sb_readdata;
	dev->readio=nandflash_sb_readio;
	dev->readRB=nandflash_sb_readRB;
	dev->reset=nandflash_sb_reset;
	dev->sendaddr=nandflash_sb_sendaddr;
	dev->sendcmd=nandflash_sb_sendcmd;
	dev->senddata=nandflash_sb_senddata;
	dev->setALE=nandflash_sb_setALE;
	dev->setCE=nandflash_sb_setCE;
	dev->setCLE=nandflash_sb_setCLE;
	dev->setRE=nandflash_sb_setRE;
	dev->setWE=nandflash_sb_setWE;
	dev->setWP=nandflash_sb_setWP;
	memset(nf,0,sizeof(struct nandflash_sb_status));
#ifdef POSIX_SHARE_MEMORY_BROKEN
	nf->readbuffer=(uint8*)malloc(dev->pagedumpsize);
#endif
	nf->writebuffer=(uint8*)malloc(dev->pagedumpsize);
	//nf->memsize=528*32*4096;
       if ((nf->fdump= open(dev->dump, FILE_FLAG, S_IRUSR |S_IWUSR )) < 0)
       {
       	free(nf);
       	printf("error open nandflash dump!\n");
       	skyeye_exit(-1);
       }
	
       if (fstat(nf->fdump, &statbuf) < 0)   /* need size of input file */
       {
       	free(nf);
       	printf("error fstat function\n");
		skyeye_exit(-1);
       }
       if (statbuf.st_size<dev->devicesize)
       {
		printf("\nInit nandflash dump file.\n");
		needinit=1;
		start=statbuf.st_size;
		len=dev->devicesize-start;
		lseek(nf->fdump,dev->devicesize-1,SEEK_SET);
		write(nf->fdump,&flag,1);
#ifndef __MINGW32__
		fsync(nf->fdump);
#else
		_flushall();
#endif
       }
#ifndef POSIX_SHARE_MEMORY_BROKEN
       
	if (fstat(nf->fdump, &statbuf) < 0)   /* need size of input file */
       	{
       		free(nf);
       		printf("error fstat function\n");
				skyeye_exit(-1);
       	}

			printf("file size:%d\n",statbuf.st_size);
         if ((nf->addrspace= mmap(0, statbuf.st_size, PROT_READ | PROT_WRITE,
      		MAP_SHARED, nf->fdump, 0)) == MAP_FAILED)
      	{
      		free(nf);
      		printf("error mmap nandflash file\n");
		      skyeye_exit(-1);
      	}
      	if (needinit)
      	{
      		for(i=start;i<dev->devicesize;i++)
      		{
      			*(nf->addrspace+i)=flag;
      		}
      		if (!msync(nf->addrspace,dev->devicesize,MS_SYNC))
			printf("finish init nandflash dump\n");
		
      	}
		
 #else
   	nf->curblock=-1;
 	if (needinit)
 	{
 		memset(nf->readbuffer,0xff,dev->pagedumpsize);
 		lseek(nf->fdump,start,SEEK_SET);
 		while((dev->devicesize-start)>=dev->pagesize)
 		{
 		  write(nf->fdump,nf->readbuffer,dev->pagesize);
 		  start=start+dev->pagesize;
 		 }
 		 for (i=start;i<dev->devicesize;i++)
 		   write(nf->fdump,&flag,1);
 	}
 #endif
      	dev->priv=nf;
      	nandflash_sb_poweron(dev);
}
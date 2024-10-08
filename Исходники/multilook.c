int main(int argc, char *argv[])
{
  meta_parameters *meta, *meta_old, *meta_stat;
	char fnm1[BUF],fnm2[BUF],fnm3[BUF],fnm4[BUF];
	char imgfile[BUF],metaFile[BUF],cmd[BUF],metaIn[BUF],metaOut[BUF];
	FILE *fiamp, *fiphase, *foamp, *fophase, *flas;
	int ll=0, ls=1;   /* look line and sample */
	int sl=STEPLINE, ss=STEPSAMPLE;   /* step line and sample */
	int i,line, sample;
	int row, col, ampFlag = 0;
	long long nitems, newitems, inWid, inLen, outWid, outLen;
	long long ds/*,samplesRead*/;       /* input data size, number of samples read so far.*/
	long long red_offset, grn_offset, blu_offset;
	register float *ampIn, *phaseIn, ampScale;
	float *ampOut, *phaseOut,*ampBuf,Sin[256],Cos[256];
	float avg, percent=5.0;
	RGBDATA *table, *imgData;
	Uchar *redPtr, *grnPtr, *bluPtr;
	complexFloat z;
	struct DDR newddr;
	register float tmp,zImag,zReal,ampI;
	register int index,offset;
	const float convers=256.0/(2*3.14159265358979);
   
	logflag = 0;

  /* parse command line */
  while (currArg < (argc-2)) {
    char *key = argv[currArg++];
    if (strmatch(key,"-log")) {
      CHECK_ARG(1);
      strcpy(logFile,GET_ARG(1));
      fLog = FOPEN(logFile, "a");
      logflag = 1;
    }
    else if (strmatch(key,"-look")) {
      CHECK_ARG(1);
      if (2!=sscanf(GET_ARG(1),"%dx%d",&ll,&ls)) {
        printf("   ***ERROR: -look '%s' does not look like line x sample (e.g. '10x2').\n",GET_ARG(1));
        usage(argv[0]);
      }
    }
    else if (strmatch(key,"-step")) {
      CHECK_ARG(1);
      if (2!=sscanf(GET_ARG(1),"%dx%d",&sl,&ss)) {
        printf("   ***ERROR: -step '%s' does not look like line x sample (e.g. '5x1').\n",GET_ARG(1));
        usage(argv[0]);
      }
    }
    else if (strmatch(key,"-meta")) {
      CHECK_ARG(1);
      if (1!=sscanf(GET_ARG(1),"%s",metaFile)) {
        printf("   ***ERROR: Could not open '%s'.\n",GET_ARG(1));
        usage(argv[0]);
      }
      strcat(metaFile, "");
      ls = ss = 1;
      ll = sl = lzInt(metaFile, "sar.look_count:", NULL);
    }
    else if (strmatch(key,"-amplitude")) {
      printf("   Will remove amplitude part of color image\n");
      ampFlag = 1;
    }
    else {printf("\n   ***Invalid option:  %s\n",argv[currArg-1]); usage(argv[0]);}
  }
  if ((argc-currArg) < 2) {printf("   Insufficient arguments.\n"); usage(argv[0]);}

	system("date");
	printf("Program: multilook\n\n");
	if (logflag) {
	  StartWatchLog(fLog);
	  printLog("Program: multilook\n\n");
	}

	/* Create filenames and open files for reading */
  	create_name(fnm1,argv[currArg],"_amp.img");
  	create_name(fnm2,argv[currArg],"_phase.img");
	meta_stat = meta_read(fnm1);
	meta_old = meta_read(fnm2);
	meta = meta_read(fnm2);
  	create_name(fnm3,argv[++currArg],"_amp.img");
  	create_name(fnm4,argv[currArg],"_phase.img");
  	create_name(imgfile,argv[currArg],"_rgb.img");
	create_name(metaOut,argv[currArg],"_rgb.meta");
 	
	inWid = meta->general->sample_count;
	inLen = meta->general->line_count;
  	meta->general->sample_count /= ss;
  	meta->general->line_count /= sl;
	outWid = meta->general->sample_count;
	outLen = meta->general->line_count;
  
	/* Create new metadata file for the amplitude and phase.*/
	meta->sar->line_increment = 1;
	meta->sar->sample_increment = 1;
	meta->sar->azimuth_time_per_pixel *= sl;
	meta->general->x_pixel_size *= ss;
	meta->general->y_pixel_size *= sl;
	create_name(metaIn,argv[currArg],"_amp.meta");
	meta_write(meta, metaIn);
	create_name(metaIn,argv[currArg],"_phase.meta");
	meta_write(meta, metaIn);

        meta2ddr(meta, &newddr);

	/* Create 3-band image's DDR.
	   Currently metadata file don't know anything about multiband imagery.
	   We will need to convert the current version for single band amplitude
	   image back to metadata version 0.9 and change a couple of values 
	sprintf(cmd, "convert_meta %s 1.3 %s 0.9", metaIn, metaOut);
	asfSystem(cmd);
        */
	
	newddr.dtype=EBYTE;
	newddr.nbands=3;
	c_putddr(imgfile,&newddr);
  
	fiamp = fopenImage(fnm1,"rb");
	fiphase = fopenImage(fnm2,"rb");
	foamp = fopenImage(fnm3,"wb");
	fophase = fopenImage(fnm4,"wb");
	flas = fopenImage(imgfile,"wb");

	/*
	* create data buffers 
	*/
	for (i=0;i<256;i++)
	{
		float phas=((float)i)/256.0*(2*3.14159265358979);
		Sin[i]=sin(phas);
		Cos[i]=cos(phas);
	}
  
	/* set data variables */
	ampScale = 1.0/(ll*ls);
	nitems   = (ll-sl)*inWid;
	newitems = sl*inWid;
  
	ds       = sizeof(float);
	ampIn    = (float *)MALLOC(ds*(newitems+nitems+ls));
	phaseIn  = (float *)MALLOC(ds*(newitems+nitems+ls));
	ampOut   = (float *)MALLOC(ds*outWid);
	ampBuf   = (float *)MALLOC(ds*outWid);
	phaseOut = (float *)MALLOC(ds*outWid);
	table    = (RGBDATA *)MALLOC(sizeof(RGBDATA)*MAXENTRIES);
	imgData  = (RGBDATA *)MALLOC(sizeof(RGBDATA)*outWid);
	redPtr   = (Uchar *)MALLOC(sizeof(Uchar)*outWid);
	grnPtr   = (Uchar *)MALLOC(sizeof(Uchar)*outWid);
	bluPtr   = (Uchar *)MALLOC(sizeof(Uchar)*outWid);
	
        /* calculate mean value */
        if (meta_stat->stats)
          avg = meta_stat->stats->band_stats[0].mean;
        else {
          sprintf(cmd, "stats -overmeta -overstat \"%s\"\n", fnm1);
          asfSystem(cmd);
          meta_free(meta_stat);
          meta_stat = meta_read(fnm1);
          avg = meta_stat->stats->band_stats[0].mean;
        }

	/* create a colortable to be used with c2i */
	colortable(table);
  
	/* start conversion */
/*	printf("   Skipping every %d col and %d row\n",ss,sl);
	printf("   Looking at every %d col and %d row\n",ls,ll);*/
  	printf("   Input is %lld lines by %lld samples\n",inLen,inWid);
	printf("   Ouput is %lld lines by %lld samples\n\n",outLen,outWid);
	if (logflag) {
  	  sprintf(logbuf, "   Input is %lld lines by %lld samples\n",inLen,inWid);
	  printLog(logbuf);
	  sprintf(logbuf, "   Ouput is %lld lines by %lld samples\n\n",outLen,outWid);
	  printLog(logbuf);
	}
 	
	/*
	* Run through all lines in which data needs to be read so that
	* amount of data will be equal to ll * inWid.
	*/
	for(line=0; line<outLen; line++)
	{

		/* Read in a ll*inWid size chunk */
		get_float_lines(fiamp, meta_old, line*sl, ll, ampIn);
		get_float_lines(fiphase, meta_old, line*sl, ll, phaseIn);

		/* begin adding data */
		for (sample=0; sample<outWid; sample++)
		{ 
			tmp = 0.0, zReal=0.0, zImag=0.0;
			/* add up looking area */
			for (col=0;col<ls;col++)
			{
				offset=sample*ss+col;
				for (row=0;row<ll;row++)
				{
					ampI=ampIn[offset];
					index=0xFF&((int)(phaseIn[offset]*convers));
					tmp += ampI * ampI;
					zReal += ampI * Cos[index];
					zImag += ampI * Sin[index];
					offset+=inWid;
 				}
			}
     
			/* get phase from complex values */
			z.real=zReal;
			z.imag=zImag;
			/* place in output buffer */
		/*	ampOut[sample] = sqrt(tmp*ampScale); */
			ampOut[sample] = Cabs(z)*ampScale; 
			phaseOut[sample] = Cphase(z);
			if(!ampFlag)
				ampBuf[sample]=ampOut[sample];
			else
				ampBuf[sample]=avg*1.5;		
		}
    
		/* convert amp & phase to RGB. */
		if (!c2i(ampBuf,phaseOut,imgData,table,outWid,avg))
			Exit("ml: Error in c2i()");

		/* write out data to file */
		put_float_line(foamp, meta, line, ampOut);
		put_float_line(fophase, meta, line, phaseOut);

		if ((line*100/outLen)>percent) {
			printf("   Completed %3.0f percent\n", percent);
			percent+=5.0;
		}
		
		for (i=0;i<outWid;i++)
		{
			redPtr[i] = imgData[i].red;
			grnPtr[i] = imgData[i].green;
			bluPtr[i] = imgData[i].blue;
		} 
		red_offset=(long long)(line*outWid);
		grn_offset=(long long)(line*outWid+outWid*outLen);
		blu_offset=(long long)(line*outWid+(2*outWid*outLen));

		FSEEK64(flas,red_offset,SEEK_SET);
		ASF_FWRITE(redPtr,1,outWid,flas);
		FSEEK64(flas,grn_offset,SEEK_SET);
		ASF_FWRITE(grnPtr,1,outWid,flas);
		FSEEK64(flas,blu_offset,SEEK_SET);
		ASF_FWRITE(bluPtr,1,outWid,flas);
    
		/* reposition data for next read */
		for (i=0;i<nitems;i++)
		{
			ampIn[i] = ampIn[i + newitems];
			phaseIn[i] = phaseIn[i + newitems];
		}
		
	}
  
	/* 
	* free up unneeded memory and prepare to write 
	* a 3 sequential band image
	*/
/*	printf("\n\tdone with multilook\n");
	printf("writing out LAS/RGB image file\n");*
	printf("   Completed 100 percent\n\n   Wrote %lld bytes of data\n\n", 
	       (long long)(outLen*outWid*4));
	if (logflag) {
	  sprintf(logbuf, "   Wrote %lld bytes of data\n\n", 
		  (long long)(outLen*outWid*4));
	  printLog(logbuf);
	  StopWatchLog(fLog);
	  FCLOSE(fLog);
	}
*/

	FREE(ampIn);
	FREE(phaseIn);
	FREE(ampOut);
        FREE(ampBuf);
	FREE(phaseOut);
	FREE(table);
	FCLOSE(fiamp);
	FCLOSE(fiphase);
	FCLOSE(foamp);
	FCLOSE(fophase);
  
	/* free all memory, close files, print out time elapsed */
	FREE(redPtr);
	FREE(grnPtr);
	FREE(bluPtr);
	FREE(imgData);
	FCLOSE(flas);

        meta_free(meta);
        meta_free(meta_stat);
        meta_free(meta_old);

	return 0;
}
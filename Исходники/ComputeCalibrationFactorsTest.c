int ReadFiles(struct CommandLineArgsTag CLA)
{
  char line[256];
  INT4 i;
  FILE *fpS,*fpR,*fpA,*fpSeg;
  REAL8 Cmag,Cphase,Rmag,Rphase,Amag,Aphase,freq,x,y;
  static COMPLEX16FrequencySeries R0;
  static COMPLEX16FrequencySeries C0;
  static COMPLEX16FrequencySeries A0;

  /* Allocate space for response and sensing functions; just enough to read first 1200Hz */
  LALZCreateVector( &status, &R0.data, MAXLINERS);
  LALZCreateVector( &status, &C0.data, MAXLINERS);
  LALZCreateVector( &status, &A0.data, MAXLINERS);

  /* Fill in R0, C0 data */
  R0.f0=0.0;
  R0.deltaF=1.0/64.0;                   /*ACHTUNG: HARDWIRED !!*/
  C0.f0=0.0;
  C0.deltaF=1.0/64.0;                   /*ACHTUNG: HARDWIRED !!*/
  A0.f0=0.0;
  A0.deltaF=1.0/64.0;                   /*ACHTUNG: HARDWIRED !!*/

 /* This is kinda messy... Unfortunately there's no good way of doing this */
 /* ------ Open and read Sensing file ------ */
 i=0;
 fpS=fopen(CLA.CFile,"r");
 if (fpS==NULL)
   {
     fprintf(stderr,"That's weird... %s doesn't exist!\n",CLA.CFile);
     return 1;
   }
 while(fgets(line,sizeof(line),fpS))
   {
     if(*line == '#') continue;
     if(*line == '%') continue;
     if (i > MAXLINERS-1)
       {
	 /* done reading file */
	 break;
       }
     sscanf(line,"%le %le %le",&freq,&Cmag,&Cphase);
     C0.data->data[i].re=Cmag*cos(Cphase);
     C0.data->data[i].im=Cmag*sin(Cphase);
     i++;
   }
 fclose(fpS);
 /* -- close Sensing file -- */

 /* ------ Open and read Response file ------ */
 i=0;
 fpR=fopen(CLA.RFile,"r");
 if (fpR==NULL)
   {
     fprintf(stderr,"That's weird... %s doesn't exist!\n",CLA.RFile);
     return 1;
   }
 while(fgets(line,sizeof(line),fpR))
   {
     if(*line == '#') continue;
     if(*line == '%') continue;
     if (i > MAXLINERS-1)
       {
	 /* done reading file */
	 break;
       }
     sscanf(line,"%le %le %le",&freq,&Rmag,&Rphase);
     R0.data->data[i].re=Rmag*cos(Rphase);
     R0.data->data[i].im=Rmag*sin(Rphase);
     i++;
   }
 fclose(fpR);
 /* -- close Sensing file -- */

 /* ------ Open and read Response file ------ */
 i=0;
 fpA=fopen(CLA.AFile,"r");
 if (fpA==NULL)
   {
     fprintf(stderr,"That's weird... %s doesn't exist!\n",CLA.AFile);
     return 1;
   }
 while(fgets(line,sizeof(line),fpA))
   {
     if(*line == '#') continue;
     if(*line == '%') continue;
     if (i > MAXLINERS-1)
       {
	 /* done reading file */
	 break;
       }
     sscanf(line,"%le %le %le",&freq,&Amag,&Aphase);
     A0.data->data[i].re=Amag*cos(Aphase);
     A0.data->data[i].im=Amag*sin(Aphase);
     i++;
   }
 fclose(fpA);
 /* -- close Sensing file -- */

 /* ------ Open and read Segment file ------ */
 i=0;
 fpSeg=fopen(CLA.SegmentsFile,"r");
 if (fpSeg==NULL)
   {
     fprintf(stderr,"That's weird... %s doesn't exist!\n",CLA.SegmentsFile);
     return 1;
   }
 while(fgets(line,sizeof(line),fpSeg))
   {
     if(*line == '#') continue;
     if(*line == '%') continue;
     if (i > MAXLINESEGS-1)
       {
	 fprintf(stderr,"Too many lines in file %s! Exiting... \n", CLA.SegmentsFile);
	 return 1;
       }
     sscanf(line,"%d %d %f",&SL[i].nseg,&SL[i].tgps,&SL[i].seglength);
     i++;
   }
 numsegs=i;
 fclose(fpSeg);
 /* -- close Sensing file -- */

  /* compute C0 and R0 at correct frequency */
  /* use linear interpolation */

  x = modf( CLA.f / R0.deltaF, &y );
  i = floor( y );
  Rf0.re  = ( 1 - x ) * R0.data->data[i].re;
  Rf0.re += x * R0.data->data[i].re;
  Rf0.im  = ( 1 - x ) * R0.data->data[i].im;
  Rf0.im += x * R0.data->data[i].im;
  x = modf( CLA.f / C0.deltaF, &y );
  i = floor( y );
  Cf0.re  = ( 1 - x ) * C0.data->data[i].re;
  Cf0.re += x * C0.data->data[i].re;
  Cf0.im  = ( 1 - x ) * C0.data->data[i].im;
  Cf0.im += x * C0.data->data[i].im;
  x = modf( CLA.f / A0.deltaF, &y );
  i = floor( y );
  Af0.re  = ( 1 - x ) * A0.data->data[i].re;
  Af0.re += x * A0.data->data[i].re;
  Af0.im  = ( 1 - x ) * A0.data->data[i].im;
  Af0.im += x * A0.data->data[i].im;

 /* create Frame cache */
 framecache = XLALCacheImport(CLA.FrCacheFile);
 LALFrCacheOpen(&status,&framestream,framecache);

 XLALDestroyCache(&framecache);

 LALZDestroyVector(&status,&R0.data);
 LALZDestroyVector(&status,&C0.data);
 LALZDestroyVector(&status,&A0.data);

 return 0;
}
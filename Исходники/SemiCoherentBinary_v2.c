/** Output the results to file
 *
 * We choose to output all results from a specific analysis to a single file
 *
 */
int XLALOpenSemiCoherentResultsFile(FILE **fp,                  /**< [in] filepointer to output file */
				    CHAR *outputdir,            /**< [in] the output directory name */
				    ParameterSpace *pspace,     /**< [in] the parameter space */
				    CHAR *clargs,               /**< [in] the command line args */
				    UserInput_t *uvar		/**< UNDOCUMENTED */
				    )
{
  CHAR outputfile[LONGSTRINGLENGTH];    /* the output filename */
  time_t curtime = time(NULL);          /* get the current time */
  CHAR *time_string = NULL;             /* stores the current time */
  CHAR *version_string = NULL;          /* pointer to a string containing the git version information */

  /* validate input */
  if (outputdir == NULL) {
    LogPrintf(LOG_CRITICAL,"%s: Invalid input, output directory string == NULL.\n",__func__);
    XLAL_ERROR(XLAL_EINVAL);
  }

  if (pspace == NULL) {
    LogPrintf(LOG_CRITICAL,"%s: Invalid input, ParameterSpace structure == NULL.\n",__func__);
    XLAL_ERROR(XLAL_EINVAL);
  }

  /* define the output filename */
  /* the format we adopt is the following SemiCoherentResults-<SOURCE>-<START>_<END>-<MIN_FREQ_INT>_<MIN_FREQ_mHZ>_ <MAX_FREQ_INT>_<MAX_FREQ_mHZ>.txt */
  {
    UINT4 min_freq_int = floor(pspace->space->data[0].min);
    UINT4 max_freq_int = floor(pspace->space->data[0].max);
    UINT4 min_freq_mhz = (UINT4)floor(0.5 + (pspace->space->data[0].min - (REAL8)min_freq_int)*1e3);
    UINT4 max_freq_mhz = (UINT4)floor(0.5 + (pspace->space->data[0].max - (REAL8)max_freq_int)*1e3);
    UINT4 end = (UINT4)ceil(XLALGPSGetREAL8(&(pspace->epoch)) + pspace->span);
    /* if (coherent) snprintf(outputfile,LONGSTRINGLENGTH,"%s/CoherentResults-%s-%d_%d-%04d_%03d_%04d_%03d.txt",
			   outputdir,(CHAR*)uvar->comment,pspace->epoch.gpsSeconds,end,min_freq_int,min_freq_mhz,max_freq_int,max_freq_mhz);
    else */
    snprintf(outputfile,LONGSTRINGLENGTH,"%s/SemiCoherentResults-%s-%d_%d-%04d_%03d_%04d_%03d.txt",
		  outputdir,(CHAR*)uvar->comment,pspace->epoch.gpsSeconds,end,min_freq_int,min_freq_mhz,max_freq_int,max_freq_mhz);
  }
  LogPrintf(LOG_DEBUG,"%s : output %s\n",__func__,outputfile);

  /* open the output file */
  if (((*fp) = fopen(outputfile,"w")) == NULL) {
    LogPrintf(LOG_CRITICAL,"%s: Error, failed to open file %s for writing.  Exiting.\n",__func__,outputfile);
    XLAL_ERROR(XLAL_EINVAL);
  }

  /* Convert time to local time representation */
  {
    struct tm *loctime = localtime(&curtime);
    CHAR *temp_time = asctime(loctime);
    UINT4 n = strlen(temp_time);
    time_string = XLALCalloc(n,sizeof(CHAR));
    snprintf(time_string,n-1,"%s",temp_time);
  }

  /* get GIT version information */
  {
    CHAR *temp_version = XLALGetVersionString(0);
    UINT4 n = strlen(temp_version);
    version_string = XLALCalloc(n,sizeof(CHAR));
    snprintf(version_string,n-1,"%s",temp_version);
    XLALFree(temp_version);
  }

  /* output header information */
  fprintf((*fp),"%s \n",version_string);
  fprintf((*fp),"%%%% command line args\t\t= %s\n",clargs);
  fprintf((*fp),"%%%% filename\t\t\t\t= %s\n",outputfile);
  fprintf((*fp),"%%%% date\t\t\t\t\t= %s\n",time_string);
  fprintf((*fp),"%%%% start time (GPS sec)\t\t= %d\n",pspace->epoch.gpsSeconds);
  fprintf((*fp),"%%%% observation span (sec)\t= %d\n",(UINT4)pspace->span);
  fprintf((*fp),"%%%% coherent time (sec)\t\t= %d\n",(UINT4)pspace->tseg);
 /*  fprintf(fp,"%%%% number of segments\t\t= %d\n",Bayes->nsegments); */
/*   fprintf(fp,"%%%% number of dimensions\t= %d\n",Bayes->gridparams->ndim); */
/*   if (pspace->ampspace) fprintf(fp,"%%%% amplitude dimension\t\t\t= 1\n"); */
/*   else fprintf(fp,"%%%% amplitude dimension\t\t\t= 0\n"); */
/*   fprintf(fp,"%%%% mismatch\t\t\t\t= %6.12f\n",Bayes->gridparams->mismatch); */
  fprintf((*fp),"%%%%\n");

  /* free memory */
  XLALFree(time_string);
  XLALFree(version_string);

  LogPrintf(LOG_DEBUG,"%s : leaving.\n",__func__);
  return XLAL_SUCCESS;

}
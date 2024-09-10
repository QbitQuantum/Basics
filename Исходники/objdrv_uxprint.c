/*** uxpWrite - write to a new print job.  Each time this driver is opened
 *** and written to, it spools a new print job.
 ***/
int
uxpWrite(void* inf_v, char* buffer, int cnt, int offset, int flags, pObjTrxTree* oxt)
    {
    pUxpData inf = UXP(inf_v);
    int rval;
    char* spooldir = NULL;
    char* type = NULL;
    struct stat fileinfo;
    int start_filter = 0;
    int saved_errno;

	/** Start the filter process? **/
	if (!inf->SpoolFileFD && !inf->MasterFD)
	    {
	    start_filter = 1;
	    }

    	/** Ok, need to create a new print job? **/
	if (inf->SpoolFileFD == NULL)
	    {
	    /** Get spool dir. **/
	    stAttrValue(stLookup(inf->Node->Data,"spool_directory"), NULL, &spooldir, 0);
	    if (!spooldir) 
	        {
		mssError(1,"UXP","Spool directory not specified in node object");
		return -1;
		}

	    /** Generate a spool file name **/
	  TRY_SPOOL_AGAIN:
	    do  {
	        sprintf(inf->SpoolPathname,"%s/%8.8d.job",spooldir,UXP_INF.SpoolCnt++);
		} while (lstat(inf->SpoolPathname, &fileinfo) == 0);

	    /** Open the spool file **/
	    inf->SpoolFileFD = fdOpen(inf->SpoolPathname, O_WRONLY | O_CREAT | O_EXCL, 0600);
	    if (!inf->SpoolFileFD) 
	        {
		/** oops - race condition, someone else got it, try again **/
		saved_errno = errno;
		if (lstat(inf->SpoolPathname, &fileinfo) == 0) goto TRY_SPOOL_AGAIN;

		/** Oh well, can't open the thing. **/
		/** Shouldn't be writing to errno, but mssErrorErrno wants it... sigh... **/
		errno = saved_errno;
		mssErrorErrno(1,"UXP","Could not open spool file");
		return -1;
		}
	    }

	/** Ok, delayed start of filter process to wait until spoofile-fd is open **/
	if (start_filter)
	    {
	    stAttrValue(stLookup(inf->Node->Data,"type"), NULL, &type, 0);
	    if (type && strcmp(type, inf->ReqType) && !strcmp(inf->ReqType,"text/html"))
	        {
		uxp_internal_StartFilter(inf);
		}
	    }

	/** Need to filter the data? **/
	if (inf->MasterFD)
	    {
	    rval = fdWrite(inf->MasterFD, buffer, cnt, offset, flags);
	    }
	else
	    {
	    /** Write to the spool file. **/
	    rval = fdWrite(inf->SpoolFileFD, buffer, cnt, offset, flags);
	    }

    return rval;
    }
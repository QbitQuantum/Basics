int WINAPI
OpenFile(LPCSTR lpszFileName,OFSTRUCT *lpofs,UINT wFunction)
{
    int   fd;
    const char *lpstr = lpszFileName;

    /*
     *  The "lpstr" variable is needed as a workaround to a bug
     *  in the SunOS "acc" compiler, which treats the LPCSTR typedef
     *  as type "const char * const" rather than the requested
     *  "const char *".
     */

    APISTR((LF_APICALL,"OpenFile(LPCSTR=%s,OFSTRUCT=%p,UINT=%x)\n",
	lpszFileName,lpofs,wFunction));

    if ((wFunction & OF_REOPEN)) {
	lpstr = lpofs->szPathName;
    }
    if (!lpstr) {
           APISTR((LF_APIFAIL,"OpenFile: returns int HFILE_ERROR\n"));
           return HFILE_ERROR;
    }

    if(wFunction & OF_PARSE) {
	memset((LPSTR)lpofs,0,sizeof(OFSTRUCT));
	MFS_ALTPATH(lpofs->szPathName, lpstr);
        APISTR((LF_APIFAIL,"OpenFile: returns int 0\n"));
	return 0;
    }

    lpofs->fFixedDisk = 1;

    if(wFunction & OF_DELETE) {
	fd = _ldelete(lpstr);
	if(fd == 0) {
          APISTR((LF_APIRET,"OpenFile: returns int 1\n"));
	  return 1;
	} else {
          APISTR((LF_APIFAIL,"OpenFile: returns int HFILE_ERROR\n"));
	  return HFILE_ERROR;
	}
    }

    if(wFunction & OF_CREATE)
	fd = _lcreat(lpstr, 0);
    else
	fd = OpenEngine(lpstr,lpofs,wFunction);		

#ifdef LATER
    if(fd < 0) {
	if((wFunction & (OF_PROMPT|OF_CREATE)) == OF_PROMPT) {
	    printf("prompting user for file %s cancel...\n",
					wFunction&OF_CANCEL?"w/":"w/o ");
	}
    }
    if((wFunction & (OF_READ|OF_VERIFY)) == (OF_READ|OF_VERIFY)) {
	printf("checking for date/time...\n");
    }
#endif

    if(fd < 0) {
    	APISTR((LF_APIFAIL,"OpenFile: returns int %d\n",fd));
	return fd;	
    }

    if(wFunction & OF_EXIST)
	_lclose(fd);

    APISTR((LF_APIRET,"OpenFile: returns int %d\n",fd));
    return fd;
}
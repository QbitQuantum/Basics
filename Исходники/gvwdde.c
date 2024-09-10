int
gsview_progman(char *groupname, char *gsviewpath, int gsver, char *gspath, char *gsargs)
{
DWORD idInst = 0L;
FARPROC lpDdeProc;
HSZ hszServName;
HSZ hszSysTopic;
HSZ hszGroupsItem;
HCONV hConv;
HDDEDATA hdata = NULL;
char setup[MAXSTR+MAXSTR];
DWORD dwResult;
char groupfile[MAXSTR];
int i;
char *s, *d;
FILE *ddefile;
char gspathbuf[MAXSTR];
char gsviewpathbuf[MAXSTR];
char gsdocbuf[MAXSTR];

    strncpy(gspathbuf, gspath, sizeof(gspathbuf)/sizeof(TCHAR));
    strncpy(gsdocbuf, gsargs, sizeof(gsdocbuf)/sizeof(TCHAR));
    d = strchr(gsdocbuf, ';');
    if (d)
       *d = '\0';
    if (gsver >= 593) {
	d = strrchr(gsdocbuf, '\\');
	if (d) {
	    d++;
	    strcpy(d, "doc\\");
	}
    }
    else {
	strcat(gsdocbuf, "\\");
    }
    strncpy(gsviewpathbuf, gsviewpath, sizeof(gsviewpathbuf));
    if (!is_win32s) {
	/* The DDE interface isn't reliable with long names */
	/* Convert everything to short names */
	GetShortPathNameA(gspath, gspathbuf, sizeof(gspathbuf));
	GetShortPathNameA(gsviewpath, gsviewpathbuf, sizeof(gsviewpathbuf));
    }

    /* Open ProgMan DDE undo file if it doesn't exist */
    strcpy(setup, gsviewpathbuf);
    strcat(setup, GSVIEW_ZIP);
    d = strrchr(setup, '.');
    strcpy(d, "dde.log");
    ddefile = fopen(setup, "r");
    if (ddefile != (FILE *)NULL) {
	/* We found a previous ProgMan DDE undo file. */
	/* Don't touch it since we want to keep the original record */
	/* of the ProgMan state before GSview was installed */ 
	fclose(ddefile);
	ddefile = (FILE *)NULL;
    }
    else {
        ddefile = fopen(setup, "w");
	/* If we fail to open the file for writing, the destination is probably 
	 * read only.  Don't worry, just don't write to the log file.
	 */
    }

    /* derive group filename from group name */
    for (i=0, s=groupname, d=groupfile; i<8 && *s; s++) {
	if (isalpha((int)(*s)) || isdigit((int)(*s))) {
	    *d++ = *s;
	    i++;
	} 
    }
    *d = '\0';
    if (strlen(groupfile)==0)
	strcpy(groupfile, "gstools");

    lpDdeProc = MakeProcInstance((FARPROC)DdeCallback, phInstance);
    if (DdeInitialize(&idInst, (PFNCALLBACK)lpDdeProc, CBF_FAIL_POKES, 0L)) {
	return 1;
    }
    hszServName = DdeCreateStringHandleA(idInst, "PROGMAN", CP_WINANSI);
    hszSysTopic = DdeCreateStringHandleA(idInst, "PROGMAN", CP_WINANSI);
    hConv = DdeConnect(idInst, hszServName, hszSysTopic, (PCONVCONTEXT)NULL);
    if (hConv == NULL) {
	DdeFreeStringHandle(idInst, hszServName);
	DdeFreeStringHandle(idInst, hszSysTopic);
	return 1;
    }

    if (ddefile) {
	/* Find out if group existed */
	hszGroupsItem = DdeCreateStringHandleA(idInst, groupname, CP_WINANSI);
	hdata = DdeClientTransaction((LPBYTE)NULL, 0, hConv,\
	    hszGroupsItem, CF_TEXT, XTYP_REQUEST, 5000, &dwResult);
	DdeFreeStringHandle(idInst, hszGroupsItem);
    }

#define DDEEXECUTE(str)\
    DdeClientTransaction((LPBYTE)str, strlen(str)+1, hConv,\
	NULL, CF_TEXT, XTYP_EXECUTE, 5000, &dwResult)

    sprintf(setup, "[CreateGroup(\042%s\042,%s.grp)][ShowGroup(\042%s\042,1)]",
	groupname, groupfile, groupname);  /* display, active */
    DDEEXECUTE(setup);
    if (ddefile)	/* display, no active */
        fprintf(ddefile, "[ShowGroup(\042%s\042,8)]\n",groupname);
    sprintf(setup, "[ReplaceItem(\042%s\042)]", GSVIEW_NAME);
    DDEEXECUTE(setup);
#ifdef _WIN64
#define GSVIEW_ICON "gsview64.ico"
#else
#define GSVIEW_ICON "gsview32.ico"
#endif
    if (!is_win4)
       sprintf(setup, "[AddItem(\042%s%s\042,\042%s\042, \042%s%s\042)]", 
	  gsviewpathbuf, GSVIEW_EXENAME, GSVIEW_NAME, gsviewpathbuf, 
	  GSVIEW_ICON);
    else
       sprintf(setup, "[AddItem(\042%s%s\042,\042%s\042)]", 
	  gsviewpathbuf, GSVIEW_EXENAME, GSVIEW_NAME);
    DDEEXECUTE(setup);
    if (ddefile)
        fprintf(ddefile, "[DeleteItem(\042%s\042)]\n", GSVIEW_NAME);

/* Win3.1 documentation says you must put quotes around names */
/* with embedded spaces. */
/* In Win95, it appears you must put quotes around the EXE name */
/* and options separately */

    sprintf(setup, "[ReplaceItem(\042GSview README\042)]");
    DDEEXECUTE(setup);
#ifdef NOTUSED_IN_GSVIEW28
    if (!is_win4)
	sprintf(setup, "[AddItem(\042notepad.exe %sREADME.TXT\042,\042GSview README\042)]", 
	    gsviewpathbuf);
    else
	sprintf(setup, "[AddItem(\042notepad.exe\042 \042%sREADME.TXT\042,\042GSview README\042,\042notepad.exe\042,1)]", 
	    gsviewpathbuf);
#endif
    sprintf(setup, "[AddItem(\042%sReadme.htm\042,\042GSview README\042)]", 
	    gsviewpathbuf);
    DDEEXECUTE(setup);
    if (ddefile)
        fprintf(ddefile, "[DeleteItem(\042%s\042)]\n", "GSview README");

    sprintf(setup, "[ReplaceItem(\042Ghostscript\042)]");
    DDEEXECUTE(setup);
    if (!is_win4)
        sprintf(setup, "[AddItem(\042%s%s -I%s\042,\042Ghostscript\042, \042%sgstext.ico\042)]", 
	    gspathbuf, GS_EXENAME, gsargs, gspathbuf);
    else
        sprintf(setup, "[AddItem(\042%s%s\042 \042-I%s\042,\042Ghostscript\042)]", 
	    gspathbuf, GS_EXENAME, gsargs);
    DDEEXECUTE(setup);
    if (ddefile)
        fprintf(ddefile, "[DeleteItem(\042%s\042)]\n", "Ghostscript");

    sprintf(setup, "[ReplaceItem(\042Ghostscript README\042)]");
    DDEEXECUTE(setup);
    if (gsver >= 540) {
	    sprintf(setup, 
		"[AddItem(\042%sReadme.htm\042,\042Ghostscript README\042)]", 
		 gsdocbuf);
    }
    else {
	if (!is_win4)
	    sprintf(setup, "[AddItem(\042notepad.exe %sREADME.\042,\042Ghostscript README\042)]", 
		 gsdocbuf);
	else
	    sprintf(setup, "[AddItem(\042notepad.exe\042 \042%sREADME.\042,\042Ghostscript README\042, \042notepad.exe\042,1)]", 
		 gsdocbuf);
    }
    DDEEXECUTE(setup);
    if (ddefile)
        fprintf(ddefile, "[DeleteItem(\042%s\042)]\n", "Ghostscript README");


#undef DDEXECUTE

    /* Now remember the way things were */
    if (ddefile) {
      if (hdata) {
	DWORD dlen;
	BYTE FAR *lpData = DdeAccessData(hdata, &dlen);
	LPSTR p, q;
	/* skip first line */
	q = (LPSTR)lpData;
	while (*q && (*q != '\r') && (*q != '\n'))
	    q++;
	while (*q && ((*q == '\r') || (*q == '\n')))
	    q++;
	p = q;
	/* for each group item */
	while (*p) {
	    /* skip to end of line */
	    while (*q && (*q != '\r') && (*q != '\n'))
		q++;
	    strncpy(setup, p, (int)(q-p)+1);
	    add_group_item(ddefile, setup);
	    /* skip to start of next group name */
	    while (*q && ((*q == '\r') || (*q == '\n')))
		q++;
	    p = q;
	}
	if (ddefile)		/* display, no active */
	    fprintf(ddefile, "[ShowGroup(\042%s\042,8)]\n",groupname);
	DdeUnaccessData(hdata);
	DdeFreeDataHandle(hdata);
      }
      else {
	/* group didn't exist before, so delete it */
        fprintf(ddefile, "[DeleteGroup(\042%s\042)]\n", groupname);
      }
      fclose(ddefile);
    }

    DdeDisconnect(hConv);
    DdeFreeStringHandle(idInst, hszServName);
    DdeFreeStringHandle(idInst, hszSysTopic);
    DdeUninitialize(idInst);

    return 0;
}
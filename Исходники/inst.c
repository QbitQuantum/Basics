static BOOL
InUn(int remove, char *drivername, char *dllname, char *dll2name, char *dsname)
{
    char path[301], driver[300], attr[300], inst[400], inst2[400];
    WORD pathmax = sizeof (path) - 1, pathlen;
    DWORD usecnt, mincnt;

    if (SQLInstallDriverManager(path, pathmax, &pathlen)) {
	char *p;

	sprintf(driver, "%s;Driver=%s;Setup=%s;",
		drivername, dllname, dllname);
	p = driver;
	while (*p) {
	    if (*p == ';') {
		*p = '\0';
	    }
	    ++p;
	}
	usecnt = 0;
	SQLInstallDriverEx(driver, NULL, path, pathmax, &pathlen,
			   ODBC_INSTALL_INQUIRY, &usecnt);
	sprintf(driver, "%s;Driver=%s\\%s;Setup=%s\\%s;",
		drivername, path, dllname, path, dllname);
	p = driver;
	while (*p) {
	    if (*p == ';') {
		*p = '\0';
	    }
	    ++p;
	}
	sprintf(inst, "%s\\%s", path, dllname);
	if (dll2name) {
	    sprintf(inst2, "%s\\%s", path, dll2name);
	}
	if (!remove && usecnt > 0) {
	    /* first install try: copy over driver dll, keeping DSNs */
	    if (GetFileAttributes(dllname) != INVALID_FILE_ATTRIBUTES &&
		CopyFile(dllname, inst, 0) &&
		CopyOrDelModules(dllname, path, 0)) {
		if (dll2name != NULL) {
		    CopyFile(dll2name, inst2, 0);
		}
		return TRUE;
	    }
	}
	mincnt = remove ? 1 : 0;
	while (usecnt != mincnt) {
	    if (!SQLRemoveDriver(driver, TRUE, &usecnt)) {
		break;
	    }
	}
	if (remove) {
	    if (!SQLRemoveDriver(driver, TRUE, &usecnt)) {
		ProcessErrorMessages("SQLRemoveDriver");
		return FALSE;
	    }
	    if (!usecnt) {
		char buf[512];

		DeleteFile(inst);
		/* but keep inst2 */
		CopyOrDelModules(dllname, path, 1);
		if (!quiet) {
		    sprintf(buf, "%s uninstalled.", drivername);
		    MessageBox(NULL, buf, "Info",
			       MB_ICONINFORMATION|MB_OK|MB_TASKMODAL|
			       MB_SETFOREGROUND);
		}
	    }
	    if (nosys) {
		goto done;
	    }
	    sprintf(attr, "DSN=%s;Database=sqlite.db;", dsname);
	    p = attr;
	    while (*p) {
		if (*p == ';') {
		    *p = '\0';
		}
		++p;
	    }
	    SQLConfigDataSource(NULL, ODBC_REMOVE_SYS_DSN, drivername, attr);
	    goto done;
	}
	if (GetFileAttributes(dllname) == INVALID_FILE_ATTRIBUTES) {
	    return FALSE;
	}
	if (!CopyFile(dllname, inst, 0)) {
	    char buf[512];

	    sprintf(buf, "Copy %s to %s failed", dllname, inst);
	    MessageBox(NULL, buf, "CopyFile",
		       MB_ICONSTOP|MB_OK|MB_TASKMODAL|MB_SETFOREGROUND); 
	    return FALSE;
	}
	if (dll2name != NULL && !CopyFile(dll2name, inst2, 0)) {
	    char buf[512];

	    sprintf(buf, "Copy %s to %s failed", dll2name, inst2);
	    MessageBox(NULL, buf, "CopyFile",
		       MB_ICONSTOP|MB_OK|MB_TASKMODAL|MB_SETFOREGROUND); 
	    /* but go on hoping that an SQLite engine is in place */
	}
	if (!CopyOrDelModules(dllname, path, 0)) {
	    return FALSE;
	}
	if (!SQLInstallDriverEx(driver, path, path, pathmax, &pathlen,
				ODBC_INSTALL_COMPLETE, &usecnt)) {
	    ProcessErrorMessages("SQLInstallDriverEx");
	    return FALSE;
	}
	if (nosys) {
	    goto done;
	}
	sprintf(attr, "DSN=%s;Database=sqlite.db;", dsname);
	p = attr;
	while (*p) {
	    if (*p == ';') {
		*p = '\0';
	    }
	    ++p;
	}
	SQLConfigDataSource(NULL, ODBC_REMOVE_SYS_DSN, drivername, attr);
	if (!SQLConfigDataSource(NULL, ODBC_ADD_SYS_DSN, drivername, attr)) {
	    ProcessErrorMessages("SQLConfigDataSource");
	    return FALSE;
	}
    } else {
	ProcessErrorMessages("SQLInstallDriverManager");
	return FALSE;
    }
done:
    return TRUE;
}
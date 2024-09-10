int
TclpListVolumes( 
    Tcl_Interp *interp)		/* Interpreter for returning volume list. */
{
    Tcl_Obj *resultPtr, *elemPtr;
    char buf[40 * 4];		/* There couldn't be more than 30 drives??? */
    int i;
    char *p;

    resultPtr = Tcl_GetObjResult(interp);

    /*
     * On Win32s:
     * GetLogicalDriveStrings() isn't implemented.
     * GetLogicalDrives() returns incorrect information.
     */

    if (GetLogicalDriveStringsA(sizeof(buf), buf) == 0) {
	/*
	 * GetVolumeInformation() will detects all drives, but causes
	 * chattering on empty floppy drives.  We only do this if 
	 * GetLogicalDriveStrings() didn't work.  It has also been reported
	 * that on some laptops it takes a while for GetVolumeInformation()
	 * to return when pinging an empty floppy drive, another reason to 
	 * try to avoid calling it.
	 */

	buf[1] = ':';
	buf[2] = '/';
	buf[3] = '\0';

	for (i = 0; i < 26; i++) {
	    buf[0] = (char) ('a' + i);
	    if (GetVolumeInformationA(buf, NULL, 0, NULL, NULL, NULL, NULL, 0)  
		    || (GetLastError() == ERROR_NOT_READY)) {
		elemPtr = Tcl_NewStringObj(buf, -1);
		Tcl_ListObjAppendElement(NULL, resultPtr, elemPtr);
	    }
	}
    } else {
	for (p = buf; *p != '\0'; p += 4) {
	    p[2] = '/';
	    elemPtr = Tcl_NewStringObj(p, -1);
	    Tcl_ListObjAppendElement(NULL, resultPtr, elemPtr);
	}
    }
    return TCL_OK;	
}
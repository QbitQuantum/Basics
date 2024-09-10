/* take a path with a drive letter, possibly relative, and return a full path
 * without the drive letter.  This is the full path relative to the working
 * dir for that drive letter.  The input and output paths can be the same.
 */
long fs_GetFullPath(char *pathp, char *outPathp, long outSize)
{
	char tpath[1000];
	char origPath[1000];
    char *firstp;
    long code;
    int pathHasDrive;
    int doSwitch;
    char newPath[3];

	if (pathp[0] != 0 && pathp[1] == ':') {
		/* there's a drive letter there */
        firstp = pathp+2;
        pathHasDrive = 1;
    } else {
        firstp = pathp;
		pathHasDrive = 0;
	}

    if (*firstp == '\\' || *firstp == '/') {
		/* already an absolute pathname, just copy it back */
        strcpy(outPathp, firstp);
        return 0;
    }

    GetCurrentDirectoryA(sizeof(origPath), origPath);

	doSwitch = 0;
    if (pathHasDrive && (*pathp & ~0x20) != (origPath[0] & ~0x20)) {
		/* a drive has been specified and it isn't our current drive.
         * to get path, switch to it first.  Must case-fold drive letters
         * for user convenience.
         */
		doSwitch = 1;
        newPath[0] = *pathp;
        newPath[1] = ':';
        newPath[2] = 0;
        if (!SetCurrentDirectoryA(newPath)) {
			code = GetLastError();
            return code;
        }
    }

    /* now get the absolute path to the current wdir in this drive */
    GetCurrentDirectoryA(sizeof(tpath), tpath);
    strcpy(outPathp, tpath+2);	/* skip drive letter */
	/* if there is a non-null name after the drive, append it */
	if (*firstp != 0) {
        strcat(outPathp, "\\");
        strcat(outPathp, firstp);
	}

	/* finally, if necessary, switch back to our home drive letter */
    if (doSwitch) {
        SetCurrentDirectoryA(origPath);
    }

    return 0;
}
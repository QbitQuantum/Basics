BOOL Cleanup(void)
{
    char FileName[20];
    int i;
    BOOL bRet = TRUE; // assume success

    // loop through all accesses, modes, dispositions and flags
    for (i=0; i<4*8*4*5; ++i) {
        sprintf(FileName, "test%03d.txt", i);
	if (DeleteFileA(FileName) == FALSE) {
	    if (GetLastError() != ERROR_FILE_NOT_FOUND) {
		bRet = FALSE;
	    }
	}
    }
    return bRet;
}
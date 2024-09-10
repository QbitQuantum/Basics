BOOL    EXTERN LoadCP(LPCSTR filename, HGLOBAL FAR *phMem, LPCHANDLE lpCP)
{
    icHeader    CPHeader;
    HFILE       hFile;
    SINT        Res, CPSize;
    MEMPTR      mpCP;

    *phMem = 0;
    if (lpCP == NULL)
    {
        SetCPLastError(CP_NULL_POINTER_ERR);
        return(FALSE);
    }

    hFile = _lopen(filename, READ );
    if( hFile == HFILE_ERROR )
    {
        SetCPLastError(CP_FILE_OPEN_ERR);
        return(FALSE);
    }
 
    Res = _lread(hFile, (LPVOID) &CPHeader, sizeof(CPHeader));
    if( (Res == HFILE_ERROR) ||
        (Res != sizeof(CPHeader)) )
    {
        _lclose(hFile);
        SetCPLastError(CP_FILE_READ_ERR);
        return(FALSE);
    }

    // Make the initial check for validity of the profile
    if( SigtoCSIG(CPHeader.magic) != icMagicNumber )
    {
        _lclose(hFile);
        SetCPLastError(CP_FORMAT_ERR);
        return(FALSE);
    }

    CPSize = ui32toSINT(CPHeader.size);
    if( MemAlloc(CPSize, phMem, (LPMEMPTR) &mpCP) )
    {

        *lpCP = (CHANDLE) mpCP;  // Put the memory pointer as  handle
        // Read profile into  memory
         _lseek(hFile, 0L, SEEK_SET);

        while(CPSize)
        {
            Res = _lread(hFile, (LPVOID) mpCP, 4096);
            if (Res == HFILE_ERROR) 
            {
                _lclose(hFile);
                SetCPLastError(CP_FILE_READ_ERR);
                return(FALSE);
            }
            mpCP    += Res;
            CPSize  -= Res;
        }
    }else
    {
        *phMem = 0;
        _lclose(hFile);
        return(FALSE);
    }
    _lclose(hFile);
    return (TRUE);
}
bool GetAliases(wchar_t* asExeName, wchar_t** rsAliases, LPDWORD rnAliasesSize)
{
    bool lbRc = false;
    DWORD nAliasRC, nAliasErr, nAliasAErr = 0, nSizeA = 0;
    _ASSERTE(asExeName && rsAliases && rnAliasesSize);
    _ASSERTE(*rsAliases == NULL);
    *rnAliasesSize = GetConsoleAliasesLength(asExeName);

    if (*rnAliasesSize == 0)
    {
        lbRc = true;
    }
    else
    {
        *rsAliases = (wchar_t*)calloc(*rnAliasesSize+2,1);
        nAliasRC = GetConsoleAliases(*rsAliases,*rnAliasesSize,asExeName);

        if (nAliasRC)
        {
            lbRc = true;
        }
        else
        {
            nAliasErr = GetLastError();

            if (nAliasErr == ERROR_NOT_ENOUGH_MEMORY)
            {
                // Попробовать ANSI функции
                UINT nCP = CP_OEMCP;
                char szExeName[MAX_PATH+1];
                char *pszAliases = NULL;
                WideCharToMultiByte(nCP,0,asExeName,-1,szExeName,MAX_PATH+1,0,0);
                nSizeA = GetConsoleAliasesLengthA(szExeName);

                if (nSizeA)
                {
                    pszAliases = (char*)calloc(nSizeA+1,1);
                    nAliasRC = GetConsoleAliasesA(pszAliases,nSizeA,szExeName);

                    if (nAliasRC)
                    {
                        lbRc = true;
                        MultiByteToWideChar(nCP,0,pszAliases,nSizeA,*rsAliases,((*rnAliasesSize)/2)+1);
                    }
                    else
                    {
                        nAliasAErr = GetLastError();
                    }

                    free(pszAliases);
                }
            }

            if (!nAliasRC)
            {
                if ((*rnAliasesSize) < 255) {
                    free(*rsAliases);
                    *rsAliases = (wchar_t*)calloc(128,2);
                }

                _wsprintf(*rsAliases, SKIPLEN(127) L"\nConEmuC: GetConsoleAliases failed, ErrCode=0x%08X(0x%08X), AliasesLength=%i(%i)\n\n", nAliasErr, nAliasAErr, *rnAliasesSize, nSizeA);
            }
        }
    }

    return lbRc;
}
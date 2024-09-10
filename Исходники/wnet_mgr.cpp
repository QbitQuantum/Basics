static xpr_bool_t WINAPI EnumerateFunc(LPNETRESOURCE lpnr2, LPNETRESOURCE aNetResource, in_addr *pin_addr2)
{
    DWORD sWNetResult, sWNetEnumResult;
    HANDLE sWNetEnum;
    DWORD sBufferSize = 16384;
    DWORD i, sEntries = -1;
    LPNETRESOURCE sLocalNetResource;
    xpr_tchar_t sFullName[XPR_MAX_URL_LENGTH + 1] = {0};
    xpr_char_t sAnsiFullName[XPR_MAX_URL_LENGTH + 1] = {0};
    xpr_char_t sHostName[XPR_MAX_URL_LENGTH + 1] = {0};
    xpr_size_t sInputBytes;
    xpr_size_t sOutputBytes;

    sWNetResult = WNetOpenEnum(RESOURCE_GLOBALNET, RESOURCETYPE_ANY, 0, lpnr2, &sWNetEnum);
    if (sWNetResult != NO_ERROR)
        return XPR_FALSE;

    sLocalNetResource = (LPNETRESOURCE)GlobalAlloc(GPTR, sBufferSize);
    if (sLocalNetResource == XPR_NULL) 
        return XPR_FALSE;

    xpr_bool_t sResult = XPR_FALSE;

    do
    {  
        ZeroMemory(sLocalNetResource, sBufferSize);

        sWNetEnumResult = WNetEnumResource(sWNetEnum, &sEntries, sLocalNetResource, &sBufferSize);
        if (sWNetEnumResult == NO_ERROR)
        {
            for (i = 0; i < sEntries; ++i)
            {
                // sLocalNetResource[i]
                _tcscpy(sFullName, sLocalNetResource[i].lpRemoteName);
                if (_tcscmp(sFullName, XPR_STRING_LITERAL("\\\\")) == 0)
                {
                    xpr_sint_t sLen = (xpr_sint_t)_tcslen(sFullName) - 2;
                    memmove(sFullName, sFullName+2, sLen*sizeof(xpr_tchar_t));
                    sFullName[sLen] = '\0';
                }

                sInputBytes = _tcslen(sFullName) * sizeof(xpr_tchar_t);
                sOutputBytes = XPR_MAX_URL_LENGTH * sizeof(xpr_tchar_t);
                XPR_TCS_TO_MBS(sFullName, &sInputBytes, sAnsiFullName, &sOutputBytes);
                sAnsiFullName[sOutputBytes / sizeof(xpr_char_t)] = 0;

                gethostname(sHostName, (xpr_sint_t)strlen(sHostName));

                HOSTENT *sHostEnt = gethostbyname(sAnsiFullName);
                if (XPR_IS_NOT_NULL(sHostEnt))
                {
                    struct in_addr *sInAddr = (struct in_addr *)sHostEnt->h_addr_list[0];
                    if (sInAddr->S_un.S_un_b.s_b1 == pin_addr2->S_un.S_un_b.s_b1 &&
                        sInAddr->S_un.S_un_b.s_b2 == pin_addr2->S_un.S_un_b.s_b2 &&
                        sInAddr->S_un.S_un_b.s_b3 == pin_addr2->S_un.S_un_b.s_b3 &&
                        sInAddr->S_un.S_un_b.s_b4 == pin_addr2->S_un.S_un_b.s_b4)
                    {
                        _tcscpy(aNetResource->lpRemoteName, sLocalNetResource[i].lpRemoteName);
                        sResult = XPR_TRUE;
                        goto ENUM_END;
                    }
                }

                if (RESOURCEUSAGE_CONTAINER == (sLocalNetResource[i].dwUsage & RESOURCEUSAGE_CONTAINER))
                {
                    if (EnumerateFunc(&sLocalNetResource[i], aNetResource, pin_addr2))
                        goto ENUM_END;
                }
            }
        }
        else if (sWNetEnumResult != ERROR_NO_MORE_ITEMS)
        {
            break;
        }
    } while (sWNetEnumResult != ERROR_NO_MORE_ITEMS);

ENUM_END:
    GlobalFree((HGLOBAL)sLocalNetResource);

    sWNetResult = WNetCloseEnum(sWNetEnum);
    if (sWNetResult != NO_ERROR)
        return XPR_FALSE;

    return sResult;
}
SYSLIBFUNC(DWORD) StrSplitToStringsExW(LPCWSTR lpSource,DWORD dwSourceSize,LPWSTR **lpppStrings,DWORD dwFlags,WCHAR wSeparator)
{
    DWORD dwCount=0;
    do
    {
        if (!SYSLIB_SAFE::CheckStrParamW(lpSource,dwSourceSize))
            break;

        if (!dwSourceSize)
        {
            dwSourceSize=lstrlenW(lpSource);
            if (!dwSourceSize)
                break;
        }

        LPCWSTR lpStrEnd=lpSource+dwSourceSize;
        LPWSTR *lppStrings=NULL;

        while (lpSource < lpStrEnd)
        {
            LPCWSTR lpStrStart=lpSource;
            DWORD dwStrSize;
            if (dwFlags & STRSPLIT_USE_SEPARATOR)
            {
                LPCWSTR lpCurEnd=lpSource;
                while ((lpCurEnd < lpStrEnd) && (*lpCurEnd != wSeparator))
                    lpCurEnd++;

                dwStrSize=(DWORD)(lpCurEnd-lpSource);
                lpSource=lpCurEnd+1;
            }
            else
                dwStrSize=GetStringSizeW(&lpSource,lpStrEnd);

            if (!dwStrSize)
                break;

            lppStrings=(LPWSTR *)MemRealloc(lppStrings,(dwCount+1)*sizeof(*lppStrings));
            if (!lppStrings)
            {
                dwCount=0;
                break;
            }

            lppStrings[dwCount]=StrDuplicateW(lpStrStart,dwStrSize);
            if (!lppStrings[dwCount])
            {
                MemFreeArrayOfPointers((LPVOID*)lppStrings,dwCount);
                dwCount=0;
                break;
            }

            dwCount++;
        }

        if (!dwCount)
            break;

        *lpppStrings=lppStrings;
    }
    while (false);
    return dwCount;
}
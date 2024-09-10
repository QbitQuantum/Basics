int __cdecl wmain (int argc, WCHAR* args[])
{
    WCHAR wszRegPath[MAX_LEN] ;
    int iTimeout=0;
    BOOL bEnd = FALSE;
    
    while(!bEnd)
    {
        wprintf(L"Enter registry key path (\"quit\" to quit): ");
        wscanf(L"%s", wszRegPath, MAX_LEN);

        if(!_wcsicmp(wszRegPath, L"quit"))
        {
            bEnd=TRUE;
            continue;
        }

        wprintf(L"Enter timeout for enumeration: ");
        wscanf(L"%d", &iTimeout);
        
        if(iTimeout==0)
        {
            wprintf(L"Invalid timeout specified...\n");
            bEnd=TRUE;
        }
        else
        {
            //
            // Enumerate 
            //
            if ( RegEnum(wszRegPath, iTimeout) == FALSE )
            {
                DisplayError(wszRegPath, REG_DWORD, iTimeout, TRUE);
            }

        }
    }
    return 0;
}
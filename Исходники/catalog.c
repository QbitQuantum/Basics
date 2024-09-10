INT
LoadProvider(PCATALOG_ENTRY Provider,
             LPWSAPROTOCOL_INFOW lpProtocolInfo)
{
    INT Status;

    WS_DbgPrint(MID_TRACE, ("Loading provider at (0x%X)  Name (%wZ).\n",
                Provider, &Provider->LibraryName));

    if (NULL == Provider->hModule)
    {
        /* DLL is not loaded so load it now
         * UNICODE_STRING objects are not null-terminated, but LoadLibraryW
         * expects a null-terminated string
         */
        Provider->LibraryName.Buffer[Provider->LibraryName.Length / sizeof(WCHAR)] = L'\0';
        Provider->hModule = LoadLibraryW(Provider->LibraryName.Buffer);
        if (NULL != Provider->hModule)
        {
            Provider->WSPStartup = (LPWSPSTARTUP)GetProcAddress(Provider->hModule,
                                                                "WSPStartup");
            if (Provider->WSPStartup)
            {
                WS_DbgPrint(MAX_TRACE, ("Calling WSPStartup at (0x%X).\n",
                            Provider->WSPStartup));
                Status = Provider->WSPStartup(MAKEWORD(2, 2),
                                              &Provider->WSPData,
                                              lpProtocolInfo,
                                              UpcallTable,
                                              &Provider->ProcTable);

                /* FIXME: Validate the procedure table */
            }
            else
                Status = ERROR_BAD_PROVIDER;
        }
        else
            Status = ERROR_DLL_NOT_FOUND;
    }
    else
        Status = NO_ERROR;

    WS_DbgPrint(MID_TRACE, ("Status (%d).\n", Status));

    return Status;
}
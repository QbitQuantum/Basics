PPH_PROCESS_PROPCONTEXT PhCreateProcessPropContext(
    _In_ HWND ParentWindowHandle,
    _In_ PPH_PROCESS_ITEM ProcessItem
    )
{
    static PH_INITONCE initOnce = PH_INITONCE_INIT;
    PPH_PROCESS_PROPCONTEXT propContext;
    PROPSHEETHEADER propSheetHeader;

    if (PhBeginInitOnce(&initOnce))
    {
        PhpProcessPropContextType = PhCreateObjectType(L"ProcessPropContext", 0, PhpProcessPropContextDeleteProcedure);
        PhpProcessPropPageContextType = PhCreateObjectType(L"ProcessPropPageContext", 0, PhpProcessPropPageContextDeleteProcedure);
        PhEndInitOnce(&initOnce);
    }

    propContext = PhCreateObjectZero(sizeof(PH_PROCESS_PROPCONTEXT), PhpProcessPropContextType);
    propContext->PropSheetPages = PhAllocateZero(sizeof(HPROPSHEETPAGE) * PH_PROCESS_PROPCONTEXT_MAXPAGES);

    if (!PH_IS_FAKE_PROCESS_ID(ProcessItem->ProcessId))
    {
        propContext->Title = PhFormatString(
            L"%s (%u)",
            ProcessItem->ProcessName->Buffer,
            HandleToUlong(ProcessItem->ProcessId)
            );
    }
    else
    {
        PhSetReference(&propContext->Title, ProcessItem->ProcessName);
    }

    memset(&propSheetHeader, 0, sizeof(PROPSHEETHEADER));
    propSheetHeader.dwSize = sizeof(PROPSHEETHEADER);
    propSheetHeader.dwFlags =
        PSH_MODELESS |
        PSH_NOAPPLYNOW |
        PSH_NOCONTEXTHELP |
        PSH_PROPTITLE |
        PSH_USECALLBACK |
        PSH_USEHICON;
    propSheetHeader.hInstance = PhInstanceHandle;
    propSheetHeader.hwndParent = ParentWindowHandle;
    propSheetHeader.hIcon = ProcessItem->SmallIcon;
    propSheetHeader.pszCaption = propContext->Title->Buffer;
    propSheetHeader.pfnCallback = PhpPropSheetProc;

    propSheetHeader.nPages = 0;
    propSheetHeader.nStartPage = 0;
    propSheetHeader.phpage = propContext->PropSheetPages;

    if (PhCsForceNoParent)
        propSheetHeader.hwndParent = NULL;

    memcpy(&propContext->PropSheetHeader, &propSheetHeader, sizeof(PROPSHEETHEADER));

    PhSetReference(&propContext->ProcessItem, ProcessItem);

    return propContext;
}
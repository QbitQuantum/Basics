BOOL WINAPI PifPropGetPages(LPVOID lpv,
                            LPFNADDPROPSHEETPAGE lpfnAddPage,
                            LPARAM lParam)
{
#define hDrop   (HDROP)lpv
    PPROPLINK ppl;
    PROPSHEETPAGE psp;
    int iType, iSheet, cSheets;
    HPROPSHEETPAGE hpage;
    TCHAR szFileName[MAXPATHNAME];
    FunctionName(PifPropGetPages);

    // only process things if hDrop contains only one file
    if (DragQueryFile(hDrop, (UINT)-1, NULL, 0) != 1)
    {
        return TRUE;
    }

    // get the name of the file
    DragQueryFile(hDrop, 0, szFileName, ARRAYSIZE(szFileName));

    // if this is a windows app, don't do no properties
    if (IsWinExe(szFileName))
        return TRUE;

    // if we can't get a property handle, don't do no properties either
    if (!(ppl = (PPROPLINK)PifMgr_OpenProperties(szFileName, NULL, 0, OPENPROPS_NONE)))
        return TRUE;

    InitRealModeFlag(ppl);

    if (!(cSheets = LoadPropertySheets((int)ppl, 0)))
        goto CloseProps;

    // Since the user wishes to *explicitly* change settings for this app
    // we make sure that the DONTWRITE flag isn't going to get in his way...

    ppl->flProp &= ~PROP_DONTWRITE;

    iSheet = cSheets = 0;
    iType = (GetKeyState(VK_CONTROL) >= 0? SHEETTYPE_SIMPLE : SHEETTYPE_ADVANCED);

    while (TRUE) {

        if (!(iSheet = EnumPropertySheets((int)ppl, iType, iSheet, &psp))) {
            // done with enumeration
            break;
        }
#ifndef WINNT
        psp.dwFlags |= PSP_USECALLBACK | PSP_USEREFPARENT;
        psp.pfnCallback = PifPropPageRelease;
        psp.pcRefParent = &s_cRefThisDll;
#else
        psp.dwFlags |= PSP_USECALLBACK;
        psp.pfnCallback = PifPropPageRelease;
        psp.pcRefParent = 0;
#endif

        hpage = CreatePropertySheetPage(&psp);
        if (hpage)
        {
            // the PROPLINK is now being used by this property sheet as well

            if (lpfnAddPage(hpage, lParam))
            {
                ppl->iSheetUsage++;
                cSheets++;
            }
            else
            {
                PifPropPageRelease(NULL, PSPCB_RELEASE, &psp);
            }
        }
    }

    if (!cSheets) {
        FreePropertySheets((int)ppl, 0);

CloseProps:
        PifMgr_CloseProperties((int)ppl, CLOSEPROPS_NONE);
    }
    return TRUE;
}
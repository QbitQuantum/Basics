bbCHAR* uiDlgFileName(uiWINH hWin, const bbCHAR* pPath, bbUINT opt, uiDlgFileNameFilter* const pFilter)
{
#if (bbOS == bbOS_WIN32) || (bbOS == bbOS_WINCE)

    bbCHAR* pFileNameBuffer;
    bbUINT const bufferstart = (opt & uiDLGFILEOPT_MULTISELECT) ? sizeof(uiDlgFileNameBlock)/sizeof(bbCHAR) : 0;
    OPENFILENAME ofn;

    bbMemClear(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner   = hWin;

    if (pPath)
        ofn.nMaxFile = bbStrLen(pPath) + 1;

    if (ofn.nMaxFile < 512)
        ofn.nMaxFile = 512;

    if ((pFileNameBuffer = (bbCHAR*) bbMemAlloc(sizeof(bbCHAR) * ofn.nMaxFile + sizeof(uiDlgFileNameBlock))) == NULL)
        return NULL;

    ofn.lpstrFile = pFileNameBuffer + bufferstart;

    if (pPath)
        bbStrCpy(ofn.lpstrFile, pPath);
    else
        *ofn.lpstrFile = 0;

    if (pFilter)
    {
        ofn.nFilterIndex = pFilter->FilterIndex;
        ofn.lpstrFilter  = pFilter->pFilter;
    }

    ofn.Flags = (opt & (uiDLGFILEOPT_MULTISELECT|uiDLGFILEOPT_NODEREFERENCELINKS|uiDLGFILEOPT_OVERWRITEPROMPT))
        | OFN_DONTADDTORECENT | OFN_ENABLESIZING | OFN_NOTESTFILECREATE | OFN_HIDEREADONLY | OFN_EXPLORER;

    BOOL (__stdcall *fnGetFileName)(LPOPENFILENAME) = (opt & uiDLGFILEOPT_SAVE) ? GetSaveFileName : GetOpenFileName;

    if (fnGetFileName(&ofn) == 0)
    {
        DWORD err = CommDlgExtendedError();

        if (err == FNERR_BUFFERTOOSMALL)
        {
            ofn.nMaxFile = *(WORD*)ofn.lpstrFile;
            if (bbMemRealloc(sizeof(bbCHAR) * ofn.nMaxFile + sizeof(uiDlgFileNameBlock), (void**)&pFileNameBuffer) != bbEOK)
                goto uiDlgFileSave_err;
            ofn.lpstrFile = pFileNameBuffer + bufferstart;

            if (fnGetFileName(&ofn))
                goto uiDlgFileSave_ok;
            err = CommDlgExtendedError();
        }

        if (err == 0)
        {
            bbErrSet(bbEEND);
        }
        else
        {
            bbErrSet(bbESYS); //xxx add error codes
            bbLog(bbErr, bbT("uiDlgFileSave: error %X\n"), err);
        }

        goto uiDlgFileSave_err;
    }

    uiDlgFileSave_ok:

    if (pFilter)
    {
        pFilter->FilterIndex = ofn.nFilterIndex;
    }

    if (opt & uiDLGFILEOPT_MULTISELECT)
    {
        ((uiDlgFileNameBlock*)pFileNameBuffer)->CurFileOffset = 
        ((uiDlgFileNameBlock*)pFileNameBuffer)->FirstFileOffset = ofn.nFileOffset;

        if (ofn.nFileOffset > 0)
            pFileNameBuffer[ofn.nFileOffset + bufferstart - 1] = '\0'; // 0-term path also for single-selection case
    }

    return pFileNameBuffer;

    uiDlgFileSave_err:
    bbMemFree(pFileNameBuffer);
    return NULL;
#else
#endif
}
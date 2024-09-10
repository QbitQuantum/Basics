static HRESULT
InvokeRemoteRegistryPickerDialog(IN IDsObjectPicker *pDsObjectPicker,
                                 IN HWND hwndParent  OPTIONAL,
                                 OUT LPWSTR lpBuffer,
                                 IN UINT uSize)
{
    IDataObject *pdo = NULL;
    HRESULT hRet;

    hRet = pDsObjectPicker->lpVtbl->InvokeDialog(pDsObjectPicker,
            hwndParent,
            &pdo);
    if (hRet == S_OK)
    {
        STGMEDIUM stm;
        FORMATETC fe;

        fe.cfFormat = (CLIPFORMAT) RegisterClipboardFormatW(CFSTR_DSOP_DS_SELECTION_LIST);
        fe.ptd = NULL;
        fe.dwAspect = DVASPECT_CONTENT;
        fe.lindex = -1;
        fe.tymed = TYMED_HGLOBAL;

        hRet = pdo->lpVtbl->GetData(pdo,
                                    &fe,
                                    &stm);
        if (SUCCEEDED(hRet))
        {
            PDS_SELECTION_LIST SelectionList = (PDS_SELECTION_LIST)GlobalLock(stm.hGlobal);
            if (SelectionList != NULL)
            {
                if (SelectionList->cItems == 1)
                {
                    size_t nlen = wcslen(SelectionList->aDsSelection[0].pwzName);
                    if (nlen >= uSize)
                    {
                        nlen = uSize - 1;
                    }

                    memcpy(lpBuffer,
                           SelectionList->aDsSelection[0].pwzName,
                           nlen * sizeof(WCHAR));

                    lpBuffer[nlen] = L'\0';
                }

                GlobalUnlock(stm.hGlobal);
            }

            ReleaseStgMedium(&stm);
        }

        pdo->lpVtbl->Release(pdo);
    }

    return hRet;
}
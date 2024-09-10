/***********************************************************************
 *           OleUIPasteSpecialA (OLEDLG.4)
 */
UINT WINAPI OleUIPasteSpecialA(LPOLEUIPASTESPECIALA psA)
{
    OLEUIPASTESPECIALW ps;
    UINT ret;
    TRACE("(%p)\n", psA);

    memcpy(&ps, psA, psA->cbStruct);

    ps.lpszCaption = strdupAtoW(psA->lpszCaption);
    if(!IS_INTRESOURCE(ps.lpszTemplate))
        ps.lpszTemplate = strdupAtoW(psA->lpszTemplate);

    if(psA->cPasteEntries > 0)
    {
        DWORD size = psA->cPasteEntries * sizeof(ps.arrPasteEntries[0]);
        UINT i;

        ps.arrPasteEntries = HeapAlloc(GetProcessHeap(), 0, size);
        memcpy(ps.arrPasteEntries, psA->arrPasteEntries, size);
        for(i = 0; i < psA->cPasteEntries; i++)
        {
            ps.arrPasteEntries[i].lpstrFormatName =
                strdupAtoW(psA->arrPasteEntries[i].lpstrFormatName);
            ps.arrPasteEntries[i].lpstrResultText =
                strdupAtoW(psA->arrPasteEntries[i].lpstrResultText);
        }
    }

    ret = OleUIPasteSpecialW(&ps);

    if(psA->cPasteEntries > 0)
    {
        UINT i;
        for(i = 0; i < psA->cPasteEntries; i++)
        {
            HeapFree(GetProcessHeap(), 0, (WCHAR*)ps.arrPasteEntries[i].lpstrFormatName);
            HeapFree(GetProcessHeap(), 0, (WCHAR*)ps.arrPasteEntries[i].lpstrResultText);
        }
        HeapFree(GetProcessHeap(), 0, ps.arrPasteEntries);
    }
    if(!IS_INTRESOURCE(ps.lpszTemplate))
        HeapFree(GetProcessHeap(), 0, (WCHAR*)ps.lpszTemplate);
    HeapFree(GetProcessHeap(), 0, (WCHAR*)ps.lpszCaption);

    /* Copy back the output fields */
    psA->dwFlags = ps.dwFlags;
    psA->lpSrcDataObj = ps.lpSrcDataObj;
    psA->nSelectedIndex = ps.nSelectedIndex;
    psA->fLink = ps.fLink;
    psA->hMetaPict = ps.hMetaPict;
    psA->sizel = ps.sizel;

    return ret;
}
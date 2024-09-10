/***********************************************************************
 *           OleUIAddVerbMenuA (OLEDLG.1)
 */
BOOL WINAPI OleUIAddVerbMenuA(IOleObject *object, LPCSTR shorttype,
    HMENU hMenu, UINT uPos, UINT uIDVerbMin, UINT uIDVerbMax,
    BOOL addConvert, UINT idConvert, HMENU *lphMenu)
{
    WCHAR *shorttypeW = NULL;
    BOOL ret;

    TRACE("(%p, %s, %p, %d, %d, %d, %d, %d, %p)\n", object, debugstr_a(shorttype),
        hMenu, uPos, uIDVerbMin, uIDVerbMax, addConvert, idConvert, lphMenu);

    if (shorttype)
    {
        INT len = MultiByteToWideChar(CP_ACP, 0, shorttype, -1, NULL, 0);
        shorttypeW = HeapAlloc(GetProcessHeap(), 0, len*sizeof(WCHAR));
        if (shorttypeW)
            MultiByteToWideChar(CP_ACP, 0, shorttype, -1, shorttypeW, len);
    }

    ret = OleUIAddVerbMenuW(object, shorttypeW, hMenu, uPos, uIDVerbMin, uIDVerbMax,
        addConvert, idConvert, lphMenu);
    HeapFree(GetProcessHeap(), 0, shorttypeW);
    return ret;
}
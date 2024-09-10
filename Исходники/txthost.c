DECLSPEC_HIDDEN HRESULT WINAPI ITextHostImpl_TxGetPropertyBits(ITextHost *iface, DWORD dwMask, DWORD *pdwBits)
{
    ITextHostImpl *This = impl_from_ITextHost(iface);
    ME_TextEditor *editor = (ME_TextEditor *)GetWindowLongPtrW(This->hWnd, 0);
    DWORD style;
    DWORD dwBits = 0;

    if (editor)
    {
        style = editor->styleFlags;
        if (editor->mode & TM_RICHTEXT)
            dwBits |= TXTBIT_RICHTEXT;
        if (editor->bWordWrap)
            dwBits |= TXTBIT_WORDWRAP;
        if (style & ECO_AUTOWORDSELECTION)
            dwBits |= TXTBIT_AUTOWORDSEL;
    } else {
        DWORD dwScrollBar;

        style = GetWindowLongW(This->hWnd, GWL_STYLE);
        ITextHostImpl_TxGetScrollBars(iface, &dwScrollBar);

        dwBits |= TXTBIT_RICHTEXT|TXTBIT_AUTOWORDSEL;
        if (!(dwScrollBar & ES_AUTOHSCROLL))
            dwBits |= TXTBIT_WORDWRAP;
    }

    /* Bits that correspond to window styles. */
    if (style & ES_MULTILINE)
        dwBits |= TXTBIT_MULTILINE;
    if (style & ES_READONLY)
        dwBits |= TXTBIT_READONLY;
    if (style & ES_PASSWORD)
        dwBits |= TXTBIT_USEPASSWORD;
    if (!(style & ES_NOHIDESEL))
        dwBits |= TXTBIT_HIDESELECTION;
    if (style & ES_SAVESEL)
        dwBits |= TXTBIT_SAVESELECTION;
    if (style & ES_VERTICAL)
        dwBits |= TXTBIT_VERTICAL;
    if (style & ES_NOOLEDRAGDROP)
        dwBits |= TXTBIT_DISABLEDRAG;

    dwBits |= TXTBIT_ALLOWBEEP;

    /* The following bits are always FALSE because they are probably only
     * needed for ITextServices_OnTxPropertyBitsChange:
     *   TXTBIT_VIEWINSETCHANGE
     *   TXTBIT_BACKSTYLECHANGE
     *   TXTBIT_MAXLENGTHCHANGE
     *   TXTBIT_CHARFORMATCHANGE
     *   TXTBIT_PARAFORMATCHANGE
     *   TXTBIT_SHOWACCELERATOR
     *   TXTBIT_EXTENTCHANGE
     *   TXTBIT_SELBARCHANGE
     *   TXTBIT_SCROLLBARCHANGE
     *   TXTBIT_CLIENTRECTCHANGE
     *
     * Documented by MSDN as not supported:
     *   TXTBIT_USECURRENTBKG
     */

    *pdwBits = dwBits & dwMask;
    return S_OK;
}
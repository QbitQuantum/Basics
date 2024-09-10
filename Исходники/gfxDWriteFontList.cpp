nsresult
gfxDWriteFontEntry::GetFontTable(PRUint32 aTableTag,
                                 FallibleTArray<PRUint8> &aBuffer)
{
    gfxDWriteFontList *pFontList = gfxDWriteFontList::PlatformFontList();

    // don't use GDI table loading for symbol fonts or for
    // italic fonts in Arabic-script system locales because of
    // potential cmap discrepancies, see bug 629386
    if (mFont && pFontList->UseGDIFontTableAccess() &&
        !(mItalic && UsingArabicScriptSystemLocale()) &&
        !mFont->IsSymbolFont())
    {
        LOGFONTW logfont = { 0 };
        if (!InitLogFont(mFont, &logfont))
            return NS_ERROR_FAILURE;

        AutoDC dc;
        AutoSelectFont font(dc.GetDC(), &logfont);
        if (font.IsValid()) {
            PRInt32 tableSize =
                ::GetFontData(dc.GetDC(), NS_SWAP32(aTableTag), 0, NULL, NULL);
            if (tableSize != GDI_ERROR) {
                if (aBuffer.SetLength(tableSize)) {
                    ::GetFontData(dc.GetDC(), NS_SWAP32(aTableTag), 0,
                                  aBuffer.Elements(), aBuffer.Length());
                    return NS_OK;
                }
                return NS_ERROR_OUT_OF_MEMORY;
            }
        }
        return NS_ERROR_FAILURE;
    }

    HRESULT hr;
    nsresult rv;
    nsRefPtr<IDWriteFontFace> fontFace;

    rv = CreateFontFace(getter_AddRefs(fontFace));

    if (NS_FAILED(rv)) {
        return rv;
    }

    PRUint8 *tableData;
    PRUint32 len;
    void *tableContext = NULL;
    BOOL exists;
    hr = fontFace->TryGetFontTable(NS_SWAP32(aTableTag),
                                   (const void**)&tableData,
                                   &len,
                                   &tableContext,
                                   &exists);

    if (FAILED(hr) || !exists) {
        return NS_ERROR_FAILURE;
    }
    if (!aBuffer.SetLength(len)) {
        return NS_ERROR_OUT_OF_MEMORY;
    }
    memcpy(aBuffer.Elements(), tableData, len);
    if (tableContext) {
        fontFace->ReleaseFontTable(&tableContext);
    }
    return NS_OK;
}
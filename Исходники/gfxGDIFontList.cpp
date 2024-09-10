PRBool 
GDIFontEntry::TestCharacterMap(PRUint32 aCh)
{
    if (ReadCMAP() != NS_OK) {
        // Type1 fonts aren't necessarily Unicode but
        // this is the best guess we can make here
        mUnicodeFont = IsType1();

        // For fonts where we failed to read the character map,
        // we can take a slow path to look up glyphs character by character
        mUnknownCMAP = PR_TRUE;
    }

    if (mUnknownCMAP) {
        if (aCh > 0xFFFF)
            return PR_FALSE;

        // previous code was using the group style
        gfxFontStyle fakeStyle;  
        if (mItalic)
            fakeStyle.style = FONT_STYLE_ITALIC;
        fakeStyle.weight = mWeight * 100;

        nsRefPtr<gfxFont> tempFont = FindOrMakeFont(&fakeStyle, PR_FALSE);
        if (!tempFont || !tempFont->Valid())
            return PR_FALSE;
        gfxGDIFont *font = static_cast<gfxGDIFont*>(tempFont.get());

        HDC dc = GetDC((HWND)nsnull);
        SetGraphicsMode(dc, GM_ADVANCED);
        HFONT hfont = font->GetHFONT();
        HFONT oldFont = (HFONT)SelectObject(dc, hfont);

        PRUnichar str[1] = { (PRUnichar)aCh };
        WORD glyph[1];

        PRBool hasGlyph = PR_FALSE;

        // Bug 573038 - in some cases GetGlyphIndicesW returns 0xFFFF for a 
        // missing glyph or 0x1F in other cases to indicate the "invalid" 
        // glyph.  Map both cases to "not found"
        if (IsType1() || mForceGDI) {
            // Type1 fonts and uniscribe APIs don't get along.  
            // ScriptGetCMap will return E_HANDLE
            DWORD ret = GetGlyphIndicesW(dc, str, 1, 
                                         glyph, GGI_MARK_NONEXISTING_GLYPHS);
            if (ret != GDI_ERROR
                && glyph[0] != 0xFFFF
                && (IsType1() || glyph[0] != MISSING_GLYPH))
            {
                hasGlyph = PR_TRUE;
            }
        } else {
            // ScriptGetCMap works better than GetGlyphIndicesW 
            // for things like bitmap/vector fonts
            SCRIPT_CACHE sc = NULL;
            HRESULT rv = ScriptGetCMap(dc, &sc, str, 1, 0, glyph);
            if (rv == S_OK)
                hasGlyph = PR_TRUE;
        }

        SelectObject(dc, oldFont);
        ReleaseDC(NULL, dc);

        if (hasGlyph) {
            mCharacterMap.set(aCh);
            return PR_TRUE;
        }
    } else {
        // font had a cmap so simply check that
        return mCharacterMap.test(aCh);
    }

    return PR_FALSE;
}
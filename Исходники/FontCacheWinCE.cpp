PassRefPtr<SimpleFontData> FontCache::systemFallbackForCharacters(const FontDescription& description, const SimpleFontData* originalFontData, bool, const UChar* characters, int length)
{
    String familyName;
    WCHAR name[LF_FACESIZE];

    UChar character = characters[0];
    const FontPlatformData& origFont = originalFontData->platformData();

    if (IMLangFontLinkType* langFontLink = getFontLinkInterface()) {
        HGDIOBJ oldFont = GetCurrentObject(g_screenDC, OBJ_FONT);
        HFONT hfont = 0;
        DWORD codePages = 0;
        UINT codePage = 0;
        // Try MLang font linking first.
        langFontLink->GetCharCodePages(character, &codePages);
        if (codePages && u_getIntPropertyValue(character, UCHAR_UNIFIED_IDEOGRAPH)) {
            // The CJK character may belong to multiple code pages. We want to
            // do font linking against a single one of them, preferring the default
            // code page for the user's locale.
            const Vector<DWORD, 4>& CJKCodePageMasks = getCJKCodePageMasks();
            unsigned numCodePages = CJKCodePageMasks.size();
            for (unsigned i = 0; i < numCodePages; ++i) {
                hfont = createMLangFont(langFontLink, g_screenDC, origFont, CJKCodePageMasks[i]);
                if (!hfont)
                    continue;

                SelectObject(g_screenDC, hfont);
                GetTextFace(g_screenDC, LF_FACESIZE, name);

                if (hfont && !(codePages & CJKCodePageMasks[i])) {
                    // We asked about a code page that is not one of the code pages
                    // returned by MLang, so the font might not contain the character.
                    if (!currentFontContainsCharacter(langFontLink, g_screenDC, hfont, character, name))
                    {
                        SelectObject(g_screenDC, oldFont);
                        langFontLink->ReleaseFont(hfont);
                        hfont = 0;
                        continue;
                    }
                }
                break;
            }
        } else {
            hfont = createMLangFont(langFontLink, g_screenDC, origFont, codePages, character);
            SelectObject(g_screenDC, hfont);
            GetTextFace(g_screenDC, LF_FACESIZE, name);
        }
        SelectObject(g_screenDC, oldFont);

        if (hfont) {
            familyName = name;
            langFontLink->ReleaseFont(hfont);
        } else
            FontPlatformData::mapKnownFont(codePages, familyName);
    }

    if (familyName.isEmpty())
        familyName = FontPlatformData::defaultFontFamily();

    if (!familyName.isEmpty()) {
        // FIXME: temporary workaround for Thai font problem
        FontDescription fontDescription(description);
        if (ublock_getCode(c) == UBLOCK_THAI && fontDescription.weight() > FontWeightNormal)
            fontDescription.setWeight(FontWeightNormal);

        FontPlatformData* result = getCachedFontPlatformData(fontDescription, familyName);
        if (result && result->hash() != origFont.hash()) {
            if (RefPtr<SimpleFontData> fontData = getCachedFontData(result, DoNotRetain))
                return fontData.release();
        }
    }

    return 0;
}
static bool fontContainsCharacter(const FontPlatformData* fontData,
                                  const wchar_t* family, UChar32 character)
{
    // FIXME: For non-BMP characters, GetFontUnicodeRanges is of
    // no use. We have to read directly from the cmap table of a font.
    // Return true for now.
    if (character > 0xFFFF)
        return true;

    // This cache is just leaked on shutdown.
    static FontCmapCache* fontCmapCache = 0;
    if (!fontCmapCache)
        fontCmapCache = new FontCmapCache;

    HashMap<const wchar_t*, icu::UnicodeSet*>::iterator it = fontCmapCache->find(family);
    if (it != fontCmapCache->end()) 
        return it->second->contains(character);
    
    HFONT hfont = fontData->hfont(); 
    HDC hdc = GetDC(0);
    HGDIOBJ oldFont = static_cast<HFONT>(SelectObject(hdc, hfont));
    int count = GetFontUnicodeRanges(hdc, 0);
    if (!count && PlatformSupport::ensureFontLoaded(hfont))
        count = GetFontUnicodeRanges(hdc, 0);
    if (!count) {
        LOG_ERROR("Unable to get the font unicode range after second attempt");
        SelectObject(hdc, oldFont);
        ReleaseDC(0, hdc);
        return true;
    }

    static Vector<char, 512> glyphsetBuffer;
    glyphsetBuffer.resize(GetFontUnicodeRanges(hdc, 0));
    GLYPHSET* glyphset = reinterpret_cast<GLYPHSET*>(glyphsetBuffer.data());
    // In addition, refering to the OS/2 table and converting the codepage list
    // to the coverage map might be faster. 
    count = GetFontUnicodeRanges(hdc, glyphset);
    ASSERT(count > 0);
    SelectObject(hdc, oldFont);
    ReleaseDC(0, hdc);

    // FIXME: consider doing either of the following two:
    // 1) port back ICU 4.0's faster look-up code for UnicodeSet
    // 2) port Mozilla's CompressedCharMap or gfxSparseBitset
    unsigned i = 0;
    icu::UnicodeSet* cmap = new icu::UnicodeSet;
    while (i < glyphset->cRanges) {
        WCHAR start = glyphset->ranges[i].wcLow; 
        cmap->add(start, start + glyphset->ranges[i].cGlyphs - 1);
        i++;
    }
    cmap->freeze();
    // We don't lowercase |family| because all of them are under our control
    // and they're already lowercased. 
    fontCmapCache->set(family, cmap); 
    return cmap->contains(character);
}
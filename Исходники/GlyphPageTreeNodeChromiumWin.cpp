// Fills |length| glyphs starting at |offset| in a |page| in the Basic 
// Multilingual Plane (<= U+FFFF). The input buffer size should be the
// same as |length|. We can use the standard Windows GDI functions here. 
// Returns true if any glyphs were found.
static bool fillBMPGlyphs(unsigned offset,
                          unsigned length,
                          UChar* buffer,
                          GlyphPage* page,
                          const SimpleFontData* fontData,
                          bool recurse)
{
    HDC dc = GetDC((HWND)0);
    HGDIOBJ oldFont = SelectObject(dc, fontData->platformData().hfont());

    TEXTMETRIC tm = {0};
    if (!GetTextMetrics(dc, &tm)) {
        SelectObject(dc, oldFont);
        ReleaseDC(0, dc);

        if (recurse) {
            if (PlatformBridge::ensureFontLoaded(fontData->platformData().hfont()))
                return fillBMPGlyphs(offset, length, buffer, page, fontData, false);

            fillEmptyGlyphs(page);
            return false;
        } else {
            // FIXME: Handle gracefully the error if this call also fails.
            // See http://crbug.com/6401
            LOG_ERROR("Unable to get the text metrics after second attempt");
            fillEmptyGlyphs(page);
            return false;
        }
    }

    // FIXME: GetGlyphIndices() sets each item of localGlyphBuffer[]
    // with the one of the values listed below.
    //  * With the GGI_MARK_NONEXISTING_GLYPHS flag
    //    + If the font has a glyph available for the character,
    //      localGlyphBuffer[i] > 0x0.
    //    + If the font does not have glyphs available for the character,
    //      localGlyphBuffer[i] = 0x1F (TrueType Collection?) or
    //                            0xFFFF (OpenType?).
    //  * Without the GGI_MARK_NONEXISTING_GLYPHS flag
    //    + If the font has a glyph available for the character,
    //      localGlyphBuffer[i] > 0x0.
    //    + If the font does not have glyphs available for the character,
    //      localGlyphBuffer[i] = 0x80.
    //      (Windows automatically assigns the glyph for a box character to
    //      prevent ExtTextOut() from returning errors.)
    // To avoid from hurting the rendering performance, this code just
    // tells WebKit whether or not the all glyph indices for the given
    // characters are 0x80 (i.e. a possibly-invalid glyph) and let it
    // use alternative fonts for the characters.
    // Although this may cause a problem, it seems to work fine as far as I
    // have tested. (Obviously, I need more tests.)
    WORD localGlyphBuffer[GlyphPage::size];

    // FIXME: I find some Chinese characters can not be correctly displayed
    // when call GetGlyphIndices without flag GGI_MARK_NONEXISTING_GLYPHS,
    // because the corresponding glyph index is set as 0x20 when current font
    // does not have glyphs available for the character. According a blog post
    // http://blogs.msdn.com/michkap/archive/2006/06/28/649791.aspx
    // I think we should switch to the way about calling GetGlyphIndices with
    // flag GGI_MARK_NONEXISTING_GLYPHS, it should be OK according the
    // description of MSDN.
    // Also according to Jungshik and Hironori's suggestion and modification
    // we treat turetype and raster Font as different way when windows version
    // is less than Vista.
    GetGlyphIndices(dc, buffer, length, localGlyphBuffer, GGI_MARK_NONEXISTING_GLYPHS);

    // Copy the output to the GlyphPage
    bool haveGlyphs = false;
    int invalidGlyph = 0xFFFF;
    const DWORD cffTableTag = 0x20464643; // 4-byte identifier for OpenType CFF table ('CFF ').
    if (!isVistaOrNewer() && !(tm.tmPitchAndFamily & TMPF_TRUETYPE) && (GetFontData(dc, cffTableTag, 0, 0, 0) == GDI_ERROR))
        invalidGlyph = 0x1F;

    Glyph spaceGlyph = 0;  // Glyph for a space. Lazily filled.

    for (unsigned i = 0; i < length; i++) {
        UChar c = buffer[i];
        Glyph glyph = localGlyphBuffer[i];
        const SimpleFontData* glyphFontData = fontData;
        // When this character should be a space, we ignore whatever the font
        // says and use a space. Otherwise, if fonts don't map one of these
        // space or zero width glyphs, we will get a box.
        if (Font::treatAsSpace(c)) {
            // Hard code the glyph indices for characters that should be
            // treated like spaces.
            glyph = initSpaceGlyph(dc, &spaceGlyph);
        } else if (glyph == invalidGlyph) {
            // WebKit expects both the glyph index and FontData
            // pointer to be 0 if the glyph is not present
            glyph = 0;
            glyphFontData = 0;
        } else
            haveGlyphs = true;
        page->setGlyphDataForCharacter(offset + i, glyph, glyphFontData);
    }

    SelectObject(dc, oldFont);
    ReleaseDC(0, dc);
    return haveGlyphs;
}
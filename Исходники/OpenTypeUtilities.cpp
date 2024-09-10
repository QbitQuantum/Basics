// Rename the font and install the new font data into the system
HANDLE renameAndActivateFont(SharedBuffer* fontData, const String& fontName)
{
    Vector<char> rewrittenFontData;
    size_t nameTableSize = renameFont(fontData, fontName, rewrittenFontData);
    if (!nameTableSize)
        return 0;

    DWORD numFonts = 0;
    HANDLE fontHandle = AddFontMemResourceEx(rewrittenFontData.data(), fontData->size() + nameTableSize, 0, &numFonts);

    if (fontHandle && numFonts < 1) {
        RemoveFontMemResourceEx(fontHandle);
        return 0;
    }

    return fontHandle;
}
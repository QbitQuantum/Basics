PassRefPtr<SimpleFontData> FontCache::getLastResortFallbackFont(const FontDescription& description, ShouldRetain shouldRetain)
{
    FontDescription::GenericFamilyType generic = description.genericFamily();

    // FIXME: Would be even better to somehow get the user's default font here.
    // For now we'll pick the default that the user would get without changing
    // any prefs.
    DEFINE_STATIC_LOCAL(AtomicString, timesStr, "Times New Roman");
    DEFINE_STATIC_LOCAL(AtomicString, courierStr, "Courier New");
    DEFINE_STATIC_LOCAL(AtomicString, arialStr, "Arial");

    AtomicString& fontStr = timesStr;
    if (generic == FontDescription::SansSerifFamily)
        fontStr = arialStr;
    else if (generic == FontDescription::MonospaceFamily)
        fontStr = courierStr;

    RefPtr<SimpleFontData> simpleFont = getFontData(description, fontStr, false, shouldRetain);
    if (simpleFont)
        return simpleFont.release();

    // Fall back to system fonts as Win Safari does because this function must
    // return a valid font. Once we find a valid system font, we save its name
    // to a static variable and use it to prevent trying system fonts again.
    static wchar_t fallbackFontName[LF_FACESIZE] = {0};
    if (fallbackFontName[0])
        return getFontData(description, fallbackFontName, false, shouldRetain);

    // Fall back to the DEFAULT_GUI_FONT if no known Unicode fonts are available.
    if (HFONT defaultGUIFont = static_cast<HFONT>(GetStockObject(DEFAULT_GUI_FONT))) {
        LOGFONT defaultGUILogFont;
        GetObject(defaultGUIFont, sizeof(defaultGUILogFont), &defaultGUILogFont);
        if (simpleFont = fontDataFromDescriptionAndLogFont(description, shouldRetain, defaultGUILogFont, fallbackFontName))
            return simpleFont.release();
    }

    // Fall back to Non-client metrics fonts.
    NONCLIENTMETRICS nonClientMetrics = {0};
    nonClientMetrics.cbSize = sizeof(nonClientMetrics);
    if (SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(nonClientMetrics), &nonClientMetrics, 0)) {
        if (simpleFont = fontDataFromDescriptionAndLogFont(description, shouldRetain, nonClientMetrics.lfMessageFont, fallbackFontName))
            return simpleFont.release();
        if (simpleFont = fontDataFromDescriptionAndLogFont(description, shouldRetain, nonClientMetrics.lfMenuFont, fallbackFontName))
            return simpleFont.release();
        if (simpleFont = fontDataFromDescriptionAndLogFont(description, shouldRetain, nonClientMetrics.lfStatusFont, fallbackFontName))
            return simpleFont.release();
        if (simpleFont = fontDataFromDescriptionAndLogFont(description, shouldRetain, nonClientMetrics.lfCaptionFont, fallbackFontName))
            return simpleFont.release();
        if (simpleFont = fontDataFromDescriptionAndLogFont(description, shouldRetain, nonClientMetrics.lfSmCaptionFont, fallbackFontName))
            return simpleFont.release();
    }

    // Fall back to all the fonts installed in this PC. When a font has a
    // localized name according to the system locale as well as an English name,
    // both GetTextFace() and EnumFontFamilies() return the localized name. So,
    // FontCache::createFontPlatformData() does not filter out the fonts
    // returned by this EnumFontFamilies() call.
    HWndDC dc(0);
    if (dc) {
        GetLastResortFallbackFontProcData procData(this, &description, shouldRetain, fallbackFontName);
        EnumFontFamilies(dc, 0, getLastResortFallbackFontProc, reinterpret_cast<LPARAM>(&procData));

        if (procData.m_fontData)
            return procData.m_fontData.release();
    }

    ASSERT_NOT_REACHED();
    return 0;
}
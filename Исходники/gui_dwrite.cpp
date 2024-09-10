    HRESULT
DWriteContext::SetLOGFONT(const LOGFONTW &logFont, float fontSize)
{
    // Most of this function is copy from: http://msdn.microsoft.com/en-us/library/windows/desktop/dd941783(v=vs.85).aspx
    HRESULT hr = S_OK;

    IDWriteFont *font = NULL;
    IDWriteFontFamily *fontFamily = NULL;
    IDWriteLocalizedStrings *localizedFamilyNames = NULL;

    if (SUCCEEDED(hr))
    {
	hr = mGdiInterop->CreateFontFromLOGFONT(&logFont, &font);
    }

    // Get the font family to which this font belongs.
    if (SUCCEEDED(hr))
    {
	hr = font->GetFontFamily(&fontFamily);
    }

    // Get the family names. This returns an object that encapsulates one or
    // more names with the same meaning but in different languages.
    if (SUCCEEDED(hr))
    {
	hr = fontFamily->GetFamilyNames(&localizedFamilyNames);
    }

    // Get the family name at index zero. If we were going to display the name
    // we'd want to try to find one that matched the use locale, but for
    // purposes of creating a text format object any language will do.

    wchar_t familyName[100];
    if (SUCCEEDED(hr))
    {
	hr = localizedFamilyNames->GetString(0, familyName,
		ARRAYSIZE(familyName));
    }

    if (SUCCEEDED(hr))
    {
	// If no font size was passed in use the lfHeight of the LOGFONT.
	if (fontSize == 0)
	{
	    // Convert from pixels to DIPs.
	    fontSize = PixelsToDipsY(logFont.lfHeight);
	    if (fontSize < 0)
	    {
		// Negative lfHeight represents the size of the em unit.
		fontSize = -fontSize;
	    }
	    else
	    {
		// Positive lfHeight represents the cell height (ascent +
		// descent).
		DWRITE_FONT_METRICS fontMetrics;
		font->GetMetrics(&fontMetrics);

		// Convert the cell height (ascent + descent) from design units
		// to ems.
		float cellHeight = static_cast<float>(
			fontMetrics.ascent + fontMetrics.descent)
					       / fontMetrics.designUnitsPerEm;

		// Divide the font size by the cell height to get the font em
		// size.
		fontSize /= cellHeight;
	    }
	}
    }

    // The text format includes a locale name. Ideally, this would be the
    // language of the text, which may or may not be the same as the primary
    // language of the user. However, for our purposes the user locale will do.
    wchar_t localeName[LOCALE_NAME_MAX_LENGTH];
    if (SUCCEEDED(hr))
    {
	if (GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH) == 0)
	    hr = HRESULT_FROM_WIN32(GetLastError());
    }

    if (SUCCEEDED(hr))
    {
	// Create the text format object.
	hr = mDWriteFactory->CreateTextFormat(
		familyName,
		NULL, // no custom font collection
		font->GetWeight(),
		font->GetStyle(),
		font->GetStretch(),
		fontSize,
		localeName,
		&mTextFormat);
    }

    if (SUCCEEDED(hr))
    {
	mFontWeight = static_cast<DWRITE_FONT_WEIGHT>(logFont.lfWeight);
	mFontStyle = logFont.lfItalic ? DWRITE_FONT_STYLE_ITALIC
	    : DWRITE_FONT_STYLE_NORMAL;
    }

    SafeRelease(&localizedFamilyNames);
    SafeRelease(&fontFamily);
    SafeRelease(&font);

    return hr;
}
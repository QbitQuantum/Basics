void QWindowsFontEngineDirectWrite::initFontInfo(const QFontDef &request,
        int dpi, IDWriteFont *font)
{
    fontDef = request;

    IDWriteFontFamily *fontFamily = NULL;
    HRESULT hr = font->GetFontFamily(&fontFamily);

    IDWriteLocalizedStrings *familyNames = NULL;
    if (SUCCEEDED(hr))
        hr = fontFamily->GetFamilyNames(&familyNames);

    UINT32 index = 0;

    if (SUCCEEDED(hr)) {
        BOOL exists = false;

        wchar_t localeName[LOCALE_NAME_MAX_LENGTH];
        int defaultLocaleSuccess = GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH);
        if (defaultLocaleSuccess)
            hr = familyNames->FindLocaleName(localeName, &index, &exists);

        if (SUCCEEDED(hr) && !exists)
            hr = familyNames->FindLocaleName(L"en-us", &index, &exists);

        if (!exists)
            index = 0;
    }

    // Get the family name.
    if (SUCCEEDED(hr)) {
        UINT32 length = 0;

        hr = familyNames->GetStringLength(index, &length);

        if (SUCCEEDED(hr)) {
            QVarLengthArray<wchar_t, 128> name(length+1);

            hr = familyNames->GetString(index, name.data(), name.size());

            if (SUCCEEDED(hr))
                fontDef.family = QString::fromWCharArray(name.constData());
        }
    }

    if (familyNames != NULL)
        familyNames->Release();
    if (fontFamily)
        fontFamily->Release();

    if (FAILED(hr))
        qErrnoWarning(hr, "initFontInfo: Failed to get family name");

    if (fontDef.pointSize < 0)
        fontDef.pointSize = fontDef.pixelSize * 72. / dpi;
    else if (fontDef.pixelSize == -1)
        fontDef.pixelSize = qRound(fontDef.pointSize * dpi / 72.);
}
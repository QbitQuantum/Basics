void QWinRTFontDatabase::populateFamily(const QString &familyName)
{
    IDWriteFontFamily *fontFamily = m_fontFamilies.value(familyName);
    if (!fontFamily) {
        qWarning("The font family %s was not found.", qPrintable(familyName));
        return;
    }

    bool fontRegistered = false;
    const int fontCount = fontFamily->GetFontCount();
    for (int j = 0; j < fontCount; ++j) {
        ComPtr<IDWriteFont> font;
        HRESULT hr = fontFamily->GetFont(j, &font);
        if (FAILED(hr)) {
            qWarning("Unable to get font: %s", qPrintable(qt_error_string(hr)));
            continue;
        }

        // Skip simulated faces
        if (font->GetSimulations() != DWRITE_FONT_SIMULATIONS_NONE)
            continue;

        ComPtr<IDWriteFontFace> baseFontFace;
        hr = font->CreateFontFace(&baseFontFace);
        if (FAILED(hr)) {
            qWarning("Unable to create base font face: %s", qPrintable(qt_error_string(hr)));
            continue;
        }
        ComPtr<IDWriteFontFace1> fontFace;
        hr = baseFontFace.As(&fontFace);
        if (FAILED(hr)) {
            qWarning("Unable to create font face: %s", qPrintable(qt_error_string(hr)));
            continue;
        }

        // We can't deal with multi-file fonts
        quint32 fileCount;
        hr = fontFace->GetFiles(&fileCount, NULL);
        if (FAILED(hr)) {
            qWarning("Unable to get font file count: %s", qPrintable(qt_error_string(hr)));
            continue;
        }
        if (fileCount != 1)
            continue;

        ComPtr<IDWriteLocalizedStrings> informationalStrings;
        BOOL exists;
        hr = font->GetInformationalStrings(DWRITE_INFORMATIONAL_STRING_MANUFACTURER,
                                           &informationalStrings, &exists);
        if (FAILED(hr)) {
            qWarning("Unable to get font foundry: %s", qPrintable(qt_error_string(hr)));
            continue;
        }
        QString foundryName;
        if (exists) {
            quint32 length;
            hr = informationalStrings->GetStringLength(0, &length);
            if (FAILED(hr))
                qWarning("Unable to get foundry name length: %s", qPrintable(qt_error_string(hr)));
            if (SUCCEEDED(hr)) {
                QVector<wchar_t> buffer(length + 1);
                hr = informationalStrings->GetString(0, buffer.data(), buffer.size());
                if (FAILED(hr))
                    qWarning("Unable to get foundry name: %s", qPrintable(qt_error_string(hr)));
                if (SUCCEEDED(hr))
                    foundryName = QString::fromWCharArray(buffer.data(), length);
            }
        }

        QFont::Weight weight;
        switch (font->GetWeight()) {
        case DWRITE_FONT_WEIGHT_THIN:
        case DWRITE_FONT_WEIGHT_EXTRA_LIGHT:
        case DWRITE_FONT_WEIGHT_LIGHT:
        case DWRITE_FONT_WEIGHT_SEMI_LIGHT:
            weight = QFont::Light;
            break;
        default:
        case DWRITE_FONT_WEIGHT_NORMAL:
        case DWRITE_FONT_WEIGHT_MEDIUM:
            weight = QFont::Normal;
            break;
        case DWRITE_FONT_WEIGHT_DEMI_BOLD:
            weight = QFont::DemiBold;
            break;
        case DWRITE_FONT_WEIGHT_BOLD:
        case DWRITE_FONT_WEIGHT_EXTRA_BOLD:
            weight = QFont::Bold;
            break;
        case DWRITE_FONT_WEIGHT_BLACK:
        case DWRITE_FONT_WEIGHT_EXTRA_BLACK:
            weight = QFont::Black;
            break;
        }

        QFont::Style style;
        switch (font->GetStyle()) {
        default:
        case DWRITE_FONT_STYLE_NORMAL:
            style = QFont::StyleNormal;
            break;
        case DWRITE_FONT_STYLE_OBLIQUE:
            style = QFont::StyleOblique;
            break;
        case DWRITE_FONT_STYLE_ITALIC:
            style = QFont::StyleItalic;
            break;
        }

        QFont::Stretch stretch;
        switch (font->GetStretch()) {
        default:
        case DWRITE_FONT_STRETCH_UNDEFINED:
        case DWRITE_FONT_STRETCH_NORMAL:
            stretch = QFont::Unstretched;
            break;
        case DWRITE_FONT_STRETCH_ULTRA_CONDENSED:
            stretch = QFont::UltraCondensed;
            break;
        case DWRITE_FONT_STRETCH_EXTRA_CONDENSED:
            stretch = QFont::ExtraCondensed;
            break;
        case DWRITE_FONT_STRETCH_CONDENSED:
            stretch = QFont::Condensed;
            break;
        case DWRITE_FONT_STRETCH_SEMI_CONDENSED:
            stretch = QFont::SemiCondensed;
            break;
        case DWRITE_FONT_STRETCH_SEMI_EXPANDED:
            stretch = QFont::SemiExpanded;
            break;
        case DWRITE_FONT_STRETCH_EXPANDED:
            stretch = QFont::Expanded;
            break;
        case DWRITE_FONT_STRETCH_EXTRA_EXPANDED:
            stretch = QFont::ExtraExpanded;
            break;
        case DWRITE_FONT_STRETCH_ULTRA_EXPANDED:
            stretch = QFont::UltraExpanded;
            break;
        }

        const bool fixedPitch = fontFace->IsMonospacedFont();

        quint32 unicodeRange[4];
        quint32 actualRangeCount;
        hr = fontFace->GetUnicodeRanges(
                    2, reinterpret_cast<DWRITE_UNICODE_RANGE *>(unicodeRange), &actualRangeCount);
        if (FAILED(hr) && hr != E_NOT_SUFFICIENT_BUFFER) { // Ignore insufficient buffer; we only need 4 indices
            qWarning("Unable to get font unicode range: %s", qPrintable(qt_error_string(hr)));
            continue;
        }
        quint32 codePageRange[2] = { 0, 0 };
        QSupportedWritingSystems writingSystems =
                QPlatformFontDatabase::writingSystemsFromTrueTypeBits(unicodeRange, codePageRange);

        IDWriteFontFile *fontFile;
        hr = fontFace->GetFiles(&fileCount, &fontFile);
        if (FAILED(hr)) {
            qWarning("Unable to get font file: %s", qPrintable(qt_error_string(hr)));
            continue;
        }

        FontDescription description = { fontFace->GetIndex(), QUuid::createUuid().toByteArray() };
        m_fonts.insert(fontFile, description);
        registerFont(familyName, QString(), foundryName, weight, style, stretch,
                     true, true, 0, fixedPitch, writingSystems, fontFile);
        fontRegistered = true;
    }

    // Always populate something to avoid an assert
    if (!fontRegistered) {
        registerFont(familyName, QString(), QString(), QFont::Normal, QFont::StyleNormal,
                     QFont::Unstretched, false, false, 0, false, QSupportedWritingSystems(), 0);
    }
}
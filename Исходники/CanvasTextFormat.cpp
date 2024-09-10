    ComPtr<IDWriteTextFormat> CanvasTextFormat::GetRealizedTextFormat()
    {
        if (m_format)
            return m_format;

        ComPtr<IDWriteFactory2> factory;
        ThrowIfFailed(DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(&factory),
            static_cast<IUnknown**>(&factory)));

        ThrowIfFailed(factory->CreateTextFormat(
            static_cast<const wchar_t*>(m_fontFamilyName),
            m_fontCollection.Get(),
            ToFontWeight(m_fontWeight),
            ToFontStyle(m_fontStyle),
            ToFontStretch(m_fontStretch),
            m_fontSize,
            static_cast<const wchar_t*>(m_localeName),
            &m_format));

        RealizeFlowDirection();
        RealizeIncrementalTabStop();
        RealizeLineSpacing();
        RealizeParagraphAlignment();
        RealizeReadingDirection();
        RealizeTextAlignment();
        RealizeTrimming();
        RealizeWordWrapping();

        return m_format;
    }
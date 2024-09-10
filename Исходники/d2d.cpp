void d2d::InitTextDevice(const wstring fontName, FLOAT fontSize)
{
    if (m_pD2DFactory == nullptr)
    {
        return;
    }
    
    // Create a DirectWrite factory.
    HRESULT hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(m_pDWriteFactory), reinterpret_cast<IUnknown**>(&m_pDWriteFactory));
    if (FAILED(hr) || m_pDWriteFactory == nullptr)
    {
        return;
    }

    // Create a DirectWrite text format object.
    hr = m_pDWriteFactory->CreateTextFormat(
            fontName.c_str(),
            NULL,
            DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            fontSize,
            L"", //locale
            &m_pTextFormat);
    
    if (FAILED(hr) || m_pTextFormat == nullptr)
    {
        return;
    }

    // Center the text horizontally and vertically.
    m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

    hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBlackBrush);

    pokerlog << "InitTextDevice OK." << endl;
}
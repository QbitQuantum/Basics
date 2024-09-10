result_t Render2D::init(HWND window)
{
    // Pass the window handler for future processing.
    a_window = window;

    HRESULT hRes = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &ap_d2dFactory);
    if (FAILED(hRes))
    {
        return RET_FAILURE;
    }

    hRes = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&ap_dwFactory));
    if (FAILED(hRes))
    {
        return RET_FAILURE;
    }

    hRes = ap_dwFactory->CreateTextFormat(
        L"Gabriola",
        nullptr,
        DWRITE_FONT_WEIGHT_REGULAR,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        72.0f,
        L"en-us",
        &ap_dwTextFormat);
    if (FAILED(hRes))
    {
        return RET_FAILURE;
    }

    hRes = ap_dwTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    if (FAILED(hRes))
    {
        return RET_FAILURE;
    }

    hRes = ap_dwTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    if (FAILED(hRes))
    {
        return RET_FAILURE;
    }

    return RET_SUCCESS;
}
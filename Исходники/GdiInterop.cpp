HRESULT DWriteCreateResources(HDC hdc, wchar_t *text, HFONT hfont)
{
    HRESULT hr = S_OK;

    // If the DirectWrite factory doesn't exist, create the resources,
    // only create these resources once.
    if (!g_pDWriteFactory)
    {
        HWND hwnd;
        RECT r;

        // DirectWrite variables.
        IDWriteFontFamily* pFontFamily = NULL;
        IDWriteFont* pFont = NULL;
        IDWriteLocalizedStrings* pFamilyNames = NULL;
        
        // Logical (GDI) font.
        LOGFONT lf = {};

        UINT32 length = 0;
        UINT32 index = 0;
        float fontSize = 0;

        // length of the string
        UINT32 textLength = 0;

        wchar_t *name = NULL;

        // Get a handle to the DC and the window rect.
        hwnd = WindowFromDC(hdc);
        GetClientRect(hwnd, &r);

        // Calculate the string length.
        textLength = UINT32(wcslen(text));

        // Create the DirectWrite factory.
        hr = DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(IDWriteFactory),
            reinterpret_cast<IUnknown**>(&g_pDWriteFactory)
            );

        // Create a GDI interop interface.
        if (SUCCEEDED(hr))
        {
            hr = g_pDWriteFactory->GetGdiInterop(&g_pGdiInterop);
        }
        
        if (SUCCEEDED(hr))
        {
            // Get a logical font from the font handle.
            GetObject(hfont, sizeof(LOGFONT), &lf);
        }

        // Convert to a DirectWrite font.
        if (SUCCEEDED(hr))
        {
            hr = g_pGdiInterop->CreateFontFromLOGFONT(&lf, &pFont);
        }
        
        // Get the font family.
        if (SUCCEEDED(hr))
        {
            hr = pFont->GetFontFamily(&pFontFamily);
        }

        // Get a list of localized family names.
        if (SUCCEEDED(hr))
        {
            hr = pFontFamily->GetFamilyNames(&pFamilyNames);
        }

        // Select the first locale.  This is OK, because we are not displaying the family name.
        index = 0;
        
        // Get the length of the family name.
        if (SUCCEEDED(hr))
        {
            hr = pFamilyNames->GetStringLength(index, &length);
        }

        if (SUCCEEDED(hr))
        {
            // Allocate a new string.
            name = new (std::nothrow) wchar_t[length+1];
		    if (name == NULL)
            {
			    hr = E_OUTOFMEMORY;
            }
        }

        // Get the actual family name.
        if (SUCCEEDED(hr))
        {
            hr = pFamilyNames->GetString(index, name, length+1);
        }

        if (SUCCEEDED(hr))
        {
            // Calculate the font size.
            fontSize = (float) -MulDiv(lf.lfHeight, 96, GetDeviceCaps(hdc, LOGPIXELSY));
        }

        // Create a text format using the converted font information.
        if (SUCCEEDED(hr))
        {
            hr = g_pDWriteFactory->CreateTextFormat(
                name,                // Font family name.
                NULL,                        
                pFont->GetWeight(),
                pFont->GetStyle(),
                pFont->GetStretch(),
                fontSize,
                L"en-us",
                &g_pTextFormat
                );
        }

        // Create a text layout.
        if (SUCCEEDED(hr))
        {
            hr = g_pDWriteFactory->CreateTextLayout(
                text,
                textLength,
                g_pTextFormat,
                1024.0f,
                480.0f,
                &g_pTextLayout
                );
        }

        // Underline and strikethrough are part of a LOGFONT structure, but are not
        // part of a DWrite font object so we must set them using the text layout.
        if(lf.lfUnderline)
        {
            DWRITE_TEXT_RANGE textRange = {0, textLength};
            g_pTextLayout->SetUnderline(true, textRange);
        }

        if(lf.lfStrikeOut)
        {
            DWRITE_TEXT_RANGE textRange = {0, textLength};
            g_pTextLayout->SetStrikethrough(true, textRange);
        }
        
        // Create a bitmap render target for our custom renderer.
        if (SUCCEEDED(hr))
        {
            hr = g_pGdiInterop->CreateBitmapRenderTarget(hdc, r.right, r.bottom, &g_pBitmapRenderTarget);
        }
        
        // Create default rendering params for our custom renderer.
        if (SUCCEEDED(hr))
        {
            hr = g_pDWriteFactory->CreateRenderingParams(&g_pRenderingParams);
        }

        if (SUCCEEDED(hr))
        {
            // Initialize the custom renderer class.
		    g_pGdiTextRenderer = new (std::nothrow) GdiTextRenderer(g_pBitmapRenderTarget, g_pRenderingParams);
        }

        // Clean up local interfaces.
        SafeRelease(&pFontFamily);
        SafeRelease(&pFont);
        SafeRelease(&pFamilyNames);
    }

    return hr;
}
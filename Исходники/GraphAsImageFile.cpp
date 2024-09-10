HRESULT SaveToImageFile(PlotData **data
						, unsigned int imageWidth, unsigned int imageHeight
						, float rangeX, float rangeY
						, float leftMargin, float bottomMargin
						, float xTick, float yTick)
{
    HRESULT hr = S_OK;
    //
    // Create Factories
    //

    IWICImagingFactory *pWICFactory = NULL;
    ID2D1Factory *pD2DFactory = NULL;
    IDWriteFactory *pDWriteFactory = NULL;
    IWICBitmap *pWICBitmap = NULL;
    ID2D1RenderTarget *pRT = NULL;
    IDWriteTextFormat *pTextFormat = NULL;
    ID2D1SolidColorBrush *pSolidBrush = NULL;
    IWICBitmapEncoder *pEncoder = NULL;
    IWICBitmapFrameEncode *pFrameEncode = NULL;
    IWICStream *pStream = NULL;

    hr = CoCreateInstance(
        CLSID_WICImagingFactory,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_IWICImagingFactory,
        reinterpret_cast<void **>(&pWICFactory)
        );

    if (SUCCEEDED(hr))
    {
        hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
    }

    if (SUCCEEDED(hr))
    {
        hr = DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(pDWriteFactory),
            reinterpret_cast<IUnknown **>(&pDWriteFactory)
            );
    }

    //
    // Create IWICBitmap and RT
    //

    if (SUCCEEDED(hr))
    {
        hr = pWICFactory->CreateBitmap(
			imageWidth,
			imageHeight,
            GUID_WICPixelFormat32bppBGR,
            WICBitmapCacheOnLoad,
            &pWICBitmap
            );
    }

    if (SUCCEEDED(hr))
    {
        hr = pD2DFactory->CreateWicBitmapRenderTarget(
            pWICBitmap,
            D2D1::RenderTargetProperties(),
            &pRT
            );
    }

    if (SUCCEEDED(hr))
    {
        //
        // Create text format
        //

        static const WCHAR sc_fontName[] = L"Arial";
        static const FLOAT sc_fontSize = 20;

        hr = pDWriteFactory->CreateTextFormat(
            sc_fontName,
            NULL,
            DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            sc_fontSize,
            L"", //locale
            &pTextFormat
            );
    }
    if (SUCCEEDED(hr))
    {
        pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

        pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

        //
        // Create a path geometry representing an hour glass
        //

    }
    if (SUCCEEDED(hr))
    {
        hr = pRT->CreateSolidColorBrush(
            D2D1::ColorF(D2D1::ColorF::Black),
            &pSolidBrush
            );
    }
    if (SUCCEEDED(hr))
    {
        //
        // Render into the bitmap
        //

        pRT->BeginDraw();

        pRT->Clear(D2D1::ColorF(D2D1::ColorF::White));

        D2D1_SIZE_F rtSize = pRT->GetSize();


        //static const WCHAR sc_helloWorld[] = L"Hello, World!";
        //pRT->DrawText(
        //    sc_helloWorld,
        //    ARRAYSIZE(sc_helloWorld) - 1,
        //    pTextFormat,
        //    D2D1::RectF(0, 0, rtSize.width, rtSize.height),
        //    pBlackBrush);

		float scaleX = (rtSize.width - leftMargin) / rangeX;
		float scaleY = (rtSize.height - bottomMargin) / rangeY;
        //
        // Reset back to the identity transform
        //
		pRT->DrawLine(D2D1::Point2F(leftMargin, 0.0f), D2D1::Point2F(leftMargin, rtSize.height - bottomMargin), pSolidBrush);
		pRT->DrawLine(D2D1::Point2F(leftMargin, rtSize.height - bottomMargin), D2D1::Point2F(rtSize.width, rtSize.height - bottomMargin), pSolidBrush);

		pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::LightGray, 0.4f));
		size_t countTicks = rangeY / yTick;
		for(size_t tick = 1; tick <= countTicks; ++tick)
		{
			float y = rtSize.height - bottomMargin - static_cast<float>(tick) * yTick * scaleY;
			pRT->DrawLine(D2D1::Point2F(leftMargin - 3.0f, y), D2D1::Point2F(rtSize.width, y), pSolidBrush);
		}
		countTicks = rangeX / xTick;
		for(size_t tick = 1; tick <= countTicks; ++tick)
		{
			float x = leftMargin + static_cast<float>(tick) * xTick * scaleX;
			pRT->DrawLine(D2D1::Point2F(x, 0.0f), D2D1::Point2F(x, rtSize.height - bottomMargin + 3.0f), pSolidBrush);
		}

		//D2D1_MATRIX_3X2_F rotation = D2D1::Matrix3x2F::Rotation(-90.0f);
		D2D1_MATRIX_3X2_F translation = D2D1::Matrix3x2F::Translation(leftMargin, rtSize.height - bottomMargin);
		//D2D1_MATRIX_3X2_F scale = D2D1::Matrix3x2F::Scale(D2D1::SizeF(600.0f, 1.0f));
		pRT->SetTransform(translation);
		GraphData(data, pD2DFactory, pRT, pSolidBrush, scaleX, scaleY );

        hr = pRT->EndDraw();
    }
    if (SUCCEEDED(hr))
    {

        //
        // Save image to file
        //

        hr = pWICFactory->CreateStream(&pStream);
    }

    WICPixelFormatGUID format = GUID_WICPixelFormatDontCare;
    if (SUCCEEDED(hr))
    {
        static const WCHAR filename[] = L"output.png";
        hr = pStream->InitializeFromFilename(filename, GENERIC_WRITE);
    }
    if (SUCCEEDED(hr))
    {
        hr = pWICFactory->CreateEncoder(GUID_ContainerFormatPng, NULL, &pEncoder);
    }
    if (SUCCEEDED(hr))
    {
        hr = pEncoder->Initialize(pStream, WICBitmapEncoderNoCache);
    }
    if (SUCCEEDED(hr))
    {
        hr = pEncoder->CreateNewFrame(&pFrameEncode, NULL);
    }
    if (SUCCEEDED(hr))
    {
        hr = pFrameEncode->Initialize(NULL);
    }
    if (SUCCEEDED(hr))
    {
        hr = pFrameEncode->SetSize(imageWidth, imageHeight);
    }
    if (SUCCEEDED(hr))
    {
        hr = pFrameEncode->SetPixelFormat(&format);
    }
    if (SUCCEEDED(hr))
    {
        hr = pFrameEncode->WriteSource(pWICBitmap, NULL);
    }
    if (SUCCEEDED(hr))
    {
        hr = pFrameEncode->Commit();
    }
    if (SUCCEEDED(hr))
    {
        hr = pEncoder->Commit();
    }

    SafeRelease(&pWICFactory);
    SafeRelease(&pD2DFactory);
    SafeRelease(&pDWriteFactory);
    SafeRelease(&pWICBitmap);
    SafeRelease(&pRT);
    SafeRelease(&pTextFormat);
    SafeRelease(&pSolidBrush);
    SafeRelease(&pEncoder);
    SafeRelease(&pFrameEncode);
    SafeRelease(&pStream);

    return hr;
}
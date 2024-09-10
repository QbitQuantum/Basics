    HRESULT DisplayerImpl::CreateDeviceIndependentResources() {
        HRESULT hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&mDWriteFactory);
        if (FAILED(hr))
            return hr;

        D2D1_FACTORY_OPTIONS options;
        memset(&options, 0, sizeof(options));

#ifdef _DEBUG
        options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#endif

        hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, options, mD2DFactory.GetAddressOf());
        if (FAILED(hr))
            return hr;

        mD2DFactory->GetDesktopDpi(&mDpiX, &mDpiY);
        return hr;
    }
    Direct2DFactories()
    {
        if (direct2dDll.open ("d2d1.dll"))
        {
            JUCE_DLL_FUNCTION (D2D1CreateFactory, d2d1CreateFactory, HRESULT, direct2dDll, (D2D1_FACTORY_TYPE, REFIID, D2D1_FACTORY_OPTIONS*, void**))

            if (d2d1CreateFactory != nullptr)
            {
                D2D1_FACTORY_OPTIONS options;
                options.debugLevel = D2D1_DEBUG_LEVEL_NONE;

                d2d1CreateFactory (D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof (ID2D1Factory), &options,
                                   (void**) d2dFactory.resetAndGetPointerAddress());
            }
        }
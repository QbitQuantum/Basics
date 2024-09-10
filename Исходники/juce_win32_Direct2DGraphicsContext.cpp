    SharedD2DFactory()
    {
        jassertfalse; //xxx Direct2D support isn't ready for use yet!

        D2D1CreateFactory (D2D1_FACTORY_TYPE_SINGLE_THREADED, d2dFactory.resetAndGetPointerAddress());
        DWriteCreateFactory (DWRITE_FACTORY_TYPE_SHARED, __uuidof (IDWriteFactory), (IUnknown**) directWriteFactory.resetAndGetPointerAddress());

        if (directWriteFactory != nullptr)
            directWriteFactory->GetSystemFontCollection (systemFonts.resetAndGetPointerAddress());
    }
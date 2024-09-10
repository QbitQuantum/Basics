 CustomFontFileLoader() : m_directWriteFactory(0), m_directWriteFontFileLoader(0)
 {
     HRESULT hres = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
                                        __uuidof(IDWriteFactory),
                                        reinterpret_cast<IUnknown **>(&m_directWriteFactory));
     if (FAILED(hres)) {
         qErrnoWarning(hres, "CustomFontFileLoader::CustomFontFileLoader: "
                             "DWriteCreateFactory failed.");
     } else {
         m_directWriteFontFileLoader = new DirectWriteFontFileLoader();
         m_directWriteFactory->RegisterFontFileLoader(m_directWriteFontFileLoader);
     }
 }
void CCommonServiceTests::Execute_WithBadQueryString_ReturnsError ()
{
    try {
        HRESULT l_hr;

        WineApi::IConfigPtr l_spConfig;
        l_hr = l_spConfig.CreateInstance (__uuidof (WineApi::Config));
        if (FAILED (l_hr)) _com_issue_error (l_hr);

        l_spConfig->ApiKey = API_KEY;
        l_spConfig->Version = VERSION;

        WineApi::ICatalogServicePtr l_spCatalogService;
        l_hr = l_spCatalogService.CreateInstance (__uuidof (WineApi::CatalogService));

        WineApi::ICatalogPtr l_spCatalog = l_spCatalogService
                                           ->Search1 (L"merlot")
                                           ->State (L"Bogus")
                                           ->Execute ();

        CPPUNIT_ASSERT (l_spCatalog->Status->ReturnCode == WineApi::ReturnCodeCriticalError);
        CPPUNIT_ASSERT (l_spCatalog->Status->Messages->Count == 1);
    }
    catch (const _com_error& l_ce) {
        HandleComErrorException (l_ce);
    }
}
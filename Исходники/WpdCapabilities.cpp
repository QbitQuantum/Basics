/**
 *  This method is called when we receive a WPD_COMMAND_CAPABILITIES_GET_SUPPORTED_FUNCTIONAL_CATEGORIES
 *  command.
 *
 *  The parameters sent to us are:
 *  - none.
 *
 *  The driver should:
 *  - Return an IPortableDevicePropVariantCollection (of type VT_CLSID) in
 *      WPD_PROPERTY_CAPABILITIES_FUNCTIONAL_CATEGORIES, containing
 *      the supported functional categories for this device.
 */
HRESULT WpdCapabilities::OnGetFunctionalCategories(
    _In_ IPortableDeviceValues*  pParams,
    _In_ IPortableDeviceValues*  pResults)
{
    HRESULT hr = S_OK;
    CComPtr<IPortableDevicePropVariantCollection> pFunctionalCategories;

    UNREFERENCED_PARAMETER(pParams);

    // CoCreate a collection to store the supported functional categories.
    if (hr == S_OK)
    {
        hr = CoCreateInstance(CLSID_PortableDevicePropVariantCollection,
                              NULL,
                              CLSCTX_INPROC_SERVER,
                              IID_IPortableDevicePropVariantCollection,
                              (VOID**) &pFunctionalCategories);
        CHECK_HR(hr, "Failed to CoCreate CLSID_PortableDevicePropVariantCollection");
    }

    // Add the supported functional categories to the collection.
    if (hr == S_OK)
    {
        for (DWORD dwIndex = 0; dwIndex < ARRAYSIZE(g_SupportedFunctionalCategories); dwIndex++)
        {
            PROPVARIANT pv = {0};
            PropVariantInit(&pv);
            // Don't call PropVariantClear, since we did not allocate the memory for these GUIDs

            pv.vt    = VT_CLSID;
            pv.puuid = (GUID*) &g_SupportedFunctionalCategories[dwIndex];

            hr = pFunctionalCategories->Add(&pv);
            CHECK_HR(hr, "Failed to add supported functional category at index %d", dwIndex);
            if (FAILED(hr))
            {
                break;
            }
        }
    }

    // Set the WPD_PROPERTY_CAPABILITIES_FUNCTIONAL_CATEGORIES value in the results.
    if (hr == S_OK)
    {
        hr = pResults->SetIUnknownValue(WPD_PROPERTY_CAPABILITIES_FUNCTIONAL_CATEGORIES, pFunctionalCategories);
        CHECK_HR(hr, "Failed to set WPD_PROPERTY_CAPABILITIES_FUNCTIONAL_CATEGORIES");
    }

    return hr;
}
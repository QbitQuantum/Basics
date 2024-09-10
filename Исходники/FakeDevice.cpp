HRESULT FakeDevice::GetFunctionalObjects(
    _In_    REFGUID                               guidFunctionalCategory,
    _In_    IPortableDevicePropVariantCollection* pFunctionalObjects)
{
    HRESULT     hr = S_OK;
    PROPVARIANT pv = {0};

    if(pFunctionalObjects == NULL)
    {
        hr = E_POINTER;
        CHECK_HR(hr, "Cannot have NULL parameter");
        return hr;
    }

    PropVariantInit(&pv);
    // Don't call PropVariantClear, since we did not allocate the memory for these object identifiers

    // Add WPD_DEVICE_OBJECT_ID to the functional object identifiers collection
    if ((guidFunctionalCategory  == WPD_FUNCTIONAL_CATEGORY_DEVICE) ||
        (guidFunctionalCategory  == WPD_FUNCTIONAL_CATEGORY_ALL))
    {
        pv.vt       = VT_LPWSTR;
        pv.pwszVal  = WPD_DEVICE_OBJECT_ID;
        hr = pFunctionalObjects->Add(&pv);
        CHECK_HR(hr, "Failed to add device object ID");
    }

    // Add CONTACTS_SERVICE_OBJECT_ID to the functional object identifiers collection
    if (hr == S_OK)
    {
        if ((guidFunctionalCategory  == SERVICE_Contacts) ||
            (guidFunctionalCategory  == WPD_FUNCTIONAL_CATEGORY_ALL))
        {
            pv.vt       = VT_LPWSTR;
            pv.pwszVal  = CONTACTS_SERVICE_OBJECT_ID;
            hr = pFunctionalObjects->Add(&pv);
            CHECK_HR(hr, "Failed to add contacts service object ID");
        }
    }

    // Add STORAGE_OBJECT_ID to the functional object identifiers collection
    // if request is not scoped by the contacts service
    if ((guidFunctionalCategory  == WPD_FUNCTIONAL_CATEGORY_STORAGE) ||
        (guidFunctionalCategory  == WPD_FUNCTIONAL_CATEGORY_ALL))
    {
        pv.vt       = VT_LPWSTR;
        pv.pwszVal  = STORAGE_OBJECT_ID;
        hr = pFunctionalObjects->Add(&pv);
        CHECK_HR(hr, "Failed to add storage object ID");
    }

    return hr;
}
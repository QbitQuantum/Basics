HRESULT SetPropertyValue(PCWSTR pszFilename, PCWSTR pszCanonicalName, PCWSTR pszValue)
{
    // Convert the Canonical name of the property to PROPERTYKEY
    PROPERTYKEY key;
    HRESULT hr = PSGetPropertyKeyFromName(pszCanonicalName, &key);
    if (SUCCEEDED(hr))
    {
        IPropertyStore* pps = NULL;

        // Call the helper to get the property store for the
        // initialized item
        hr = GetPropertyStore(pszFilename, GPS_READWRITE, &pps);
        if (SUCCEEDED(hr))
        {
            PROPVARIANT propvarValue = {0};
            hr = InitPropVariantFromString(pszValue, &propvarValue);
            if (SUCCEEDED(hr))
            {
                hr = PSCoerceToCanonicalValue(key, &propvarValue);
                if (SUCCEEDED(hr))
                {
                    // Set the value to the property store of the item.
                    hr = pps->SetValue(key, propvarValue);
                    if (SUCCEEDED(hr))
                    {
                        // Commit does the actual writing back to the file stream.
                        hr = pps->Commit();
                        if (SUCCEEDED(hr))
                        {
                            wprintf(L"Property %s value %s written successfully \n", pszCanonicalName, pszValue);
                        }
                        else
                        {
                            wprintf(L"Error %x: Commit to the propertystore failed.\n", hr);
                        }
                    }
                    else
                    {
                        wprintf(L"Error %x: Set value to the propertystore failed.\n", hr);
                    }
                }
                PropVariantClear(&propvarValue);
            }
            pps->Release();
        }
        else
        {
            wprintf(L"Error %x: getting the propertystore for the item.\n", hr);
        }
    }
     else
    {
        wprintf(L"Invalid property specified: %s\n", pszCanonicalName);
    }
    return hr;
}
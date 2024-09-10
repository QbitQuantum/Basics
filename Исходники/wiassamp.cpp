HRESULT ReadSomeWiaProperties( IWiaPropertyStorage *pWiaPropertyStorage )
{
    //
    // Validate arguments
    //
    if (NULL == pWiaPropertyStorage)
    {
        return E_INVALIDARG;
    }

    //
    // Declare PROPSPECs and PROPVARIANTs, and initialize them to zero.
    //
    PROPSPEC PropSpec[3] = {0};
    PROPVARIANT PropVar[3] = {0};

    //
    // How many properties are we querying for?
    //
    const ULONG c_nPropertyCount = sizeof(PropSpec)/sizeof(PropSpec[0]);

    //
    // Define which properties we want to read:
    // Device ID.  This is what we'd use to create
    // the device.
    //
    PropSpec[0].ulKind = PRSPEC_PROPID;
    PropSpec[0].propid = WIA_DIP_DEV_ID;

    //
    // Device Name
    //
    PropSpec[1].ulKind = PRSPEC_PROPID;
    PropSpec[1].propid = WIA_DIP_DEV_NAME;

    //
    // Device description
    //
    PropSpec[2].ulKind = PRSPEC_PROPID;
    PropSpec[2].propid = WIA_DIP_DEV_DESC;

    //
    // Ask for the property values
    //
    HRESULT hr = pWiaPropertyStorage->ReadMultiple( c_nPropertyCount, PropSpec, PropVar );
    if (SUCCEEDED(hr))
    {
        //
        // IWiaPropertyStorage::ReadMultiple will return S_FALSE if some
        // properties could not be read, so we have to check the return
        // types for each requested item.
        //
        
        //
        // Check the return type for the device ID
        //
        if (VT_BSTR == PropVar[0].vt)
        {
            //
            // Do something with the device ID
            //
            _tprintf( TEXT("WIA_DIP_DEV_ID: %ws\n"), PropVar[0].bstrVal );
        }

        //
        // Check the return type for the device name
        //
        if (VT_BSTR == PropVar[1].vt)
        {
            //
            // Do something with the device name
            //
            _tprintf( TEXT("WIA_DIP_DEV_NAME: %ws\n"), PropVar[1].bstrVal );
        }

        //
        // Check the return type for the device description
        //
        if (VT_BSTR == PropVar[2].vt)
        {
            //
            // Do something with the device description
            //
            _tprintf( TEXT("WIA_DIP_DEV_DESC: %ws\n"), PropVar[2].bstrVal );
        }
        
        //
        // Free the returned PROPVARIANTs
        //
        FreePropVariantArray( c_nPropertyCount, PropVar );
    }
    else
    {
        ReportError( TEXT("Error calling IWiaPropertyStorage::ReadMultiple"), hr );
    }

    //
    // Return the result of reading the properties
    //
    return hr;
}
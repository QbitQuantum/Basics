//------------------------------------------------------------------------------
// CDeviceContextMenu::GetDeviceHardwareID
//
//      Get device hardware id from the devnode(s) of the device. You can get 
//      device properties that cannot be obtained directly from the shell item object
//      throught the device devnode(s).
//
//      Note there are two pieces of contextual information from the shell
//      object you can use to find the devnodes for your device.
//
//      1) Function Paths (PKEY_Devices_FunctionPaths)
//          This property is a vector of strings of the Device Instance Paths
//          for your device's devnodes. This function below will show how to
//          use this property to access properties off the devnodes.
//
//      2) Interface Paths (PKEY_Devices_InterfacePaths)
//          This property is a vectory of strings of the Device Interface Paths
//          of all your device's devnodes. Use of this property use not shown in
//          this sample, but if you find the property helpful for your scenario
//          you can use it. 
//------------------------------------------------------------------------------
HRESULT CDeviceContextMenu::GetDeviceHardwareID(
    __in IShellItem2* pShellItem2,
    __out PWSTR* ppszHardwareID
    )
{
    DWORD           cbBuffer            = 0;
    HDEVINFO        devInfo             = {0}; 
    SP_DEVINFO_DATA devInfoData         = {0};
    DEVPROPTYPE     devPropType         = 0;
    HRESULT         hr                  = S_OK;
    PBYTE           pBuffer             = NULL;
    PROPVARIANT     pv                  = {0};
    PCWSTR          pszHwid             = NULL;

    PropVariantInit( &pv );

    //
    // First get the Function Paths (Device Instance Paths) needed to grab the
    // devnode info directly from PnP.
    //
    if( S_OK == hr )
    {
        hr = pShellItem2->GetProperty( PKEY_Devices_FunctionPaths, &pv );
    }
    if( S_OK == hr &&
        ((VT_VECTOR | VT_LPWSTR) != pv.vt ||
        ( 0 == pv.calpwstr.cElems ) ) )
    {
        // Function Paths doesn't exist or is the wrong type or empty. 
        // This should never happen, but its good practice to check anyway.
        hr = HRESULT_FROM_WIN32( ERROR_NOT_FOUND );
    }

    //
    // For simplicity in the sample, we'll just work with the first path in the
    // list. i.e. the first devnode in the list.
    //
    // IMPORTANT: In a real scenario, you need to keep in mind that your device
    // shown in the Devices and Printers folder is likely made up of one or more
    // Device Functions (devnodes). In this case, you may not be able to get all
    // properties from just any devnode. You'll need to look at all devnodes and
    // figure out which one contains the properties you're after. In this sample
    // we're just attempting to get one device hardware id from the devnode who's
    // Device Instance Path is in the FunctionPaths list retreived from the shell
    // object. 
    //

    //
    // Create an empty HDEVINFO set to use for the first devnode's info
    //
    if( S_OK == hr )
    {
        devInfo = SetupDiCreateDeviceInfoList( NULL, NULL );
        if( INVALID_HANDLE_VALUE == devInfo )
        {
            hr = HRESULT_FROM_WIN32( GetLastError() );
        }
    }

    //
    // Open the devnode's info
    //
    if( S_OK == hr )
    {
        devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

        if( FALSE == SetupDiOpenDeviceInfo(
                        devInfo,
                        pv.calpwstr.pElems[0],
                        NULL, 
                        0, 
                        &devInfoData 
                        ) )
        {
            hr = HRESULT_FROM_WIN32( GetLastError() );
        }
    }

    // You can ask for properties defined in devpkey.h. Some keys in 
    // FunctionDiscoveryKey.h are also available on devnodes; For example,
    // devnodes from PnP-X (Network Devices) will have PKEY_PNPX properties
    // set on them. These can be retreived with SetupDi* calls as well.
    // PROPERTYKEY can be safely cast to DEVPROPKEY. However, keep in mind
    // the types are defined differently. Variant types are essentially a
    // superset of DEVPROPTYPEs. The mapping on many property types is
    // straight forward. DEVPROP_TYPE_STRING and VT_LPWSTR
    // are the same, for example. Below we'll get a PnP-X property so it's
    // clear how this works. 
    //
    // One case where the mapping isn't exact, is VT_VECTOR | VT_LPWSTR
    // (vector of strings), which in the devnode is stored as a 
    // DEVPROP_TYPE_STRING_LIST (REG_MULTI_SZ style string list). Keep this
    // in mind when asking for PKEY types from a devnode vs. DEVPKEY types.
    //

    //
    // Get the hardware ids
    //
    if( S_OK == hr )
    {
        // Get the required buffer size 
        if( FALSE == SetupDiGetDeviceProperty(
                        devInfo,
                        &devInfoData,
                        &DEVPKEY_Device_HardwareIds,
                        &devPropType,
                        NULL,
                        0,
                        &cbBuffer,
                        0 
                        ) &&
            ERROR_INSUFFICIENT_BUFFER != GetLastError() )
        {
            hr = HRESULT_FROM_WIN32( GetLastError() );
        }
    }

    if( S_OK == hr )
    {
        pBuffer = new (std::nothrow) BYTE[cbBuffer];
        if( NULL == pBuffer )
        {
            hr = E_OUTOFMEMORY;
        }
        ZeroMemory( pBuffer, cbBuffer );
    }

    if( S_OK == hr )
    {
        if( FALSE == SetupDiGetDeviceProperty(
                        devInfo,
                        &devInfoData,
                        &DEVPKEY_Device_HardwareIds,
                        &devPropType,
                        pBuffer,
                        cbBuffer,
                        NULL,
                        0 
                        ) )
        {
            hr = HRESULT_FROM_WIN32( GetLastError() );
        }
    }

    if( S_OK == hr &&
        DEVPROP_TYPE_STRING_LIST == devPropType )
    {
        //
        // Get the first Hardware ID from the list
        //
        pszHwid = reinterpret_cast<PWSTR>(pBuffer);
        hr = SHStrDup( pszHwid, ppszHardwareID );
    }

    //
    // Cleanup
    //
    if( NULL != pBuffer )
    {
        delete[] pBuffer;
        pBuffer = NULL;
    }

    if( INVALID_HANDLE_VALUE != devInfo )
    {
        (void) SetupDiDestroyDeviceInfoList( devInfo );
    }

    PropVariantClear( &pv );

    return hr;
}// CDeviceContextMenu::GetDeviceHardwareID
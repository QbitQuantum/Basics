//////////////////////////////////////////////////////////////////////////////
//++
//
//  CPartitionInfo::HrGetFriendlyName
//
//  Description:
//      Get the friendly name of this partition.  This name will be the
//      logical disk names of all logical disks on this partition.
//
//  Arguments:
//      pbstrNameOut
//          Upon success will point to an allocated BSTR containing the name.
//
//  Return Value:
//      S_OK
//          Success.
//
//      Other
//          An error occurred.
//
//  Remarks:
//      If S_OK is returned the caller needs to call SysFreeString on pbstrNameOut.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CPartitionInfo::HrGetFriendlyName(
    BSTR * pbstrNameOut
    )
{
    HRESULT             hr = S_FALSE;
    DWORD               idx;
    IWbemClassObject *  piwco = NULL;
    WCHAR *             pwsz = NULL;
    WCHAR *             pwszTmp = NULL;
    DWORD               cch = 0;
    VARIANT             var;

    VariantInit( &var );

    if ( m_idxNextLogicalDisk == 0 )
    {
        goto Cleanup;
    } // if:

    if ( pbstrNameOut == NULL )
    {
        hr = E_POINTER;
        STATUS_REPORT_REF(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_GetFriendlyName
                , IDS_ERROR_NULL_POINTER
                , IDS_ERROR_NULL_POINTER_REF
                , hr
                );
        goto Cleanup;
    } // if:

    for ( idx = 0; idx < m_idxNextLogicalDisk; idx++ )
    {
        hr = ((*m_prgLogicalDisks)[ idx ])->TypeSafeQI( IWbemClassObject, &piwco );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        hr = HrGetWMIProperty( piwco, L"DeviceID", VT_BSTR, &var );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        cch += ( UINT ) wcslen( var.bstrVal ) + 2;                      // a space and the '\0'

        pwszTmp = (WCHAR *) HEAPREALLOC( pwsz, sizeof( WCHAR ) * cch, HEAP_ZERO_MEMORY );
        if ( pwszTmp == NULL  )
        {
            goto OutOfMemory;
        } // if:

        pwsz = pwszTmp;
        pwszTmp = NULL;

        hr = StringCchCatW( pwsz, cch, L" " );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        hr = StringCchCatW( pwsz, cch, var.bstrVal );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        VariantClear( &var );

        piwco->Release();
        piwco = NULL;
    } // for:

    *pbstrNameOut = SysAllocString( pwsz );
    if ( *pbstrNameOut == NULL )
    {
        goto OutOfMemory;
    } // if:

    goto Cleanup;

OutOfMemory:

    hr = E_OUTOFMEMORY;
    STATUS_REPORT_REF(
              TASKID_Major_Find_Devices
            , TASKID_Minor_HrGetFriendlyName
            , IDS_ERROR_OUTOFMEMORY
            , IDS_ERROR_OUTOFMEMORY_REF
            , hr
            );

Cleanup:

    VariantClear( &var );

    if ( piwco != NULL )
    {
        piwco->Release();
    } // if:

    if ( pwsz != NULL )
    {
        HeapFree( GetProcessHeap(), 0, pwsz );
    } // if:

    if ( pwszTmp != NULL )
    {
        HeapFree( GetProcessHeap(), 0, pwszTmp );
    } // if:

    return hr;

} //*** CPartitionInfo::HrGetFriendlyName
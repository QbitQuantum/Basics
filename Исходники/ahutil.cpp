HRESULT
GetElementRawTimeSpanProperty(
    IN IAppHostElement * pElement,
    IN LPCWSTR           pszPropertyName,
    OUT ULONGLONG *      pulonglong
)
{
    HRESULT hr = S_OK;
    BSTR    bstrPropertyName = NULL;
    IAppHostProperty * pProperty = NULL;
    VARIANT            varValue;

    VariantInit( &varValue );

    bstrPropertyName = SysAllocString( pszPropertyName );
    if ( bstrPropertyName == NULL )
    {
        hr = HRESULT_FROM_WIN32( ERROR_NOT_ENOUGH_MEMORY );
        goto Finished;
    }

    // Now ask for the property and if it succeeds it is returned directly back
    hr = pElement->GetPropertyByName( bstrPropertyName, &pProperty );
    if ( FAILED ( hr ) )
    {
       goto Finished;
    }

    // Now let's get the property and then extract it from the Variant.
    hr = pProperty->get_Value( &varValue );
    if ( FAILED ( hr ) )
    {
         goto Finished;
    }

    hr = VariantChangeType( &varValue, &varValue, 0, VT_UI8 );
    if ( FAILED ( hr ) )
    {
         goto Finished;
    }

    // extract the value
    *pulonglong = varValue.ullVal;


Finished:

    VariantClear( &varValue );

    if ( bstrPropertyName != NULL )
    {
        SysFreeString( bstrPropertyName );
        bstrPropertyName = NULL;
    }

    if ( pProperty != NULL )
    {
        pProperty->Release();
        pProperty = NULL;
    }

    return hr;

} // end of Config_GetRawTimeSpanProperty
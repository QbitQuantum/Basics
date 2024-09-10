/**
 *  This method is called when we receive a WPD_COMMAND_OBJECT_PROPERTIES_BULK_GET_VALUES_BY_OBJECT_FORMAT_NEXT
 *  command.
 *
 *  The parameters sent to us are:
 *  - WPD_PROPERTY_OBJECT_PROPERTIES_BULK_CONTEXT: the context the driver returned to
 *      the client in OnGetValuesByObjectFormatStart.
 *
 *  The driver should:
 *  - Return the next set of property values in WPD_PROPERTY_OBJECT_PROPERTIES_BULK_VALUES.
 *    If there are no more properties to be read an
 *    empty collection should be returned.
 *  - It is up to the driver to return as many object property values as it wants.  If zero values are returned
 *    it is assumed the bulk operation is complete and the WPD_COMMAND_OBJECT_PROPERTIES_BULK_GET_VALUES_BY_OBJECT_FORMAT_END
 *    will be called next.
 *
 *  - S_OK should be returned if the collection can be returned successfully.
 *  - Any error return indicates that the driver did not fill in any results, and the caller will
 *      not attempt to unpack any property values.
 */
HRESULT WpdObjectPropertiesBulk::OnGetValuesByObjectFormatNext(
    __in    IPortableDeviceValues*  pParams,
    __out   IPortableDeviceValues*  pResults)
{

    HRESULT                                  hr = S_OK;
    LPWSTR                                   pwszContext = NULL;
    BulkPropertiesContext*                   pContext    = NULL;
    DWORD                                    cObjects    = 0;
    CComPtr<IPortableDeviceValuesCollection> pCollection;

    if (hr == S_OK)
    {
        hr = pParams->GetStringValue(WPD_PROPERTY_OBJECT_PROPERTIES_BULK_CONTEXT, &pwszContext);
        CHECK_HR(hr, "Failed to get WPD_PROPERTY_OBJECT_PROPERTIES_BULK_CONTEXT from IPortableDeviceValues");
    }

    // Get the bulk property operation context
    if (hr == S_OK)
    {
        hr = GetClientContext(pParams, pwszContext, (IUnknown**) &pContext);
        CHECK_HR(hr, "Failed to get bulk property context");
    }

    // Make sure the the collection holds VT_LPWSTR values.
    if (hr == S_OK)
    {
        hr = pContext->ObjectIDs->ChangeType(VT_LPWSTR);
        CHECK_HR(hr, "Failed to change objectIDs collection to VT_LPWSTR");
    }

    if (hr == S_OK)
    {
        hr = pContext->ObjectIDs->GetCount(&cObjects);
        CHECK_HR(hr, "Failed to get number of objectIDs from bulk properties context");
    }

    if (hr == S_OK)
    {
        cObjects = cObjects - pContext->NextObject;
        if(cObjects > MAX_OBJECTS_TO_RETURN)
        {
            cObjects = MAX_OBJECTS_TO_RETURN;
        }
    }

    if (hr == S_OK)
    {
        hr = CoCreateInstance(CLSID_PortableDeviceValuesCollection,
                              NULL,
                              CLSCTX_INPROC_SERVER,
                              IID_IPortableDeviceValuesCollection,
                              (VOID**) &pCollection);
        CHECK_HR(hr, "Failed to CoCreate CLSID_PortableDeviceValuesCollection");
    }

    if (hr == S_OK)
    {
        for (DWORD dwIndex = pContext->NextObject, dwCount = 0; dwCount < cObjects; dwCount++, dwIndex++)
        {
            CComPtr<IPortableDeviceValues> pValues;
            PROPVARIANT pv = {0};
            PropVariantInit(&pv);
            hr = pContext->ObjectIDs->GetAt(dwIndex, &pv);
            CHECK_HR(hr, "Failed to get next object ID from bulk properties context");

            if (hr == S_OK)
            {
                hr = CoCreateInstance(CLSID_PortableDeviceValues,
                                      NULL,
                                      CLSCTX_INPROC_SERVER,
                                      IID_IPortableDeviceValues,
                                      (VOID**) &pValues);
                CHECK_HR(hr, "Failed to CoCreate CLSID_PortableDeviceValuesCollection");
            }

            if (hr == S_OK)
            {
                // If a key list was supplied, get the specified object properties, other get all
                // properties.
                if(pContext->Properties != NULL)
                {
                    hr = m_pDevice->GetPropertyValues(pContext->Scope, pv.pwszVal, pContext->Properties, pValues);
                    CHECK_HR(hr, "Failed to get property values for [%ws]", pv.pwszVal);
                }
                else
                {
                    hr = m_pDevice->GetAllPropertyValues(pContext->Scope,pv.pwszVal, pValues);
                    CHECK_HR(hr, "Failed to get property values for [%ws]", pv.pwszVal);
                }

                // Add the ObjectID to the returned results
                if (hr == S_OK)
                {
                    hr = pValues->SetStringValue(WPD_OBJECT_ID, pv.pwszVal);
                    CHECK_HR(hr, "Failed to set WPD_OBJECT_ID for %ws", pv.pwszVal);
                }
            }

            if (hr == S_OK)
            {
                hr = pCollection->Add(pValues);
                CHECK_HR(hr, "Failed to add IPortableDeviceValues to IPortableDeviceValuesCollection");
            }

            PropVariantClear(&pv);
            pContext->NextObject++;
        }
    }

    if (hr == S_OK)
    {
        hr = pResults->SetIUnknownValue(WPD_PROPERTY_OBJECT_PROPERTIES_BULK_VALUES, pCollection);
        CHECK_HR(hr, "Failed to set WPD_PROPERTY_OBJECT_PROPERTIES_BULK_VALUES");
    }

    // Free the memory.  CoTaskMemFree ignores NULLs so no need to check.
    CoTaskMemFree(pwszContext);
    SAFE_RELEASE(pContext);

    return hr;
}
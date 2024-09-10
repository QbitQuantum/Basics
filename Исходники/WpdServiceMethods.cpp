HRESULT WpdServiceMethods::DispatchMethod(
    _In_         LPCWSTR                 pwszContext,
    _In_         IPortableDeviceValues*  pStartParams,
    _COM_Outptr_ IPortableDeviceValues** ppResults)
{
    HRESULT hr       = S_OK;
    HRESULT hrStatus = S_OK;
    GUID    Method   = GUID_NULL;
    CComPtr<IPortableDeviceValues> pMethodParams;
    CComPtr<IPortableDeviceValues> pMethodResults;

    *ppResults = NULL;

    // Get the method GUID
    hr = pStartParams->GetGuidValue(WPD_PROPERTY_SERVICE_METHOD, &Method);
    CHECK_HR(hr, "Failed to get WPD_PROPERTY_SERVICE_METHOD");

    // Get the method parameters.  These can be optional if the methods don't require parameters
    if (SUCCEEDED(hr))
    {
        HRESULT hrTemp = pStartParams->GetIPortableDeviceValuesValue(WPD_PROPERTY_SERVICE_METHOD_PARAMETER_VALUES, &pMethodParams);
        CHECK_HR(hrTemp, "Failed to get WPD_PROPERTY_SERVICE_METHOD_PARAMETER_VALUES (ok if method does not require parameters)");
    }

    // Prepare the results collection
    if (SUCCEEDED(hr))
    {
        hr = CoCreateInstance(CLSID_PortableDeviceValues,
                              NULL,
                              CLSCTX_INPROC_SERVER,
                              IID_IPortableDeviceValues,
                              (VOID**)&pMethodResults);
        CHECK_HR(hr, "Failed to CoCreate CLSID_PortableDeviceValues");
    }

    if (SUCCEEDED(hr))
    {
        // Invoke the method
        if (IsEqualGUID(METHOD_FullEnumSyncSvc_BeginSync, Method))
        {
            hrStatus = m_pContactsService->OnBeginSync(pMethodParams, *ppResults);
            CHECK_HR(hrStatus, "BeginSync method failed");
        }
        else if (IsEqualGUID(METHOD_FullEnumSyncSvc_EndSync, Method))
        {
            hrStatus = m_pContactsService->OnEndSync(pMethodParams, *ppResults);
            CHECK_HR(hrStatus, "EndSync method failed");
        }
        else if (IsEqualGUID(MyCustomMethod, Method))
        {
            CComPtr<IPortableDeviceValues> pCustomEventParams;

            hr = CoCreateInstance(CLSID_PortableDeviceValues,
                                  NULL,
                                  CLSCTX_INPROC_SERVER,
                                  IID_IPortableDeviceValues,
                                  (VOID**)&pCustomEventParams);
            CHECK_HR(hr, "Failed to CoCreate CLSID_PortableDeviceValues");

            if (SUCCEEDED(hr))
            {
                hrStatus = m_pContactsService->OnMyCustomMethod(pMethodParams, pMethodResults, pCustomEventParams);
                CHECK_HR(hrStatus, "MyCustomMethod method failed");
            }

            if (SUCCEEDED(hr))
            {
                // In addition to a method complete event, we can also send a custom event,
                // for example, to indicate progress of the method
                hr = PostWpdEvent(pStartParams, pCustomEventParams);
                CHECK_HR(hr, "Failed to post custom event");
            }
        }
        else
        {
            hrStatus = HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED);
            CHECK_HR(hr, "Unknown method %ws received",CComBSTR(Method));
        }
    }

    // We always want to post a method completion event
    // Even if the method has failed
    {
        CComPtr<IPortableDeviceValues> pEventParams;
        hr = CoCreateInstance(CLSID_PortableDeviceValues,
                              NULL,
                              CLSCTX_INPROC_SERVER,
                              IID_IPortableDeviceValues,
                              (VOID**)&pEventParams);
        CHECK_HR(hr, "Failed to CoCreate CLSID_PortableDeviceValues");

        if (SUCCEEDED(hr))
        {
            hr = pEventParams->SetGuidValue(WPD_EVENT_PARAMETER_EVENT_ID, WPD_EVENT_SERVICE_METHOD_COMPLETE);
            CHECK_HR(hr, "Failed to set the event id to WPD_EVENT_SERVICE_METHOD_COMPLETE");
        }

        if (SUCCEEDED(hr))
        {
            hr = pEventParams->SetStringValue(WPD_EVENT_PARAMETER_SERVICE_METHOD_CONTEXT, pwszContext);
            CHECK_HR(hr, "Failed to set the method context for WPD_EVENT_SERVICE_METHOD_COMPLETE");
        }

        if (SUCCEEDED(hr))
        {
            hr = PostWpdEvent(pStartParams, pEventParams);
            CHECK_HR(hr, "Failed to post WPD_EVENT_SERVICE_METHOD_COMPLETE");
        }
    }

    if (SUCCEEDED(hr))
    {
        hr = hrStatus;
    }

    if (SUCCEEDED(hr))
    {
        *ppResults = pMethodResults.Detach();
    }

    return hr;
}
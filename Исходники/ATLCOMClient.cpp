int _tmain(int argc, _TCHAR* argv[])
{
    HRESULT hr;

    // Initializes the COM library on the current thread and identifies the
    // concurrency model as single-thread apartment (STA).
    ::CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);


    /////////////////////////////////////////////////////////////////////////
    // Create the ATLDllCOMServer.SimpleObject COM object using the
    // #import directive and smart pointers.
    //

    CComQIPtr<ISimpleObject> spSimpleObj;
    hr = spSimpleObj.CoCreateInstance(OLESTR(
                                          "ATLDllCOMServer.SimpleObject"));
    if (FAILED(hr))
    {
        _tprintf(_T(
                     "ISimpleObjectPtr.CoCreateInstance failed w/err 0x%08lx\n"
                 ), hr);
        return hr;
    }


    /////////////////////////////////////////////////////////////////////////
    // Use sink object 1 (CATLSimpleSinkObject1) to set up the sink for the
    // events of the source COM object.
    //

    _putts(_T("Create sink object 1"));

    // Construct the sink object CATLSimpleSinkObject1 defined in
    // ATLSimpleSinkObject.h
    CATLSimpleSinkObject1* pSinkObj1 = new CATLSimpleSinkObject1();

    // Make sure the COM object corresponding to pUnk implements
    // IProvideClassInfo2 or IPersist*. Call this method to extract info
    // about source type library if you specified only 2 parameters to
    // IDispEventImpl.
    hr = AtlGetObjectSourceInterface(spSimpleObj, &pSinkObj1->m_libid,
                                     &pSinkObj1->m_iid, &pSinkObj1->m_wMajorVerNum,
                                     &pSinkObj1->m_wMinorVerNum);
    _ASSERTE(SUCCEEDED(hr));

    // Connect the sink and source, spSimpleObj is the source COM object
    hr = pSinkObj1->DispEventAdvise(spSimpleObj, &pSinkObj1->m_iid);
    _ASSERTE(SUCCEEDED(hr));


    // Invoke the source COM object
    {
        // Set FloatProperty which fires the event FloatPropertyChanging
        _tprintf(_T("Set FloatProperty = %.2f\n"), 1.1f);
        spSimpleObj->PutFloatProperty(1.1f);

        float fProp = spSimpleObj->GetFloatProperty();
        _tprintf(_T("Get FloatProperty = %.2f\n"), fProp);
    }


    // Disconnect from the source COM object if connected
    if (pSinkObj1->m_dwEventCookie != 0xFEFEFEFE)
        pSinkObj1->DispEventUnadvise(spSimpleObj, &pSinkObj1->m_iid);

    // Destroy the sink object
    delete pSinkObj1;


    /////////////////////////////////////////////////////////////////////////
    // Use sink object 2 (CATLSimpleSinkObject2) to set up the sink for the
    // events of the source COM object.
    //

    _putts(_T("Create sink object 2"));

    // Construct the sink object CATLSimpleSinkObject2 defined in
    // ATLSimpleSinkObject.h
    CATLSimpleSinkObject2* pSinkObj2 = new CATLSimpleSinkObject2();

    // Connect the sink and source, m_spSrcObj is the source COM object
    hr = pSinkObj2->DispEventAdvise(spSimpleObj);
    _ASSERTE(SUCCEEDED(hr));


    // Invoke the source COM object
    {
        // Set FloatProperty which fires the event FloatPropertyChanging
        _tprintf(_T("Set FloatProperty = %.2f\n"), 1.2f);
        spSimpleObj->PutFloatProperty(1.2f);

        float fProp = spSimpleObj->GetFloatProperty();
        _tprintf(_T("Get FloatProperty = %.2f\n"), fProp);
    }


    // Disconnect from source if connected
    if (pSinkObj2->m_dwEventCookie != 0xFEFEFEFE)
        pSinkObj2->DispEventUnadvise(spSimpleObj);

    // Destroy the sink object
    delete pSinkObj2;


    /////////////////////////////////////////////////////////////////////////
    // Use sink object 3 (CATLSimpleSinkObject3) to set up the sink for the
    // events of the source COM object.
    //

    _putts(_T("Create sink object 3"));

    // Construct the sink object CATLSimpleSinkObject3 defined in
    // ATLSimpleSinkObject.h
    CATLSimpleSinkObject3* pSinkObj3 = new CATLSimpleSinkObject3();

    // Connect the sink and source, m_spSrcObj is the source COM object
    hr = pSinkObj3->DispEventAdvise(spSimpleObj);
    _ASSERTE(SUCCEEDED(hr));


    // Invoke the source COM object
    {
        // Set FloatProperty which fires the event FloatPropertyChanging
        _tprintf(_T("Set FloatProperty = %.2f\n"), 1.3f);
        spSimpleObj->PutFloatProperty(1.3f);

        float fProp = spSimpleObj->GetFloatProperty();
        _tprintf(_T("Get FloatProperty = %.2f\n"), fProp);
    }


    // Disconnect from source if connected
    if (pSinkObj3->m_dwEventCookie != 0xFEFEFEFE)
        pSinkObj3->DispEventUnadvise(spSimpleObj);

    // Destroy the sink object
    delete pSinkObj3;


    /////////////////////////////////////////////////////////////////////////
    // Release the COM object.
    //

    // Make sure that the source COM object is release before CoUninitialize
    spSimpleObj.Release();

    // Uninitialize COM for this thread
    ::CoUninitialize();

    return 0;
}
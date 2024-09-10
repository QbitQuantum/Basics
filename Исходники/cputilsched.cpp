HRESULT CpiFindCollectionObject(
    ICatalogCollection* piColl,
    LPCWSTR pwzID,
    LPCWSTR pwzName,
    ICatalogObject** ppiObj
    )
{
    HRESULT hr = S_OK;

    IDispatch* piDisp = NULL;
    ICatalogObject* piObj = NULL;

    VARIANT vtVal;
    ::VariantInit(&vtVal);

    long lCnt;
    hr = piColl->get_Count(&lCnt);
    ExitOnFailure(hr, "Failed to get to number of items in collection");

    for (long i = 0; i < lCnt; i++)
    {
        // get ICatalogObject interface
        hr = piColl->get_Item(i, &piDisp);
        ExitOnFailure(hr, "Failed to get object from collection");

        hr = piDisp->QueryInterface(IID_ICatalogObject, (void**)&piObj);
        ExitOnFailure(hr, "Failed to get IID_ICatalogObject interface");

        // compare id
        if (pwzID && *pwzID)
        {
            hr = piObj->get_Key(&vtVal);
            ExitOnFailure(hr, "Failed to get key");

            hr = ::VariantChangeType(&vtVal, &vtVal, 0, VT_BSTR);
            ExitOnFailure(hr, "Failed to change variant type");

            if (0 == lstrcmpiW(vtVal.bstrVal, pwzID))
            {
                if (ppiObj)
                {
                    *ppiObj = piObj;
                    piObj = NULL;
                }
                ExitFunction1(hr = S_OK);
            }

            ::VariantClear(&vtVal);
        }

        // compare name
        if (pwzName && *pwzName)
        {
            hr = piObj->get_Name(&vtVal);
            ExitOnFailure(hr, "Failed to get name");

            hr = ::VariantChangeType(&vtVal, &vtVal, 0, VT_BSTR);
            ExitOnFailure(hr, "Failed to change variant type");

            if (0 == lstrcmpW(vtVal.bstrVal, pwzName))
            {
                if (ppiObj)
                {
                    *ppiObj = piObj;
                    piObj = NULL;
                }
                ExitFunction1(hr = S_OK);
            }

            ::VariantClear(&vtVal);
        }

        // release interface pointers
        ReleaseNullObject(piDisp);
        ReleaseNullObject(piObj);
    }

    hr = S_FALSE;

LExit:
    // clean up
    ReleaseObject(piDisp);
    ReleaseObject(piObj);

    ::VariantClear(&vtVal);

    return hr;
}
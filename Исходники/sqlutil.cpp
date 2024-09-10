/********************************************************************
 SqlGetErrorInfo - gets error information from the last SQL function call

 NOTE: pbstrErrorSource and pbstrErrorDescription are optional
********************************************************************/
extern "C" HRESULT DAPI SqlGetErrorInfo(
    __in IUnknown* pObjectWithError,
    __in REFIID IID_InterfaceWithError,
    __in DWORD dwLocaleId,
    __out_opt BSTR* pbstrErrorSource,
    __out_opt BSTR* pbstrErrorDescription
    )
{
    HRESULT hr = S_OK;
    Assert(pObjectWithError);

    // interfaces needed to extract error information out
    ISupportErrorInfo* pISupportErrorInfo = NULL;
    IErrorInfo* pIErrorInfoAll = NULL;
    IErrorRecords* pIErrorRecords = NULL;
    IErrorInfo* pIErrorInfoRecord = NULL;

    // only ask for error information if the interface supports it.
    hr = pObjectWithError->QueryInterface(IID_ISupportErrorInfo,(void**)&pISupportErrorInfo);
    ExitOnFailure(hr, "No error information was found for object.");

    hr = pISupportErrorInfo->InterfaceSupportsErrorInfo(IID_InterfaceWithError);
    ExitOnFailure(hr, "InterfaceWithError is not supported for object with error");

    // ignore the return of GetErrorInfo it can succeed and return a NULL pointer in pIErrorInfoAll anyway
    hr = ::GetErrorInfo(0, &pIErrorInfoAll);
    ExitOnFailure(hr, "failed to get error info");

    if (S_OK == hr && pIErrorInfoAll)
    {
        // see if it's a valid OLE DB IErrorInfo interface that exposes a list of records
        hr = pIErrorInfoAll->QueryInterface(IID_IErrorRecords, (void**)&pIErrorRecords);
        if (SUCCEEDED(hr))
        {
            ULONG cErrors = 0;
            pIErrorRecords->GetRecordCount(&cErrors);

            // get the error information for each record
            for (ULONG i = 0; i < cErrors; ++i)
            {
                hr = pIErrorRecords->GetErrorInfo(i, dwLocaleId, &pIErrorInfoRecord);
                if (SUCCEEDED(hr))
                {
                    if (pbstrErrorSource)
                    {
                        pIErrorInfoRecord->GetSource(pbstrErrorSource);
                    }
                    if (pbstrErrorDescription)
                    {
                        pIErrorInfoRecord->GetDescription(pbstrErrorDescription);
                    }

                    ReleaseNullObject(pIErrorInfoRecord);

                    break; // TODO: return more than one error in the future!
                }
            }

            ReleaseNullObject(pIErrorRecords);
        }
        else // we have a simple error record
        {
            if (pbstrErrorSource)
            {
                pIErrorInfoAll->GetSource(pbstrErrorSource);
            }
            if (pbstrErrorDescription)
            {
                pIErrorInfoAll->GetDescription(pbstrErrorDescription);
            }
        }
    }
    else
    {
        hr = E_NOMOREITEMS;
    }

LExit:
    ReleaseObject(pIErrorInfoRecord);
    ReleaseObject(pIErrorRecords);
    ReleaseObject(pIErrorInfoAll);
    ReleaseObject(pISupportErrorInfo);

    return hr;
}
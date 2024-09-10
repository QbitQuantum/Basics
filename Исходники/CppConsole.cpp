int main()
{
    CoInitializeEx(0, COINIT_MULTITHREADED);

    HRESULT hr = S_OK;
    //GUID guid;
    //hr = CLSIDFromString(L"MyNamespace.MyClass", &guid);
    //hr = CLSIDFromString(L"{7884998B-0504-4CBE-9FF9-6BBAA9776188}", &guid);
    //hr = CoCreateInstance(guid, NULL, CLSCTX_ALL, IID_IUnknown, reinterpret_cast<void**>(&p));

    NetCom::IMyClassPtr ptr;
    hr = ptr.CreateInstance(__uuidof(NetCom::Class1));
    long l;
    hr = ptr->GetData(&l);

	SAFEARRAY *ppData = NULL;
    hr = ptr->GetStructs(&ppData);
    if (SUCCEEDED(hr) && ppData)
    {
        #pragma region Validate received datatype 

        VARTYPE vt;
        hr = SafeArrayGetVartype(ppData, &vt);
        if (SUCCEEDED(hr) && (vt != VT_RECORD))
        {
            //Not a sturcture
            hr = E_POINTER;
        }

        if (SUCCEEDED(hr))
        {
            IRecordInfoPtr spIRecordInfo = NULL;
            hr = SafeArrayGetRecordInfo(ppData, &spIRecordInfo);
            if (SUCCEEDED(hr) && spIRecordInfo)
            {
                GUID guid;
                hr = spIRecordInfo->GetGuid(&guid);
                if (guid != __uuidof(NetCom::TICKSTRUCT))
                {
                    //Invalid record type
                    hr = E_POINTER;
                }
            }
        }
        #pragma endregion

        NetCom::TICKSTRUCT *pVals = NULL;
        hr = SafeArrayAccessData(ppData, (void**)&pVals);
        if (SUCCEEDED(hr))
        {
            long lowerBound, upperBound;  // get array bounds
            SafeArrayGetLBound(ppData, 1, &lowerBound);
            SafeArrayGetUBound(ppData, 1, &upperBound);

            long count = upperBound - lowerBound + 1;
            for (int i = 0; i < count; ++i)  // iterate through returned values
            {
                printf("[%d] Date: %f Price: %f Volume: %d\n", i, pVals->Date, pVals->Price, pVals->Volume);
                pVals++;
            }
            hr = SafeArrayUnaccessData(ppData);
        }
        hr = SafeArrayDestroy(ppData);
    }

	//Control safearray lifetime by _variant_t wrapper
	_variant_t vt;
	if (SUCCEEDED(ptr->GetStructs(&vt.parray)))
	{
		vt.vt = VT_ARRAY | VT_RECORD;
		SAFEARRAY* ppData2 = vt.parray;
		//ppData2 can be used in same way as ppData above with exception:
		//1. Do not call SafeArrayDestroy. array will be destroyed by VariantClear function
		//2. Make sure ppData2 is not locked (SafeArrayAccessData) before vt.Clear or ~vt will be called.
		//		In this case VariantClear will not able to clean locked data
	}

    return 0;
}
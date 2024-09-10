STDMETHODIMP CMapiWrapper::GetProfilelist(VARIANT *Profiles,BSTR *statusmessage)
{
    // TODO: Add your implementation code here
    dlog.trace(L" Begin Mapiwrapper GetProfilelist");
    HRESULT hr = S_OK;
	CComBSTR status = L"";

    hr = MAPIInitialize(NULL);
	if( hr != S_OK)
	{
            
		
		LPCSTR temp = format_error(hr).c_str();
		
		status.AppendBSTR(L" MapiInitialize error ");
		status.AppendBSTR(A2BSTR(temp));
		
                dlog.err(status);
		*statusmessage =  status;

                return hr;
	}

    Zimbra::Mapi::Memory::SetMemAllocRoutines(NULL, MAPIAllocateBuffer, MAPIAllocateMore,
        MAPIFreeBuffer);

    vector<string> vProfileList;
     hr = exchadmin->GetAllProfiles(vProfileList);

	 if( hr != S_OK)
	{
		
		LPCSTR temp = format_error(hr).c_str();
		
		status.AppendBSTR(L" GetAllProfiles error ");
		status.AppendBSTR(A2BSTR(temp));
		dlog.err(status);
		*statusmessage =  status;

     return hr;
	}
         if(vProfileList.size() == 0)
         {
            dlog.err(L"No profiles returned for GetAllProfiles");
			status = L"No profiles";
            *statusmessage =  status;
			status.Detach();
            return S_OK;

         }
    vector<CComBSTR> tempvectors;

    std::vector<string>::iterator its;

    for (its = (vProfileList.begin()); its != vProfileList.end(); its++)
    {
        string str = (*its).c_str();
        CComBSTR temp = SysAllocString(str_to_wstr(str).c_str());

        tempvectors.push_back(temp);
    }
    VariantInit(Profiles);
    Profiles->vt = VT_ARRAY | VT_BSTR;

    SAFEARRAY *psa;
    SAFEARRAYBOUND bounds = { (ULONG)vProfileList.size(), 0 };

    psa = SafeArrayCreate(VT_BSTR, 1, &bounds);

    BSTR *bstrArray;

    SafeArrayAccessData(psa, (void **)&bstrArray);

    std::vector<CComBSTR>::iterator it;
    int i = 0;

    for (it = (tempvectors.begin()); it != tempvectors.end(); it++, i++)
        bstrArray[i] = SysAllocString((*it).m_str);
    SafeArrayUnaccessData(psa);
    Profiles->parray = psa;

	*statusmessage =  status;
        status.Detach();

	MAPIUninitialize();

        dlog.trace(L" End Mapiwrapper GetProfilelist");
    return hr;
}
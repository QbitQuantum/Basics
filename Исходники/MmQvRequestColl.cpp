HRESULT CMmQvRequestColl::RequestLastQuotes(IBatchPriceProviderPtr spProvider)
{
	typedef CComRecPtr<QuoteUpdateParams, &LIBID_PRICEPROVIDERSLib >  _QuoteUpdateParams;
	HRESULT hr = S_OK;
	try
	{
		long lSize = static_cast<long>(m_coll.size());
		if(lSize)
		{
			_QuoteUpdateParams request;
			request.Init();
			SAFEARRAYBOUND sab = { lSize, 0};

			LPSAFEARRAY psa = ::SafeArrayCreateEx(VT_RECORD, 1, &sab, (PVOID)request.GetRecordInfo());
			if(psa)
			{
				QuoteUpdateParams* pvData = NULL;
				if(SUCCEEDED(hr = ::SafeArrayAccessData(psa, (void**)&pvData)))
				{
					memset(pvData, 0,  m_coll.size() * sizeof(QuoteUpdateParams));
					int i = 0;
					for(CollType::iterator itr = m_coll.begin(); itr!=m_coll.end(); ++itr, ++i)
					{

						IMmQvRequestAtomPtr spRequestAtom = itr->second;
						spRequestAtom->get_QuoteUpdateParam(request);
						request.CopyTo(&pvData[i]);

						if(request->Symbol)
						{
							SysFreeString(request->Symbol);
							request->Symbol = NULL;
						}
						if(request->Exchange)
						{
							SysFreeString(request->Exchange);
							request->Exchange = NULL;
						}
					}	
					::SafeArrayUnaccessData(psa);
					spProvider->RequestMultipleQuotes(&psa);
				}
				SafeArrayDestroy(psa);
			}
		}
	}catch(_com_error& err)
	{
		return Error((PTCHAR)EgLib::CComErrorWrapper::ErrorDescription(err), IID_IMmQvRequestColl, err.Error());
	}
	/*catch (...)
	{
	}*/
	return S_OK;
}
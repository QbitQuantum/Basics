LPSPropValue Workshare::Mail::Mapi::GetMessageTag(LPMESSAGE lpMessage, const std::tstring& sTag)
{
	LPSPropValue pPropVal = 0;

	IMAPIPropPtr spMapiProp;
	HRESULT hr = lpMessage->QueryInterface(IID_IMAPIProp, (void**) &spMapiProp);
	if(SUCCEEDED(hr))
	{
		LPMAPINAMEID pTagName = 0;
		hr = MAPIAllocateBuffer(sizeof(MAPINAMEID), (LPVOID*)&pTagName);
		if(SUCCEEDED(hr))
		{
			pTagName[0].lpguid = (LPGUID)&PS_PUBLIC_STRINGS;
			pTagName[0].ulKind = MNID_STRING;
			_bstr_t bsTag(sTag.c_str());
			pTagName[0].Kind.lpwstrName = bsTag;

			LPSPropTagArray pPropTag = 0;
			hr = spMapiProp->GetIDsFromNames(1, &pTagName, 0, &pPropTag);
			if (!FAILED(hr))
			{
				if(1 == pPropTag->cValues && PT_ERROR != PROP_TYPE(pPropTag->aulPropTag[0]))
				{
					ULONG ulCount = 0;
					spMapiProp->GetProps(pPropTag, 0, &ulCount, &pPropVal);
				}
				MAPIFreeBuffer(pPropTag);
			}
			MAPIFreeBuffer(pTagName);
		}
	}
	return pPropVal;
}
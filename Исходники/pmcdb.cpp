STDMETHODIMP CPmcDB::readArchiveValue(
	BSTR tagName, 
	VARIANT date, 
	VARIANT * tagValue
	)
{
	SYSTEMTIME st;
	FILETIME ft;
	TAG_NAME tn;
	hislog_item_t value;
	VARIANT dd;
	HRESULT hr;
	
	if(date.vt != VT_DATE){
		// BUGBUG: not tested
		hr = VariantChangeType(&dd, &date, 0, VT_DATE);
		if(FAILED(hr)){
			return hr;
		}
		date = dd;
	}
	VariantTimeToSystemTime(date.date, &st);
	SystemTimeToFileTime(&st, &ft);
	tagname_by_textW(&tn, tagName);
	queryHisData(&tn, &ft, 1, 1);
	getHisData(&value);
	pmc_value_to_variant(&value, tagValue);
	return S_OK;
}
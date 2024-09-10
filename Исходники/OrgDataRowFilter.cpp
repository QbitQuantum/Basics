STDMETHODIMP COrgDataRowFilter::raw_Check( GrymCore::IDataRow *pRecord, VARIANT_BOOL *pVal )
{
	try {
		if ( !pRecord )
			return E_INVALIDARG;

		if ( !pVal )
			return E_POINTER;

		*pVal = VARIANT_FALSE;

		_bstr_t orgName;
		if ( pRecord->Type == orgFilType_ ) {
			// если передан филиал, то нужно у него запросить его организацию, чтобы получить ее название.
			if ( GrymCore::IDataRowPtr org = pRecord->GetValue(parentKey_) ) {
				// получаем название организации
				orgName = org->GetValue(nameKey_);
			}
		} else if ( pRecord->Type == orgType_ ) {
			// получаем название организации
			orgName = pRecord->GetValue(nameKey_);
		} else {
			return S_OK;
		}

		wchar_t *orgNameBuf = _wcsdup(orgName);
		CharLowerW(orgNameBuf);
		if ( Wildcard::wildcardfit(filter_, orgNameBuf) )
		{
			*pVal = VARIANT_TRUE;
		}
		free(orgNameBuf);

		return S_OK;
	} catch (...) {
	}
	
	return E_FAIL;
}
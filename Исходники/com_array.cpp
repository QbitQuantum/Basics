	bool com_array_reader::convert_jsarray(IDispatch * pdisp)
	{
		if (!pdisp) return false;

		DISPPARAMS params = {0};
		_variant_t ret;

		DISPID id_length;
		LPOLESTR slength = L"length";

		if (FAILED(pdisp->GetIDsOfNames(IID_NULL, &slength, 1, LOCALE_USER_DEFAULT, &id_length)))
			return false;

		if (FAILED(pdisp->Invoke(id_length, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET,
			&params, &ret, NULL, NULL)))
			return false;

		if (FAILED(VariantChangeType(&ret, &ret, 0, VT_I4)))
			return false;

		m_lbound = 0;
		m_ubound = ret.lVal - 1;

		SAFEARRAY * psa = SafeArrayCreateVector(VT_VARIANT, 0, get_count());

		if (!psa) goto cleanup_and_return;

		for (long i = m_lbound; i <= m_ubound; ++i)
		{
			DISPID dispid = 0;
			DISPPARAMS params = {0};
			wchar_t buf[33];
			LPOLESTR name = buf;
			_variant_t element;
			HRESULT hr = S_OK;

			_itow_s(i, buf, 10);

			if (SUCCEEDED(hr)) hr = pdisp->GetIDsOfNames(IID_NULL, &name, 1, LOCALE_USER_DEFAULT, &dispid);
			if (SUCCEEDED(hr)) hr = pdisp->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, 
				&params, &element, NULL, NULL);

			if (FAILED(hr)) goto cleanup_and_return;
			if (FAILED(SafeArrayPutElement(psa, &i, &element))) goto cleanup_and_return;
		}

		m_psa = psa;
		return true;

cleanup_and_return:
		reset();
		SafeArrayDestroy(psa); 
		return false;
	}
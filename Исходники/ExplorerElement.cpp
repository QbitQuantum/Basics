static void getStyleAttribute (IDispatch *object, std::string &style)
{
	VARIANT v;
	VariantInit(&v);
	HRESULT hr = getDispatchProperty(object, "style", v);
	if ( FAILED (hr))
		return;

	if (! v.vt == VT_DISPATCH)
	{
		VariantClear(&v);
		return;
	}

	VARIANT v2;
	VariantInit (&v2);
	hr = getDispatchProperty(v.pdispVal, "cssText", v2);
	if ( !FAILED(hr))
	{
		VARIANT result2;
		VariantInit(&result2);
		if ( S_OK == VariantChangeType (&result2, &v2, 0, VT_BSTR))
		{
			Utils::bstr2str (style, result2.bstrVal);
			VariantClear (&result2);
		} else {
		}
		VariantClear (&v2);
	}


	v.pdispVal->Release();
	VariantClear(&v);
}
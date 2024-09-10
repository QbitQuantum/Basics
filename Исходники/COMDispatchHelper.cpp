HRESULT CCOMDispatchHelper::GetPropertyItemValues(const IDispatchPtr& pICollection, int iIndex, 
												  _bstr_t& bstrName, _bstr_t& bstrValue)
{
	HRESULT hr = E_FAIL;
	variant_t result, vIndex;
	vIndex.lVal = iIndex;
	vIndex.vt = VT_I4;
	hr = AutoWrap(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &result, pICollection, L"Item", 1, vIndex);
	RETURN_FAILED(hr);

	IDispatchPtr spPropItem = result.pdispVal;

	variant_t vPropItem;

	hr = AutoWrap(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &vPropItem, spPropItem, L"Name", 0);
	RETURN_FAILED(hr);

	bstrName.Assign(vPropItem.bstrVal);

	hr = AutoWrap(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &vPropItem, spPropItem, L"Value", 0);
	RETURN_FAILED(hr);

	//ComConvertUtils aComConvertUtils;

	//TODO look at a better way of casting a variant_t to a PROPVARIANT
	bstrValue = (LPCTSTR)PropVariantToString(*(PROPVARIANT*)(VARIANT*)&vPropItem);

	return hr;
}
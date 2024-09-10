/*---------------------------------------------------------------------------------------------*/
static HRESULT _get_value_length(unsigned int value_type, const void* value, size_t* length)
{
	HRESULT hr;
	size_t l;

	switch (value_type)
	{
	case AXV_INT8: case AXV_UINT8: *length = 1; return S_OK;
	case AXV_INT16: case AXV_UINT16: *length = 2; return S_OK;
	case AXV_INT32: case AXV_UINT32: *length = 4; return S_OK;
	case AXV_INT64: case AXV_UINT64: *length = 8; return S_OK;
	case AXV_FLOAT32: *length = 4; return S_OK;
	case AXV_FLOAT64: *length = 8; return S_OK;
	case AXV_STR_ACP: case AXV_STR_UTF8:
	{
		hr = StringCbLengthA((const char*)value, AXTRACE_MAX_VALUE_LENGTH - 1, &l);
		if (FAILED(hr)) return hr;
		*length = l + 1;
		return S_OK;
	}
	case AXV_STR_UTF16:
	{
		hr = StringCbLengthW((const wchar_t*)value, AXTRACE_MAX_VALUE_LENGTH - 1, &l);
		if (FAILED(hr)) return hr;
		*length = l + 2;
		return S_OK;
	}
	default: break;
	}
	return E_FAIL;
}
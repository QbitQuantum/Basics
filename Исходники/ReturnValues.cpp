STDMETHODIMP CReturnValues::mNullRefException()
{
	AtlSetErrorInfo(CLSID_ReturnValues, OLESTR("Custom error message for E_POINTER"), 0, NULL, IID_IReturnValues, E_POINTER, NULL);
	return E_POINTER;
}
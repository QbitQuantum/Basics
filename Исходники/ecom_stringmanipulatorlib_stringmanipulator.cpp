ecom_StringManipulatorLib::StringManipulator::StringManipulator()
{
	HRESULT hr;
	hr = CoInitializeEx (NULL, COINIT_APARTMENTTHREADED);
	rt.ccom_check_hresult (hr);
	p_unknown = NULL;
	MULTI_QI a_qi = {&IID_IUnknown, NULL, 0};

	hr = CoCreateInstanceEx (CLSID_StringManipulator_, NULL, CLSCTX_INPROC_SERVER, NULL, 1, &a_qi);
	rt.ccom_check_hresult (hr);
	rt.ccom_check_hresult (a_qi.hr);
	p_unknown = a_qi.pItf;

	p_IString = 0;

};
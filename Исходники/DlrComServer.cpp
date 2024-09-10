STDMETHODIMP CDlrComServer::TestErrorInfo(void)
{
	AtlSetErrorInfo(CLSID_DlrComServer, OLESTR("Test error message"), 0, NULL, IID_IDlrComServer, E_FAIL, NULL);

	return E_FAIL;
}
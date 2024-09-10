STDMETHODIMP CComBus::Stop(void)
{
	// TODO: Add your implementation code here
	ExitThread();
	ClosePort();
	return S_OK;
}
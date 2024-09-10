void PlayMedia(const char *pszFileName) throw(_com_error)
{
	HRESULT hr;
	IGraphBuilderPtr pGraphBuilder;
	IMediaControlPtr pMediaControl;
	IMediaEventPtr pMediaEvent;
	WCHAR wszFileName[MAX_PATH];
	LONG lEventCode;

	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	pGraphBuilder.CreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC);

	wsprintfW(wszFileName, L"%S", pszFileName);
	hr = pGraphBuilder->RenderFile(wszFileName, NULL);
	if (!SUCCEEDED(hr))
		_com_raise_error(hr);

	pMediaControl = pGraphBuilder;
	pMediaEvent = pGraphBuilder;

	hr = pMediaControl->Run();
	if (!SUCCEEDED(hr))
		_com_raise_error(hr);

	hr = pMediaEvent->WaitForCompletion(INFINITE, &lEventCode);
	if (!SUCCEEDED(hr))
		_com_raise_error(hr);
}
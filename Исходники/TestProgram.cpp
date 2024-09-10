unsigned int __stdcall CreateD3DDevice(void *arg)
{
	HRESULT hr = E_FAIL;

	IDirect3DDevice9Ex **ppD3DDevice = static_cast<IDirect3DDevice9Ex**>(arg);

	CComPtr<IDisplayServer> pDispSvr;		
	CComPtr<IDisplayRenderEngine> pRenderEngine;

	CoInitialize(NULL);

	hr = pDispSvr.CoCreateInstance(CLSID_DisplayServer);
	
	hr = pDispSvr->Initialize(0x1da0, CreateAWindow(), NULL);				
	
	hr = pDispSvr->GetRenderEngine(&pRenderEngine);
	
	hr = pRenderEngine->Get3DDevice((IUnknown**)ppD3DDevice);

	CoUninitialize();
	
	return 0;
}
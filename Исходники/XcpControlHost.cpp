/*!
\brief Creates a XCP control container
@param[in]	hWnd	Already created control container.  Static control.
\retval HANDLE	XcpControlHost
*/
HRESULT LoAgXcpCreateControl( HWND hWnd ) 
{
	AtlAxWinInit();

	HRESULT hr;
	static const GUID IID_IXcpControl = { 0x1FB839CC, 0x116C, 0x4C9B, { 0xAE, 0x8E, 0x3D, 0xBB, 0x64, 0x96, 0xE3, 0x26 }};
	static const GUID CLSID_XcpControl = { 0xDFEAF541, 0xF3E1, 0x4c24, { 0xAC, 0xAC, 0x99, 0xC3, 0x07, 0x15, 0x08, 0x4A }};
	static const GUID IID_IXcpControl2 = { 0x1c3294f9, 0x891f, 0x49b1, { 0xBB, 0xAE, 0x49, 0x2a, 0x68, 0xBA, 0x10, 0xcc }};

	//	static const GUID CLSID_XcpControl2 = 
	//		{ 0xDFEAF541, 0xF3E1, 0x4c24, { 0xAC, 0xAC, 0x99, 0xC3, 0x07, 0x15, 0x08, 0x4A }};

	//static const GUID IID_IXcpControlHost2 = 
	//	{ 0xfb3ed7c4, 0x5797, 0x4b44, { 0x86, 0x95, 0x0c, 0x51, 0x2e, 0xa2, 0x7D, 0x8f }};

	hr = CoCreateInstance(CLSID_XcpControl, NULL, CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&CXcpControlHost::pUnKnown);

	if (SUCCEEDED(hr)) 
	{
		//CComPtr<IUnknown> spUnkContainer;
		IUnknown	*spUnkContainer = NULL;
		//CoCreateInstance( __uuidof(IUnknown), &CXcpControlHost::pUnKnown, CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&spUnkContainer );
		hr = CXcpControlHost::_CreatorClass::CreateInstance(NULL, IID_IUnknown, (void**)&spUnkContainer);
		
		if (SUCCEEDED(hr)) 
		{
			//CComPtr<IAxWinHostWindow> pAxWindow;
			IAxWinHostWindow	*pAxWindow = NULL;

			spUnkContainer->QueryInterface(IID_IAxWinHostWindow, (void**)&pAxWindow);
			if( NULL != pAxWindow )
			{
				CXcpControlHost::pUnKnown->QueryInterface(IID_IXcpControl2, (void**)&CXcpControlHost::pControl);
				hr = pAxWindow->AttachControl(CXcpControlHost::pUnKnown, hWnd);            
			}
			CXcpControlHost::hControlWindow = hWnd;

			IOleInPlaceActiveObject *pObj;
			hr = CXcpControlHost::pControl->QueryInterface(IID_IOleInPlaceActiveObject, (void**)&pObj);
			spUnkContainer->Release();
		}
	}
	return hr;
}
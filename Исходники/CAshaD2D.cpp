HRESULT CAshaD2D::CreateFactory(void)
{
	HRESULT hr=S_OK;
	//Initialize com
	CoInitializeEx(NULL,COINIT_MULTITHREADED);
	//Create WIC factory
	hr=CoCreateInstance(CLSID_WICImagingFactory1,NULL,CLSCTX_INPROC_SERVER,IID_PPV_ARGS(&m_pWICImgFactory));
	//Create D2D factory
	if(SUCCEEDED(hr))
		hr=D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED,&m_pD2D1Facatory);
	//Create DWrite factory
	if(SUCCEEDED(hr))
		hr=DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,__uuidof(IDWriteFactory),reinterpret_cast<IUnknown**>(&m_pDWriteFactory));

	return hr;
}
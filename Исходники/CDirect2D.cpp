void CDirect2D::init(){

	std::cout << "Direct2D initialization: \n";
	assert(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory) == S_OK);
	std::cout << "d2d1 factory created \n";

	assert(m_hwnd);
	
	RECT rc;
	GetClientRect(m_hwnd, &rc);

	HRESULT hr = m_pDirect2dFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(m_hwnd, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)),
		&pRenderTarget);

	//pRenderTarget->CreateSolidColorBrush(
	//	D2D1::ColorF(D2D1::ColorF::Black),
	//	&m_pBlackBrush);

	//renderObj = new CRenderObject(L"test.png");

	//renderObjectsList = new std::vector<CRenderObject *>;
	//renderObjectsList.push_back(new CRenderObject(L"test.png"));
		
}
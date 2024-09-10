bool NND2DRenderer::Init()
{
	HRESULT hr;
	hr = D2D1CreateFactory( D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_ipD2DFactory );
	if ( hr != S_OK )
	{
		return false;
	}

	HWND hwnd = NNApplication::GetInstance()->GetHWND();
	RECT rt;
	GetClientRect( hwnd, &rt );
	D2D1_SIZE_U size = D2D1::SizeU( rt.right-rt.left, rt.bottom-rt.top );

	hr = m_ipD2DFactory->CreateHwndRenderTarget( D2D1::RenderTargetProperties(),
												 D2D1::HwndRenderTargetProperties( hwnd, size ),
												 &m_ipRenderTarget );

	if ( hr != S_OK )
	{
		return false;
	}

	return true;
}
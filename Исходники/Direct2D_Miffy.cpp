// Creates resources that are not bound to a particular device.
// Their lifetime effectively extends for the duration of the application.
HRESULT Direct2D_Miffy::CreateDeviceIndependentResources()
{
    HRESULT hr = S_OK;

    // Create a Direct2D factory.
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);
	
	if(SUCCEEDED(hr)) {
		hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(IDWriteFactory),
        reinterpret_cast<IUnknown**>(&m_pDWriteFactory)
        );
	}

	if(SUCCEEDED(hr)) {
		hr = m_pDirect2dFactory->CreatePathGeometry(&m_pPathGeometryUnion);
	}

	if(SUCCEEDED(hr)) {
		hr = m_pDirect2dFactory->CreatePathGeometry(&m_pPathGeometryUnion2);
	}

	// Create the ellipse geometries, which are device-independent
	const D2D1_ELLIPSE ellipse1 = D2D1::Ellipse(
			D2D1::Point2F(240.0f, 140.0f), 40.0f, 100.0f);
	const D2D1_ELLIPSE ellipse2 = D2D1::Ellipse(
			D2D1::Point2F(400.0f, 140.0f), 40.f, 100.0f);
	const D2D1_ELLIPSE ellipse3 = D2D1::Ellipse(
			D2D1::Point2F(320.0f, 300.0f), 150.f, 120.0f);
	const D2D1_ELLIPSE ellipse4 = D2D1::Ellipse(
			D2D1::Point2F(240.0f, 280.0f), 10.f, 10.0f);
	const D2D1_ELLIPSE ellipse5 = D2D1::Ellipse(
			D2D1::Point2F(400.0f, 280.0f), 10.f, 10.0f);

	hr = m_pDirect2dFactory->CreateEllipseGeometry(ellipse1, &m_pEllipseGeometry1);
	hr = m_pDirect2dFactory->CreateEllipseGeometry(ellipse2, &m_pEllipseGeometry2);
	hr = m_pDirect2dFactory->CreateEllipseGeometry(ellipse3, &m_pEllipseGeometry3);
	hr = m_pDirect2dFactory->CreateEllipseGeometry(ellipse4, &m_pEllipseGeometry4);	 
	hr = m_pDirect2dFactory->CreateEllipseGeometry(ellipse5, &m_pEllipseGeometry5);

    return hr;
}
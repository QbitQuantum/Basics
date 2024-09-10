//
// Program starts here
//
int main( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
	HRESULT hr = D2D1CreateFactory(
					 D2D1_FACTORY_TYPE_SINGLE_THREADED,
					 &g_pD2DFactory
				 );
	hr = DWriteCreateFactory(
			 DWRITE_FACTORY_TYPE_SHARED,
			 __uuidof( IDWriteFactory ),
			 reinterpret_cast<IUnknown**>( &g_pDWriteFactory )
		 );
	hr = CoInitialize( NULL );
	hr = CoCreateInstance(
			 CLSID_WICImagingFactory,
			 NULL,
			 CLSCTX_INPROC_SERVER,
			 IID_IWICImagingFactory,
			 reinterpret_cast<void**>( &g_pWICFactory )
		 );
	g_pHWND = CreateGameWindow();
	createDeviceResources();
	//
	// Create a GWEN Direct2D renderer
	//
	g_pRenderer = new gwen::Renderer::Direct2D( g_pRT, g_pDWriteFactory, g_pWICFactory );
	runSample();
	delete g_pRenderer;
	g_pRenderer = NULL;

	if ( g_pRT != NULL )
	{
		g_pRT->Release();
		g_pRT = NULL;
	}
}
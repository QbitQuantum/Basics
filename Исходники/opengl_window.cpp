	opengl_window::opengl_window(i_rendering_engine& aRenderingEngine, i_surface_manager& aSurfaceManager, i_native_window_event_handler& aEventHandler) :
		native_window(aRenderingEngine, aSurfaceManager),
		iEventHandler(aEventHandler),
		iLogicalCoordinateSystem(neogfx::logical_coordinate_system::AutomaticGui),
		iFrameRate(60),
		iFrameCounter(0),
		iLastFrameTime(0),
		iRendering(false)
	{
#ifdef _WIN32
		ID2D1Factory* m_pDirect2dFactory;
		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);
		FLOAT dpiX, dpiY;
		m_pDirect2dFactory->GetDesktopDpi(&dpiX, &dpiY);
		iPixelDensityDpi = size(static_cast<size::dimension_type>(dpiX), static_cast<size::dimension_type>(dpiY));
#endif
	}
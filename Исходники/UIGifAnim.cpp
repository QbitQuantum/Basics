	CGifAnimUI::~CGifAnimUI(void)
	{
		DeleteGif();
		m_pManager->KillTimer( this, EVENT_TIEM_ID );
		GdiplusShutdown( m_gdiplusToken );	//  卸载GDI接口
	}
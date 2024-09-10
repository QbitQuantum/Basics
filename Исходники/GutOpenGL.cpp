bool GutInitGraphicsDeviceOpenGL(GutDeviceSpec *pSpec)
{
	int multisamples = 0;

	if ( pSpec )
		multisamples = pSpec->m_iMultiSamples;

	// `開啟視窗時就已取得這個用來代表視窗的指標, 直接拿來使用.`
	HWND hWnd = GutGetWindowHandleWin32();
	if ( hWnd==NULL )
		return false;

	if ( multisamples )
	{
		if ( !SetPixelformatEX(pSpec) )
		{
			return false;
		}
	}
	else
	{
		if ( !SetPixelformat() )
		{
			return false;
		}
	}

	glewInit();
	FixupGLExt();

	return true;
}
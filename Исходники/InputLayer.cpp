InputLayer::InputLayer( 
	HINSTANCE hInst, 
	HWND hWnd, 
	bool bExclusive, 
	bool bUseKeyboard, 
	bool bUseMouse )
{


	m_pKeyboard = NULL;
	m_pMouse = NULL;

	if( m_pGlobalILayer )
	{
		assert(false);
	}
	m_pGlobalILayer = this;

	HRESULT hr;

	/**
	 * ´´½¨DI8 ¶ÔÏó
	 */
	HR(DirectInput8Create( hInst, DIRECTINPUT_VERSION, 
						IID_IDirectInput8, (void**)&m_pDI, NULL ));

	if( bUseKeyboard )
	{
		m_pKeyboard = new Keyboard( hWnd );
	}
	if( bUseMouse )
	{
		m_pMouse = new Mouse( hWnd, bExclusive );
	}

}
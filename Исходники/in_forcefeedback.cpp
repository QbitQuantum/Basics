//-----------------------------------------------------------------------------
// Purpose: Init_ForceFeedback 
//-----------------------------------------------------------------------------
void CInput::Init_ForceFeedback() 
{ 
	// abort startup if user requests no joystick
	if ( CommandLine()->FindParm("-noff" ) ) 
	{
		return; 
	}
 
	Assert( !m_pFF );

	m_pFF = new ForceFeedbackParams_t;
	Assert( m_pFF );
	Q_memset( m_pFF, 0, sizeof( *m_pFF ) );

	HRESULT hr = DirectInput8Create(GetModuleHandle(0), DIRECTINPUT_VERSION, 
        IID_IDirectInput8, (void**)&m_pFF->m_pIInput, NULL ); 

	if ( FAILED( hr ) )
	{
		return;
	}

	hr = m_pFF->m_pIInput->CreateDevice(GUID_Joystick, &m_pFF->m_pIJoystick, NULL );
	if ( FAILED( hr ) )
	{
		return;
	}

	hr = m_pFF->m_pIJoystick->SetDataFormat(&c_dfDIJoystick2 );

	if ( FAILED( hr ) )
	{
		return;
	}
	
	HWND mainWnd = (HWND)g_pEngineWindow->GetWindowHandle();

	hr = m_pFF->m_pIJoystick->SetCooperativeLevel( mainWnd, DISCL_BACKGROUND | DISCL_EXCLUSIVE );

	if ( FAILED( hr ) )
	{
		return;
	}

	DIPROPDWORD dwd;
	//The following code turns the center spring off
	dwd.diph.dwSize       = sizeof(DIPROPDWORD);
	dwd.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dwd.diph.dwObj        = 0;
	dwd.diph.dwHow        = DIPH_DEVICE;
	dwd.dwData            = FALSE;

	if ( !ff_autocenter.GetBool() )
	{
		hr = m_pFF->m_pIJoystick->SetProperty( DIPROP_AUTOCENTER, &dwd.diph );
		if ( FAILED( hr ) )
		{
			return;
		}
	}

    // Acquire the device
	hr = m_pFF->m_pIJoystick->Acquire();

    if( FAILED( hr ) )
	{
        return;
	}

	DIDEVCAPS diDevCaps;
	Q_memset( &diDevCaps, 0, sizeof( diDevCaps ) );
	diDevCaps.dwSize = sizeof( diDevCaps );

	hr = m_pFF->m_pIJoystick->GetCapabilities( &diDevCaps );

	if ( FAILED( hr ) )
	{
		DevMsg( "GetCapabilities failed\n" );
		return;
	}

	if ( !( diDevCaps.dwFlags & DIDC_FORCEFEEDBACK ) )
	{
		// Doesn't support FF
		return;
	}

	DIDEVICEINSTANCE diDI;
	Q_memset( &diDI, 0, sizeof( diDI ) );
	diDI.dwSize = sizeof( diDI );

	hr = m_pFF->m_pIJoystick->GetDeviceInfo( &diDI );
	if ( FAILED( hr ) )
	{
		DevMsg( "GetDeviceInfo failed\n" );
		return;
	}

	DevMsg( "Forcefeedback device found:\n" ); 

	//DevMsg( "  device '%s'\n", diDI.tszInstanceName );
	DevMsg( "  product '%s'\n", diDI.tszProductName );

	DescribeFFDevice( diDevCaps );
	
	InitEffectMap();

	LoadEffectFiles( m_pFF->m_pIJoystick );

	m_pFF->m_bForceFeedbackAvailable = true; 
}
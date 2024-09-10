void CDirectXFramework::Init(HWND& hWnd, HINSTANCE& hInst, bool bWindowed)
{
	m_hWnd = hWnd;
	CoInitialize(NULL);
	
	CoCreateInstance( CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
                  IID_IGraphBuilder, (void**)&m_pGraphBuilder);

	m_pGraphBuilder->QueryInterface(IID_IMediaControl,
                                (void**)&m_pMediaControl);

	m_pGraphBuilder->QueryInterface(IID_IMediaEvent,
                                (void**)&m_pMediaEvent);

	m_pGraphBuilder->RenderFile(L"intro.wmv", NULL);

	m_pMediaControl->QueryInterface(IID_IVideoWindow,
                                (void**)&m_pVideoWindow);
	// Setup the window
	m_pVideoWindow->put_Owner((OAHWND)m_hWnd);
	// Set the style
	m_pVideoWindow->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE);
	// Obtain the size of the window
	RECT WinRect;
	GetClientRect(m_hWnd, &WinRect);
	// Set the video size to the size of the window
	WinRect.top = 0;
	WinRect.bottom = 600;
	WinRect.left = 0;
	WinRect.right = 800;
	m_pVideoWindow->SetWindowPosition(WinRect.left, WinRect.top, 
										WinRect.right, WinRect.bottom);

	//////////////////////////////////////////////////////////////////////////
	// Direct3D Foundations - D3D Object, Present Parameters, and D3D Device
	//////////////////////////////////////////////////////////////////////////

	// Create the D3D Object
	m_pD3DObject = Direct3DCreate9(D3D_SDK_VERSION);

	// Find the width and height of window using hWnd and GetWindowRect()
	RECT rect;

	GetWindowRect(hWnd, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// Set D3D Device presentation parameters before creating the device
	D3DPRESENT_PARAMETERS D3Dpp;
	ZeroMemory(&D3Dpp, sizeof(D3Dpp));  // NULL the structure's memory

	D3Dpp.hDeviceWindow					= hWnd;										// Handle to the focus window
	D3Dpp.Windowed						= bWindowed;								// Windowed or Full-screen boolean
	D3Dpp.AutoDepthStencilFormat		= D3DFMT_D24S8;								// Format of depth/stencil buffer, 24 bit depth, 8 bit stencil
	D3Dpp.EnableAutoDepthStencil		= TRUE;										// Enables Z-Buffer (Depth Buffer)
	D3Dpp.BackBufferCount				= 1;										// Change if need of > 1 is required at a later date
	D3Dpp.BackBufferFormat				= D3DFMT_X8R8G8B8;							// Back-buffer format, 8 bits for each pixel
	D3Dpp.BackBufferHeight				= height;									// Make sure resolution is supported, use adapter modes
	D3Dpp.BackBufferWidth				= width;									// (Same as above)
	D3Dpp.SwapEffect					= D3DSWAPEFFECT_DISCARD;					// Discard back-buffer, must stay discard to support multi-sample
	D3Dpp.PresentationInterval			= m_bVsync ? D3DPRESENT_INTERVAL_DEFAULT : D3DPRESENT_INTERVAL_IMMEDIATE; // Present back-buffer immediately, unless V-Sync is on								
	D3Dpp.Flags							= D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;		// This flag should improve performance, if not set to NULL.
	D3Dpp.FullScreen_RefreshRateInHz	= bWindowed ? 0 : D3DPRESENT_RATE_DEFAULT;	// Full-screen refresh rate, use adapter modes or default
	D3Dpp.MultiSampleQuality			= 0;										// MSAA currently off, check documentation for support.
	D3Dpp.MultiSampleType				= D3DMULTISAMPLE_NONE;						// MSAA currently off, check documentation for support.

	// Check device capabilities
	DWORD deviceBehaviorFlags = 0;
	m_pD3DObject->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_D3DCaps);

	// Determine vertex processing mode
	if(m_D3DCaps.DevCaps & D3DCREATE_HARDWARE_VERTEXPROCESSING)
	{
		// Hardware vertex processing supported? (Video Card)
		deviceBehaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;	
	}
	else
	{
		// If not, use software (CPU)
		deviceBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING; 
	}
	
	// If hardware vertex processing is on, check pure device support
	if(m_D3DCaps.DevCaps & D3DDEVCAPS_PUREDEVICE && deviceBehaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING)
	{
		deviceBehaviorFlags |= D3DCREATE_PUREDEVICE;	
	}
	
	// Create the D3D Device with the present parameters and device flags above
	m_pD3DObject->CreateDevice(
		D3DADAPTER_DEFAULT,		// which adapter to use, set to primary
		D3DDEVTYPE_HAL,			// device type to use, set to hardware rasterization
		hWnd,					// handle to the focus window
		deviceBehaviorFlags,	// behavior flags
		&D3Dpp,					// presentation parameters
		&m_pD3DDevice);			// returned device pointer

	//*************************************************************************

	//////////////////////////////////////////////////////////////////////////
	// Create a Font Object
	//////////////////////////////////////////////////////////////////////////
	
	// Load a font for private use for this process

	// Load D3DXFont, each font style you want to support will need an ID3DXFont
	D3DXCreateFont(m_pD3DDevice, 30, 0, FW_BOLD, 0, false, 
                  DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
                  DEFAULT_PITCH | FF_DONTCARE, TEXT("Times New Roman"), 
                  &m_pD3DFont);

	

	//////////////////////////////////////////////////////////////////////////
	// Create Sprite Object and Textures
	//////////////////////////////////////////////////////////////////////////
	// Create a sprite object, note you will only need one for all 2D sprites

	D3DXCreateSprite(m_pD3DDevice, &m_pD3DSprite);
	D3DXCreateSprite(m_pD3DDevice, &m_Ball);
	D3DXCreateSprite(m_pD3DDevice, &m_Wall);

	// Create a texture, each different 2D sprite to display to the screen
	// will need a new texture object.  If drawing the same sprite texture
	D3DXCreateTextureFromFileEx(m_pD3DDevice, L"Paddle.tga", 0, 0, 0, 0,
                  D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
                  D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255), 
                  &m_imageInfo, 0, &m_pTexture);

	D3DXCreateTextureFromFileEx(m_pD3DDevice, L"Ball.tga", 0, 0, 0, 0,
                  D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
                  D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255), 
				  &m_ballImage, 0, &m_ballTexture);

	D3DXCreateTextureFromFileEx(m_pD3DDevice, L"wall.tga", 0, 0, 0, 0,
                  D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
                  D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255), 
				  &m_wallImage, 0, &m_wallTexture);

	D3DXCreateTextureFromFileEx(m_pD3DDevice, L"START.tga", 0, 0, 0, 0,
                  D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
                  D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255), 
				  &m_StartImage, 0, &m_StartText);

	D3DXCreateTextureFromFileEx(m_pD3DDevice, L"CREDITS.tga", 0, 0, 0, 0,
                  D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
                  D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255), 
				  &m_CreditImage, 0, &m_CreditText);
	D3DXCreateTextureFromFileEx(m_pD3DDevice, L"CREDIT2.tga", 0, 0, 0, 0,
                  D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
                  D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255), 
				  &m_Credit2Image, 0, &m_Credit2Text);
	D3DXCreateTextureFromFileEx(m_pD3DDevice, L"EXIT.tga", 0, 0, 0, 0,
                  D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
                  D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255), 
				  &m_ExitImage, 0, &m_ExitText);

	// multiple times, just call that sprite's Draw() with different 
	// transformation values.


	//Paddle 1
	Paddle[0].xp = -12;
	Paddle[0].yp = 300;

	//Paddle 2
	Paddle[1].xp = 800;
	Paddle[1].yp = 300;

	//Ball
	Ball.xp = 400;
	Ball.yp = 300;

	//	Wall / Background
	Wall.xp = 400;
	Wall.yp = 300;

	//	Menu
	Menu.xp = 200;
	Menu.yp = 200;
	



	//Initial Direction
	Ball.DIR_UP_RIGHT = true;

	//MENU
	Menu.onGAME = false;
	Menu.onSTART = true;
	

	//*************************************************************************

	// create direct input object
	DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8,(void **)&m_pDIObject, NULL);

	// Create Keyboard
	m_pDIObject->CreateDevice(GUID_SysKeyboard, &m_pDIKeyboard, NULL);

	//Set Keyboard data format
	m_pDIKeyboard->SetDataFormat(&c_dfDIKeyboard); 

	//Set Keyboard coop level
	m_pDIKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE); 

	// Create Mouse
	m_pDIObject->CreateDevice(GUID_SysMouse, &m_pDIMouse, NULL);

	// Set Mouse Data Format
	m_pDIMouse->SetDataFormat(&c_dfDIMouse2);

	// Set Mouse Coop Level
	m_pDIMouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);


	//SOUND INITIALIZATION
	channel = 0;
	result = FMOD::System_Create(&system);
	
	result = system->init(100, FMOD_INIT_NORMAL, 0); // initialize fmod

	result = system->createSound("beep1.ogg", FMOD_DEFAULT, 0, &mySound1);
	result = system->createSound("beep2.ogg", FMOD_DEFAULT, 0, &mySound2);
	result = system->createSound("pongMusic.wav", FMOD_LOOP_NORMAL | FMOD_2D, 0, &myStream);


//BACKGROUND MUSIC---------------------------------------------
		result = system->playSound(myStream, 0, true, &channel);
		result = channel->setVolume(0.5f);
		result = channel->setPaused(false);
//-------------------------------------------------------------
}
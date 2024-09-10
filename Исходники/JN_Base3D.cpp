	//< d3d초기화
	HRESULT			Init3D( HWND hWnd , HINSTANCE hInst, BOOL bWindowMode, INT nWidth, INT nHeight )
	{
		m_hWnd	= hWnd;
		m_hInst	= hInst;

		//< d3d객체 인터페이스 생성
		m_pd3d = Direct3DCreate9( D3D_SDK_VERSION );

		//< 예외 처리 
		if( m_pd3d == NULL )
		{
			//< 에러 
			return E_FAIL;
		}

		//< 하드웨어 가속 여부 확인 (Caps)
		D3DCAPS9		caps;	//< 장치 정보 
		DWORD			dwVp;	//< 버텍스 프로세싱
		D3DDEVTYPE		sDevType;

		m_pd3d->GetDeviceCaps(D3DADAPTER_DEFAULT , D3DDEVTYPE_HAL, &caps);

		if( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
		{
			dwVp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
			sDevType = D3DDEVTYPE_HAL;
		}
		else
		{
			dwVp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
			sDevType = D3DDEVTYPE_SW;
		}

		//< D3D파라메터 설정 
		D3DPRESENT_PARAMETERS		d3dpp;
		ZeroMemory(&d3dpp,sizeof(D3DPRESENT_PARAMETERS));

		d3dpp.BackBufferWidth			= nWidth;
		d3dpp.BackBufferHeight			= nHeight;
		d3dpp.BackBufferCount			= 1;
		d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat			= D3DFMT_X8R8G8B8;
		d3dpp.AutoDepthStencilFormat	= D3DFMT_D24S8;	
		d3dpp.EnableAutoDepthStencil	= TRUE;	
		d3dpp.Windowed					= bWindowMode;

		//< 디바이스 생성
		if( FAILED(m_pd3d->CreateDevice(
			D3DADAPTER_DEFAULT,
			sDevType,
			m_hWnd,
			dwVp,
			&d3dpp,
			&m_pd3dDevice)))
		{
			//< 디바이스 예외 처리 
			return E_FAIL;
		}

		//< 끝~~
		return S_OK;
	}
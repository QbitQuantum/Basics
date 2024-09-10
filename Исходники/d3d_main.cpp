int D3DM_InitDevices( HWND hwnd, int w, int h, int full, HMENU menu )
{
	char	buf[256];
	int		i,j;
		LPDIRECTDRAW7 pDD = NULL;	
		HRESULT hr;
		if( FAILED( hr = DirectDrawCreateEx( NULL, (VOID**)&pDD, IID_IDirectDraw7, NULL ) ) )
			return DDENUMRET_CANCEL;

		D3DCapsStruct.m_ddCaps.dwSize = sizeof(DDCAPS);
		pDD->GetCaps( &D3DCapsStruct.m_ddCaps, NULL );
		if(pDD) {
			pDD->Release();
			pDD = NULL;
		}
	ZeroMemory( d3dTexture, sizeof(D3DD_TEXTURE)*D3DD_MAX_TEXTURE_AMOUNT );
	ZeroMemory( d3dText, sizeof(D3DD_TEXT)*D3DD_MAX_TEXT_AMOUNT );
	ZeroMemory( d3dDisp, sizeof(D3DD_DISP)*D3DD_MAX_DISP_AMOUNT );


	
	pD3D = Direct3DCreate8(D3D_SDK_VERSION);
	if(pD3D == NULL){
		MessageBox(NULL,"Direct3Dオブジェクトの生成に失敗しました。[DirectX8.1が入っていない？]","致命的なエラー", MB_OK | MB_ICONSTOP);
		return FALSE;
	}

	
	if( FAILED(pD3D->GetDeviceCaps( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &D3DCapsStruct.m_d3dCaps)) ){
		MessageBox(NULL,"デバイス能力の取得に失敗しました","致命的なエラー", MB_OK | MB_ICONSTOP);
		return FALSE;
	}
	
	EnumAdapters(D3DADAPTER_DEFAULT);

	
	if( (int)D3DCapsStruct.m_d3dCaps.MaxTextureWidth < D3DD_TEXTURE_CONTROL_SIZE ){
		DebugBox( NULL, "このビデオカードは、幅 %d pixel 以上のサイズのテクスチャを生成できません。[%s]", D3DD_TEXTURE_CONTROL_SIZE);
		return FALSE;
	}else if( (int)D3DCapsStruct.m_d3dCaps.MaxTextureHeight < D3DD_TEXTURE_CONTROL_SIZE ){
		DebugBox( NULL, "このビデオカードは、高さ %d pixel 以上のサイズのテクスチャを生成できません。[%s]", D3DD_TEXTURE_CONTROL_SIZE );
		return FALSE;
	}

	if( !(D3DCapsStruct.m_d3dCaps.ShadeCaps&D3DPSHADECAPS_ALPHAGOURAUDBLEND) ){
		MessageBox(NULL,"このビデオデバイスはグーロブレンディングに対応していません。\nゲームの画像が乱れることがあります","警告", MB_OK | MB_ICONSTOP);
	}
	if( !(D3DCapsStruct.m_d3dCaps.ShadeCaps&D3DPSHADECAPS_COLORGOURAUDRGB) ){
		MessageBox(NULL,"このビデオデバイスはグーロシェーディングに対応していません。\nゲームの画像が乱れることがあります","警告", MB_OK | MB_ICONSTOP);
	}

	if( D3DCapsStruct.m_d3dCaps.TextureCaps&D3DPTEXTURECAPS_SQUAREONLY ){
		DebugBox( NULL, "このビデオカードは長方形テクスチャを生成できません。[デバッグ用ダイアログ]" );
	}

	
	if( FAILED(pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&D3DCapsStruct.m_NowDisplayMode)) ){	
		MessageBox(NULL,"ディスプレイモードの取得に失敗しました。[なにゆえ？]","致命的なエラー", MB_OK | MB_ICONSTOP);
		return FALSE;
	}
	D3DCapsStruct.m_WindowDisplayMode = D3DCapsStruct.m_NowDisplayMode;
	D3DMain.m_DrawHwnd = hwnd;
	D3DMain.m_MenuHwnd = menu;
	if( GetSystemMetrics(SM_CXFULLSCREEN)<=800 || GetSystemMetrics(SM_CYFULLSCREEN)<=600){
		D3DMain.m_FullScreenOnly = TRUE;
		D3DMain.m_WindowMode = FALSE;
	}else{
		D3DMain.m_FullScreenOnly = FALSE;
		D3DMain.m_WindowMode = !full;
	}


	ZeroMemory(&d3dppApp,sizeof(d3dppApp));
	


	WinWidth  = w;
	WinHeight = h;



	d3dppApp.SwapEffect = D3DSWAPEFFECT_COPY;

	d3dppApp.BackBufferFormat = D3DCapsStruct.m_NowDisplayMode.Format;
	d3dppApp.BackBufferCount = 1;
	d3dppApp.BackBufferWidth  = WinWidth;
	d3dppApp.BackBufferHeight = WinHeight;





	d3dppApp.Windowed = TRUE;							
	d3dppApp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	
	HRESULT	ret;
	ret = pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hwnd,D3DCREATE_HARDWARE_VERTEXPROCESSING,&d3dppApp,&pD3DDevice);
	if( FAILED(ret) ){	
		ret = pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hwnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dppApp,&pD3DDevice);
		if( FAILED(ret) ){	
			D3DMain.m_FullScreenOnly = TRUE;
		}
	}
	if(D3DMain.m_FullScreenOnly==TRUE){
		RELEASE_3D(pD3DDevice);

		D3DMain.m_WindowMode = FALSE;
		ZeroMemory(&d3dppApp,sizeof(d3dppApp));
		for(i=0;i<D3DCapsStruct.m_DisplayModeNum;i++){
			if( D3DCapsStruct.m_DisplayMode[i].Width  == 800 && D3DCapsStruct.m_DisplayMode[i].Height == 600 ){
				switch( D3DCapsStruct.m_DisplayMode[i].Format ){
					case D3DFMT_R5G6B5:		case D3DFMT_X1R5G5B5:
					case D3DFMT_A1R5G5B5:	case D3DFMT_A4R4G4B4:
					case D3DFMT_X4R4G4B4:
						D3DCapsStruct.m_FullModeNum=i;

						d3dppApp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
						d3dppApp.Windowed = D3DMain.m_WindowMode;		
						d3dppApp.SwapEffect = FULL_FLIP;		
						d3dppApp.BackBufferFormat = D3DCapsStruct.m_DisplayMode[i].Format;	
						d3dppApp.BackBufferCount = 1;
						d3dppApp.BackBufferWidth  = WinWidth;
						d3dppApp.BackBufferHeight = WinHeight;



						break;
				}
			}
			if(d3dppApp.SwapEffect) break;
		}
		if(!full){
			wsprintf( buf, "このビデオカードの現在のモードではゲームを実行できません。フルスクリーン化しますか？\n[%d]", D3DCapsStruct.m_DisplayMode[i].RefreshRate );
			if( MessageBox( NULL, buf, "問い合わせ", MB_YESNO )==IDNO ){
				RELEASE_3D(pD3D);
				return FALSE;
			}
		}

		ret = pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hwnd,D3DCREATE_HARDWARE_VERTEXPROCESSING,&d3dppApp,&pD3DDevice);
		if( FAILED(ret) ){	
			ret = pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hwnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dppApp,&pD3DDevice);
			if( FAILED(ret) ){	
				switch(ret){
				default:
				case D3DERR_OUTOFVIDEOMEMORY:
					DebugBox( NULL, "Direct3D が処理を行うのに十分なディスプレイ メモリがありません。" );
					RELEASE_3D(pD3D);
					return FALSE;
				case D3DERR_INVALIDCALL:
					DebugBox( NULL, "Direct3Dの初期化に失敗しました[D3DERR_INVALIDCALL]\nこのグラフィックカードは必要な機能をサポートしていないか、\nあるいはDirectX8に対応したドライバが入っていません。" );
					RELEASE_3D(pD3D);
					return FALSE;
				case D3DERR_NOTAVAILABLE:
					DebugBox( NULL, "Direct3Dの初期化に失敗しました[D3DERR_NOTAVAILABLE]\nこのグラフィックカードは必要な機能をサポートしていないか、\nあるいはDirectX8に対応したドライバが入っていません。" );
					RELEASE_3D(pD3D);
					return FALSE;
				}
			}
		}
	}else{
		if(D3DMain.m_WindowMode){	
		}else{
			RELEASE_3D(pD3DDevice);
			ZeroMemory(&d3dppApp,sizeof(d3dppApp));

	
			d3dppApp.SwapEffect = FULL_FLIP;
	
	
			d3dppApp.BackBufferCount = 1;
			d3dppApp.BackBufferWidth  = WinWidth;
			d3dppApp.BackBufferHeight = WinHeight;

		
			d3dppApp.Windowed = FALSE;							
			d3dppApp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;


			if(DrawSetting.full_16bit){
				d3dppApp.BackBufferFormat=D3DFMT_UNKNOWN;
				for(i=0;i<D3DCapsStruct.m_DisplayModeNum;i++){
					if( D3DCapsStruct.m_DisplayMode[i].Width  == 800 && D3DCapsStruct.m_DisplayMode[i].Height == 600 ){
						switch( D3DCapsStruct.m_DisplayMode[i].Format ){
							case D3DFMT_R5G6B5:		case D3DFMT_X1R5G5B5:
							case D3DFMT_A1R5G5B5:	case D3DFMT_A4R4G4B4:
							case D3DFMT_X4R4G4B4:
								D3DCapsStruct.m_FullModeNum=i;
								d3dppApp.BackBufferFormat = D3DCapsStruct.m_DisplayMode[i].Format;	
								break;
						}
					}
					if(d3dppApp.BackBufferFormat!=D3DFMT_UNKNOWN) break;
				}
			}else{
				d3dppApp.BackBufferFormat = D3DCapsStruct.m_NowDisplayMode.Format;
			}

			ret = pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hwnd,D3DCREATE_HARDWARE_VERTEXPROCESSING,&d3dppApp,&pD3DDevice);
			if( FAILED(ret) ){	
				ret = pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hwnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dppApp,&pD3DDevice);
				if( FAILED(ret) ){	
					switch(ret){
					default:
					case D3DERR_OUTOFVIDEOMEMORY:
						DebugBox( NULL, "Direct3D が処理を行うのに十分なディスプレイ メモリがありません。" );
						RELEASE_3D(pD3D);
						return FALSE;
					case D3DERR_INVALIDCALL:
						DebugBox( NULL, "Direct3Dの初期化に失敗しました[D3DERR_INVALIDCALL]\nこのグラフィックカードは必要な機能をサポートしていないか、\nあるいはDirectX8に対応したドライバが入っていません。" );
						RELEASE_3D(pD3D);
						return FALSE;
					case D3DERR_NOTAVAILABLE:
						DebugBox( NULL, "Direct3Dの初期化に失敗しました[D3DERR_NOTAVAILABLE]\nこのグラフィックカードは必要な機能をサポートしていないか、\nあるいはDirectX8に対応したドライバが入っていません。" );
						RELEASE_3D(pD3D);
						return FALSE;
					}
				}
			}
		}
	}



	if( FAILED(pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&D3DCapsStruct.m_NowDisplayMode)) ){	
		MessageBox(NULL,"ディスプレイモードの取得に失敗しました。[なにゆえ？]","致命的なエラー", MB_OK | MB_ICONSTOP);
		RELEASE_3D(pD3D);
		return FALSE;
	}
	D3DCapsStruct.m_ttCaps.m_R8G8B8		= IsTextureFormatOk( D3DFMT_R8G8B8,   D3DCapsStruct.m_NowDisplayMode.Format);
	D3DCapsStruct.m_ttCaps.m_X8R8G8B8	= IsTextureFormatOk( D3DFMT_X8R8G8B8, D3DCapsStruct.m_NowDisplayMode.Format);
	D3DCapsStruct.m_ttCaps.m_A8R8G8B8	= IsTextureFormatOk( D3DFMT_A8R8G8B8, D3DCapsStruct.m_NowDisplayMode.Format);

	D3DCapsStruct.m_ttCaps.m_R5G6B5		= IsTextureFormatOk( D3DFMT_R5G6B5,   D3DCapsStruct.m_NowDisplayMode.Format);
	D3DCapsStruct.m_ttCaps.m_X1R5G5B5	= IsTextureFormatOk( D3DFMT_X1R5G5B5, D3DCapsStruct.m_NowDisplayMode.Format);
	D3DCapsStruct.m_ttCaps.m_A1R5G5B5	= IsTextureFormatOk( D3DFMT_A1R5G5B5, D3DCapsStruct.m_NowDisplayMode.Format);

	D3DCapsStruct.m_ttCaps.m_X4R4G4B4	= IsTextureFormatOk( D3DFMT_X4R4G4B4, D3DCapsStruct.m_NowDisplayMode.Format);
	D3DCapsStruct.m_ttCaps.m_A4R4G4B4	= IsTextureFormatOk( D3DFMT_A4R4G4B4, D3DCapsStruct.m_NowDisplayMode.Format);

	D3DCapsStruct.m_ttCaps.m_A8P8		= IsTextureFormatOk( D3DFMT_A8P8,     D3DCapsStruct.m_NowDisplayMode.Format);
	D3DCapsStruct.m_ttCaps.m_P8			= IsTextureFormatOk( D3DFMT_P8,       D3DCapsStruct.m_NowDisplayMode.Format);
	D3DCapsStruct.m_ttCaps.m_A8			= IsTextureFormatOk( D3DFMT_A8,       D3DCapsStruct.m_NowDisplayMode.Format);
	
	D3DD_SetBackBuffer( WinWidth, WinHeight );
	pD3DDevice->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_ARGB(0,0,0,0),1.0,0);

	if(0){
		char	buf2[512];

		wsprintf( buf, "実行ディスプレイモード[%s]\n", TxFmtMode[ LIM(d3dppApp.BackBufferFormat,0,D3DFMT_D3DD_MAX-1) ] );
		MBS_CPY(buf2,buf);

		MBS_CAT(buf2,"使用可能テクスチャ列挙\n");
		for(i=1;i<D3DFMT_D3DD_MAX-1;i++){
			if( TxFmtMode[i] ){
				j = IsTextureFormatOk( (D3DFORMAT)i, D3DCapsStruct.m_NowDisplayMode.Format);
				if(j){
					wsprintf(buf,"%-15s[%s]\n", TxFmtMode[i], (j==2)?"OK":"OK(NotRenderTarget)" );
					MBS_CAT(buf2,buf);
				}else{
					wsprintf(buf,"%-15s[%s]\n", TxFmtMode[i], "--Not--" );
					MBS_CAT(buf2,buf);
				}
			}
		}

		
		DebugBox(NULL,buf2);



	}

	D3DD_CreateTable();

	return TRUE;
}
HRESULT InitD3D(HINSTANCE hInstance)
{
	// 先创建DInput和DSound
	if(FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pDI, NULL)))
		return E_FAIL;
	if(FAILED(g_pDI->CreateDevice(GUID_SysKeyboard, &g_pDIKey, NULL)))
		return E_FAIL;
	if(FAILED(g_pDI->CreateDevice(GUID_SysMouse, &g_pDIMouse, NULL)))
		return E_FAIL;
		// 设置参数
	if(FAILED(g_pDIKey->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
		return E_FAIL;
	if(FAILED(g_pDIKey->SetDataFormat(&c_dfDIKeyboard)))
		return E_FAIL;
	if(FAILED(g_pDIMouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
		return E_FAIL;
	if(FAILED(g_pDIMouse->SetDataFormat(&c_dfDIMouse)))
		return E_FAIL;
		
		// 缓冲输入，设置数据格式和属性
	DIPROPDWORD dipdw;
	dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj        = 0;
	dipdw.diph.dwHow        = DIPH_DEVICE;
	dipdw.dwData            = SAMPLE_BUFFER_SIZE; // Arbitary buffer size

#ifdef USE_BUFFERED_KEYBOARD_INPUT
	if( FAILED( g_pDIKey->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph ) ) )
		return E_FAIL;
#endif
#ifdef USE_BUFFERED_MOUSE_INPUT
	if( FAILED( g_pDIMouse->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph ) ) )
		return E_FAIL;
#endif

		// 开始
	g_pDIKey->Acquire();
	g_pDIMouse->Acquire();



	// 初始化D3D
	if(NULL==(d3d=Direct3DCreate9(D3D_SDK_VERSION)))
		  return E_FAIL;

	//查询当前显卡模式，Desktop是目前桌面设置，d3ddm总是当前使用全屏模式的设置，即使是窗口模式，颜色数值也总和当前的一样
	if(FAILED(d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &DesktopDisplayMode)))
		  return E_FAIL;
	if(FAILED(d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
		return E_FAIL;

	//全屏的话默认是32位色
	if(!WindowMode) d3ddm.Format = D3DFMT_X8R8G8B8;

	//查询设备能力，并设置顶点处理器模式
	DWORD UserVertexShaderProcessing;

	d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dcaps);

	if(FAILED(DetectDeviceCaps())) return E_FAIL;

	if(d3dcaps.VertexShaderVersion < D3DVS_VERSION(1, 0))
		UserVertexShaderProcessing=D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		UserVertexShaderProcessing=D3DCREATE_SOFTWARE_VERTEXPROCESSING;

//创建D3D设备
	ZeroMemory(&d3dpp,sizeof(d3dpp));

	d3dpp.Windowed = WindowMode;
	d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = d3ddm.Width;
	d3dpp.BackBufferHeight = d3ddm.Height;
	d3dpp.EnableAutoDepthStencil = TRUE;
	
	if(WindowMode)
	{
		d3ddm.Format = DesktopDisplayMode.Format;
		d3dpp.BackBufferWidth = WindowWidth;
		d3dpp.BackBufferHeight = WindowHeight;
	}

	d3dpp.BackBufferFormat = d3ddm.Format;

	if(d3ddm.Format == D3DFMT_X8R8G8B8)
	{
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
		TextureFormat = D3DFMT_A8R8G8B8;
	}
	else
	{
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		TextureFormat = D3DFMT_A4R4G4B4;
	}


	// 先强制以硬件顶点方式创建设备（为了不漏掉MX440这种不支持VS但支持T&L的显卡，XIXI）
	UserVertexShaderProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	HRESULT hr = d3d->CreateDevice( D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL, hWnd, UserVertexShaderProcessing, &d3dpp, &d3ddevice);
	// 这种错误表示顶点处理方式不被硬件支持，强制以软件方式创建设备（为了兼容不支持T&L的DX7显卡，比如某些集成显卡）
	if(hr == D3DERR_INVALIDCALL)
	{
		mymessage("警告：显卡不支持硬件顶点处理，强制以软件方式创建设备，性能会急剧下降！！！");
		UserVertexShaderProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
		hr = d3d->CreateDevice( D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL, hWnd, UserVertexShaderProcessing, &d3dpp, &d3ddevice);
	}
	// 全部失败？有问题吧？
	if(FAILED(hr))
	{
		char szErrorInfo[512] = "";
		sprintf(szErrorInfo, "创建D3D设备失败！请检查系统或硬件设置！比如显卡驱动程序或DirectX是否安装正确！错误号%x", hr);
		mymessage(szErrorInfo);
		return E_FAIL;
	}

	// Shader版本检测
	char pVSVersion[7] = "", pPSVersion[7] = "";
	char pNeedVSVersion[7] = USE_VSVERSION, pNeedPSVersion[7] = USE_PSVERSION;
	char szErrorInfo[100] = "";

#ifdef USE_PIXELSHADER
	// 判断PS版本
	memcpy(pPSVersion, D3DXGetPixelShaderProfile(d3ddevice), 7);
	// 2.x中'b'虽然字母数值大于'a'，但它从支持度上来看是小于a的，所以这里强制把它置为小于'a'，以便后面比较
	if(pPSVersion[3] == '2' && pPSVersion[5] == 'b')
		pPSVersion[5] = 'a'-1;
	if(pNeedPSVersion[3] == '2' && pNeedPSVersion[5] == 'b')
		pNeedPSVersion[5] = 'a'-1;
	if(pPSVersion[3]<pNeedPSVersion[3] || pPSVersion[3]==pNeedPSVersion[3]&&pPSVersion[5]<pNeedPSVersion[5])
	{
		sprintf(szErrorInfo, "不支持Pixel Shader %c.%c！", pNeedPSVersion[3], pNeedPSVersion[5]);
		mymessage(szErrorInfo);	return E_FAIL;
	}
	
	// 判断PS2.0x的条件是否符合程序的最小需求
	if(!strcmp(USE_PSVERSION, "ps_2_a") || !strcmp(USE_PSVERSION, "ps_2_b") || !strcmp(USE_PSVERSION, "ps_2_x"))
	{
		BOOL bFlowControl = FALSE;
#ifdef PS2x_USE_FLOWCONTROL
		bFlowControl = TRUE;
#endif

		if(!CheckPS2xSupport(PS2x_USE_MAXNUM_TEMP, bFlowControl))
		{
			sprintf(szErrorInfo, "不完整支持Pixel Shader 2.x，无法执行程序！");
			mymessage(szErrorInfo);	return E_FAIL;
		}
	}


#endif USE_PIXELSHADER

#ifdef USE_VERTEXSHADER
	BOOL bSoftwareVertexProcessing = FALSE;
	// 完全不支持的，要跳过版本检测，否则D3DXGetVertexShaderProfile会返回空指针造成非法操作
	if((d3dcaps.VertexShaderVersion&0xffff) == 0) 
	{
		bSoftwareVertexProcessing = TRUE;
	}
	else
	{
		// 判断VS版本
		memcpy(pVSVersion, D3DXGetVertexShaderProfile(d3ddevice), 7);
		if(pVSVersion[3]<pNeedVSVersion[3] || pVSVersion[3]==pNeedVSVersion[3]&&pVSVersion[5]<pNeedVSVersion[5])
		{
			bSoftwareVertexProcessing = TRUE;
		}
		// 判断VS2.0x的条件是否符合程序的最小需求
		if(!strcmp(USE_VSVERSION, "vs_2_a") || !strcmp(USE_VSVERSION, "vs_2_b") || !strcmp(USE_VSVERSION, "vs_2_x"))
		{
#ifdef VS2a_USE_MAXNUM_TEMP
			if(d3dcaps.VS20Caps.NumTemps < VS2x_USE_MAXNUM_TEMP)
			{
				bSoftwareVertexProcessing = TRUE;
			}
#endif
		}
	}

	// 如果刚才是以硬件顶点创建设备的，而现在又需要强制软顶点以运行硬件不支持的VS，那么释放设备，重新创建
	if(bSoftwareVertexProcessing && UserVertexShaderProcessing == D3DCREATE_HARDWARE_VERTEXPROCESSING)
	{
		// 如果不支持指定版本的Vertex Shader，就强制创建软顶点处理设备
		sprintf(szErrorInfo, "警告：显卡不支持Vertex Shader %c.%c！强制以软件方式创建设备，性能会急剧下降！！！", pNeedVSVersion[3], pNeedVSVersion[5]);
		mymessage(szErrorInfo);
		SAFE_RELEASE(d3ddevice);
		hr = d3d->CreateDevice( D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddevice);
		if(FAILED(hr))
		{
			char szErrorInfo[512] = "";
			sprintf(szErrorInfo, "创建D3D设备失败！请检查系统或硬件设置！比如显卡驱动程序或DirectX是否安装正确！错误号%x", hr);
			mymessage(szErrorInfo);
			return E_FAIL;
		}
	}

#endif



	//初始化摄像机，之所以放在这里，是为了设备丢失后不会又重置到初始位置
	D3DXVECTOR3 PtLookAt = g_PtCameraInitPos + g_VecCameraInitDir;
	CameraChange.InitCamera(g_PtCameraInitPos.x, g_PtCameraInitPos.y, g_PtCameraInitPos.z,  PtLookAt.x, PtLookAt.y, PtLookAt.z,  0.0f,1.0f,0.0f, 7,7,90);

	//得到硬件精确计时器的频率
	QueryPerformanceFrequency(&PerformanceFrequency);

	return S_OK;
}
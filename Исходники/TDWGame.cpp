BOOL InitD3D(HWND hwnd)
{
	HRESULT hr;
	D3DDISPLAYMODE disp_mode;
	D3DPRESENT_PARAMETERS pp;

	if (g_bSetupOK) return TRUE;

	if (g_pD3D) return FALSE;

	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!g_pD3D) return FALSE;
	
	hr = g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &disp_mode);
	if (FAILED(hr)) 
	{
		g_pD3D->Release();
		g_pD3D = NULL;
		return FALSE;
	}
	
	ZeroMemory(&pp, sizeof(D3DPRESENT_PARAMETERS));
	pp.Windowed = true;
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pp.BackBufferFormat = disp_mode.Format;
	pp.EnableAutoDepthStencil = TRUE;
	pp.AutoDepthStencilFormat = D3DFMT_D16;
    pp.BackBufferCount = 1;

	BOOL flgSoft = GetPrivateProfileInt("GENERIC","LEVEL",1,".\\TDWGame.ini");

	char buff[256];
	wsprintf(buff,"%d",flgSoft);
	WritePrivateProfileString("GENERIC","LEVEL",buff,".\\TDWGame.ini");

	hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hwnd,D3DCREATE_HARDWARE_VERTEXPROCESSING,&pp,&g_pD3DDevice);
	if (FAILED(hr))
	{
		hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hwnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&pp,&g_pD3DDevice);
		if (FAILED(hr)) 
		{
			hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_REF,hwnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&pp,&g_pD3DDevice);
			if (FAILED(hr)) 
			{
				g_pD3D->Release();
				g_pD3D = NULL;
				return FALSE;
			}
		}
	}

	D3DCAPS9 DX9DCaps;
	g_pD3DDevice->GetDeviceCaps(&DX9DCaps);
	g_bSetupOK = TRUE;
	return TRUE;	
}
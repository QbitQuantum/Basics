//==================================
//  函数:InitD3D( HWND )
//  目的:初始化Direct3D设备对象
//
bool _InitD3D(HWND hwnd,RECT* Rect,const char* font_lib)
{
	dhwnd = hwnd;
	if(Rect)
	{
		drect.bottom = Rect->bottom-Rect->top;
		drect.right  = Rect->right-Rect->left;
	}
	else
	{
		GetClientRect(dhwnd, &drect);
	}

	imgbase* **&map = full_map.full_map;
	//初始化窗口map(用于检测btn)
	map = new imgbase* *[drect.right];
	for(int i=0;i<drect.right;i++)
		map[i] = new imgbase*[drect.bottom];

	for(int x=0;x<drect.right;x++)
	{
		for(int y=0;y<drect.bottom;y++)
			map[x][y] = 0;
	}
	full_map.width = drect.right; full_map.height = drect.bottom;

	//创建Direct3D对象    [用于获取硬件信息]
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(g_pD3D==NULL) return false;

	//检查是否支持硬件顶点处理
	D3DCAPS9 caps;
	g_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,&caps);
	int vp=0;
	if(caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp=D3DCREATE_HARDWARE_VERTEXPROCESSING;  //硬件处理
	else
		vp=D3DCREATE_SOFTWARE_VERTEXPROCESSING;  //软件处理


	//设置D3DPRESENT_PARAMETERS结构
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp,sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	//创建Direct3D设备对象     [用于渲染图形]
	if( FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,dhwnd,vp,&d3dpp,&g_pd3dD)) )
		return false;


	setupViewAndProjMat();		//设置观察和投影矩阵
	for(int i=0; i<=2; i++)
	{
		//设置线性过滤
		g_pd3dD->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
		g_pd3dD->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);

		//设置纹理寻址模式
		g_pd3dD->SetSamplerState(i, D3DSAMP_BORDERCOLOR, 0x00000000);
		g_pd3dD->SetSamplerState(i, D3DSAMP_ADDRESSU,    D3DTADDRESS_BORDER);
		g_pd3dD->SetSamplerState(i, D3DSAMP_ADDRESSV,    D3DTADDRESS_BORDER);
	}

	g_pd3dD->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );	//正反面都绘制
	g_pd3dD->SetRenderState( D3DRS_LIGHTING, FALSE );			//关闭光照

	//激活alpha混合
	g_pd3dD->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	g_pd3dD->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	g_pd3dD->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pd3dD->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	if(!InitImg())		//初始化图片模块
		return false;
	if(!initText(font_lib))		//初始化字体模块
		return false;
	return true;
}
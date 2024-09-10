//==================================
//  函数:InitD3D( HWND )
//  目的:初始化Direct3D设备对象
//
bool InitD3D()
{
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

	//检查硬件支持的shader的版本
/*	if(caps.VertexShaderVersion < D3DVS_VERSION(2,0))
		deviceType = D3DDEVTYPE_REF;
	else
		deviceType = D3DDEVTYPE_HAL;*/

	//设置D3DPRESENT_PARAMETERS结构
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp,sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
//	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;  //实时模式,默认是根据屏幕刷新频率

	//创建Direct3D设备对象     [用于渲染图形]
	if( FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hwnd,vp,&d3dpp,&g_pd3dD)) )
		return false;

	//设置观察和投影矩阵
	setupViewAndProjMat();

	//设置线性过滤
	g_pd3dD->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	g_pd3dD->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	g_pd3dD->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	g_pd3dD->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);

	//设置纹理寻址模式
	g_pd3dD->SetSamplerState(0, D3DSAMP_BORDERCOLOR, 0x00000000);
	g_pd3dD->SetSamplerState(0, D3DSAMP_ADDRESSU,    D3DTADDRESS_BORDER);
	g_pd3dD->SetSamplerState(0, D3DSAMP_ADDRESSV,    D3DTADDRESS_BORDER);
	g_pd3dD->SetSamplerState(1, D3DSAMP_BORDERCOLOR, 0x00000000);
	g_pd3dD->SetSamplerState(1, D3DSAMP_ADDRESSU,    D3DTADDRESS_BORDER);
	g_pd3dD->SetSamplerState(1, D3DSAMP_ADDRESSV,    D3DTADDRESS_BORDER);
	g_pd3dD->SetSamplerState(2, D3DSAMP_BORDERCOLOR, 0x00000000);
	g_pd3dD->SetSamplerState(2, D3DSAMP_ADDRESSU,    D3DTADDRESS_BORDER);
	g_pd3dD->SetSamplerState(2, D3DSAMP_ADDRESSV,    D3DTADDRESS_BORDER);

	//正反面都绘制
	g_pd3dD->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
    //关闭光照
	g_pd3dD->SetRenderState( D3DRS_LIGHTING, FALSE );

	//激活alpha混合
	g_pd3dD->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	g_pd3dD->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	g_pd3dD->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pd3dD->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	InitVertex();      //初始化顶点缓存,用于装载贴图

	return true;
}
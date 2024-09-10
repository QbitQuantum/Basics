int CDX7Video::Init(HWND wnd,HINSTANCE inst,int w,int h,int b)
{
typedef struct mode_s
	{
	u32 x,y;
	} mode_t;
mode_t modes[] =
	{
	{256,240},
	{256,256},
	{320,240},
	{640,480},
	{800,600},
	{1024,768}
	};
screen8 = 0;
screen16 = 0;
screen32 = 0;
width = w;
height = h;
bpp = b;
hwnd = wnd;
hinstance = inst;
lpDD = 0;
lpDDSPrimary = 0;
lpDDSBack = 0;
renderstart = 0;
memset(&ddsd,0,sizeof(ddsd));
if(DirectDrawCreateEx(0,(VOID**)&lpDD,IID_IDirectDraw7,0))
	{
	log_message("dx7video_c::init: error: DirectDrawCreateEx\n");
	return(1);
	}
if(bpp == 0) //windowed mode
	{
	if(lpDD->SetCooperativeLevel(hwnd,DDSCL_NORMAL) != DD_OK)
		{
		log_message("dx7video_c::init: error: SetCooperativeLevel\n");
		Kill();
		return(1);
		}
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	if(lpDD->CreateSurface(&ddsd,&lpDDSPrimary,0) != DD_OK)
		{
		log_message("dx7video_c::init: error: CreateSurface\n");
		Kill();
		return(1);
		}
	if(lpDD->CreateClipper(0,&lpClipper, NULL) != DD_OK)
		{
		log_message("dx7video_c::init: error: CreateClipper\n");
		Kill();
		return(1);
		}
	lpClipper->SetHWnd(0,hwnd);
	lpDDSPrimary->SetClipper(lpClipper);
	lpClipper->Release();
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS;
	ddsd.dwWidth = w;
	ddsd.dwHeight = h;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	if(lpDD->CreateSurface(&ddsd,&lpDDSBack,0) != DD_OK)
		{
		log_message("dx7video_c::init: error: CreateSurface\n");
		Kill();
		return(1);
		}
	ddsd.dwSize = sizeof(ddsd);
	if(lpDDSBack->GetSurfaceDesc(&ddsd) != DD_OK)
		{
		log_message("dx7video_c::init: error: GetSurfaceDesc\n");
		Kill();
		return(1);
		}
	bpp = (u8)ddsd.ddpfPixelFormat.dwRGBBitCount;
	if(ddsd.ddpfPixelFormat.dwRBitMask == 0xf800 && bpp == 16)
		bpp++;
	switch(bpp & ~1)
		{
		case 8:screen8 = (u8*)malloc(width * height * sizeof(u8));linesize = width;break;
		case 16:screen16 = (u16*)malloc(width * height * sizeof(u16));linesize = width * 2;break;
		case 32:screen32 = (u32*)malloc(width * height * sizeof(u32));linesize = width * 4;break;
		default:Kill();return(1);
		}
	Resize();
	mode = 0;
	lockflags = DDLOCK_WAIT;
	renderstart = 0;
	log_message("dx7video_c::init: inited window mode %dx%d, %d bpp\n",width,height,bpp);
	}
else //fullscreen
	{
	DDSCAPS2 dc;
	DDBLTFX dbf;
	int i,ret;
u32 swidth,sheight;

	if((ret = DirectDrawCreateEx(0,(VOID**)&lpDD,IID_IDirectDraw7,0)) != DD_OK)
		{
		ShowError(ret,"DirectDrawCreateEx");
		Kill();
		return(1);
		}
	if((ret = lpDD->SetCooperativeLevel(hwnd,DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN)) != DD_OK)
		{
		ShowError(ret,"SetCooperativeLevel");
		Kill();
		return(1);
		}
	ret = ~DD_OK;
	i = 3; //start at 640x480
	while(ret != DD_OK && i < 5)
		{
		swidth = modes[i].x;
		sheight = modes[i].y;
		i++;
		if((ret = lpDD->SetDisplayMode(swidth,sheight,bpp,0,0)) != DD_OK)
			ShowError(ret,"SetDisplayMode");
		}
	log_message("dx7video_c::init: using video mode %dx%d\n",swidth,sheight);
	memset(&ddsd,0,sizeof(DDSURFACEDESC2));
	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
	ddsd.dwBackBufferCount = 1;
	if((ret = lpDD->CreateSurface(&ddsd,&lpDDSPrimary,0)) != DD_OK)
		{
		ShowError(ret,"CreateSurface");
		Kill();
		return(1);
		}
	memset(&dc,0,sizeof(DDSCAPS2));
	dc.dwCaps = DDSCAPS_BACKBUFFER;
	if((ret = lpDDSPrimary->GetAttachedSurface(&dc,&lpDDSBack)) != DD_OK)
		{
		ShowError(ret,"GetAttachedSurface");
		Kill();
		return(1);
		}
	if((ret = lpDDSBack->GetSurfaceDesc(&ddsd)) != DD_OK)
		{
		ShowError(ret,"GetSurfaceDesc");
		Kill();
		return(1);
		}
	Resize();
	if(ddsd.ddpfPixelFormat.dwRBitMask == 0xf800 && bpp == 16)
		bpp++;
	if(bpp & 8)
		{
		log_message("no 8bit support\n");
		}
	memset(&dbf,0,sizeof(DDBLTFX));
	dbf.dwSize = sizeof(DDBLTFX);
	dbf.dwFillColor = 0;
	lpDDSBack->Blt(0,0,0,DDBLT_WAIT|DDBLT_COLORFILL,&dbf);
	lpDDSPrimary->Blt(0,0,0,DDBLT_WAIT|DDBLT_COLORFILL,&dbf);
	if((ret = lpDDSBack->Lock(0,&ddsd,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,0)) == DD_OK)
		{
		int xpos = 0;
		int ypos = 0;

		if(swidth >= (u32)width)
			xpos = ((swidth / 2) - (width / 2)) * (bpp / 8);
		if(sheight >= (u32)height)
			ypos = (sheight / 2) - (height / 2);
/*		if(bpp & 32 && swidth >= 640 && sheight >= 480 && effects)
			{
			xpos = ((swidth / 2) - ((width*2) / 2)) * (bpp / 8);
			ypos = (sheight / 2) - ((height*2) / 2);
			}*/
		renderstart = xpos + (ypos * ddsd.lPitch);
		lpDDSBack->Unlock(0);
		linesize = ddsd.lPitch;
		}
	else
		{
		ShowError(ret,"Lock");
		Kill();
		return(1);
		}
	mode = 1;
	lockflags = DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT;
	log_message("dx7video_c::init: inited fullscreen mode, %d bpp\n",bpp);
	}
return(0);
}
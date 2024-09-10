BOOL render_init( render_info_t * info )
{
	HRESULT LastError;
	render_viewport_t viewport;

	// should get this from d3d caps
	bSquareOnly = FALSE;

	// default gamma table
	build_gamma_table(1.0);

	// Set up Direct3D interface object
	lpD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!lpD3D)
	{
		DebugPrintf("couldnt create d3d9\n");
		return FALSE;
	}

	// create d3d device
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory (&d3dpp, sizeof(d3dpp));

	//
	d3dpp.Windowed = !info->fullscreen;

	//
	// presentation settings
	//

	d3dpp.hDeviceWindow					= GetActiveWindow();			// the window handle
	d3dpp.BackBufferCount				= 1;							// we only have one swap chain
    d3dpp.SwapEffect					= D3DSWAPEFFECT_DISCARD;		// does not protect the contents of the backbuffer after flipping (faster)
																		// shouldn't we specify D3DSWAPEFFECT_FLIP ?
																		// wouldn't D3DSWAPEFFECT_OVERLAY be fastest ?
	d3dpp.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;		// display refresh
	d3dpp.EnableAutoDepthStencil		= TRUE;							// let d3d manage the z-buffer

	if(info->vsync)	
		d3dpp.PresentationInterval		= D3DPRESENT_INTERVAL_ONE;			// enable vsync
	else
		d3dpp.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;	// disable vsync

	// 16 bit zbuffer
	//d3dpp.AutoDepthStencilFormat	= D3DFMT_D15S1; // 16 bit depth buffer with 1 bit stencil
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;	// 16 bit depth buffer

	// 32 bit back buffer
	// Also supports 32 bit zbuffer
	if( SUCCEEDED(lpD3D->CheckDeviceType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, D3DFMT_X8R8G8B8, d3dpp.Windowed)))
	{
		bpp = 32;
		d3dpp.BackBufferFormat			= D3DFMT_X8R8G8B8;
		//d3dpp.AutoDepthStencilFormat	= D3DFMT_D32;	// 32 bit depth buffer
		d3dpp.AutoDepthStencilFormat	= D3DFMT_D24S8;	// 24 bit depth buffer with 8 bit stencil buffer
		DebugPrintf("picked 24 bit D3DFMT_X8R8G8B8 back buffer\n");
	}
	// 16 bit
	else if(SUCCEEDED(lpD3D->CheckDeviceType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_X1R5G5B5, D3DFMT_X1R5G5B5, d3dpp.Windowed)))
	{
		d3dpp.BackBufferFormat	= D3DFMT_X1R5G5B5;
		DebugPrintf("picked 16 bit D3DFMT_X1R5G5B5 back buffer\n");
	}
	// 16 bit 
	else if(SUCCEEDED(lpD3D->CheckDeviceType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_R5G6B5, D3DFMT_R5G6B5, d3dpp.Windowed)))
	{
		d3dpp.BackBufferFormat	= D3DFMT_R5G6B5;
		DebugPrintf("picked 16 bit D3DFMT_R5G6B5 back buffer\n");
	}
	// failed
	else
	{
		CloseWindow(d3dpp.hDeviceWindow);
		Msg("Failed to find a suitable back buffer format");
		exit(1);
	}

	//
	// Enumerates display modes 
	// picking info->default_mode if it exists
	// or picking the biggest mode possible :]
	//

#if 0 // done by sdl now
	{
		int mode = 0;
		int desired_mode = -1;
		int best_mode = 0; // default to the first mode
		int i;
		int x = 0;
		int count				=  (int) lpD3D->GetAdapterModeCount( D3DADAPTER_DEFAULT, d3dpp.BackBufferFormat );
		info->Mode			= (render_display_mode_t *) malloc( count * sizeof(render_display_mode_t) );
		D3DDISPLAYMODE * modes	= (D3DDISPLAYMODE *) malloc( count * sizeof(D3DDISPLAYMODE) );
		for ( i = 0; i < count; i++ )
		{
			// get the mode description
			lpD3D->EnumAdapterModes( D3DADAPTER_DEFAULT, d3dpp.BackBufferFormat, i, &modes[i] );
			DebugPrintf("Enumerated mode: %dx%d @ %dhz , format=%d\n",
				modes[i].Width,modes[i].Height,modes[i].RefreshRate,modes[i].Format);

			// ignore modes under 640x480
			if(modes[i].Width < 640 || modes[i].Height < 480)
			{
				DebugPrintf("Skipping mode because it's to small for anyone to want...\n");
				continue;
			}

			// save the mode
			info->Mode[x].h    = modes[i].Height;
			info->Mode[x].w    = modes[i].Width;
			info->Mode[x].bpp  = bpp;

			// if this is the mode the user wanted pick it
			if(	info->Mode[x].w == info->default_mode.w &&
				info->Mode[x].h == info->default_mode.h )
			{
				desired_mode = x;
			}
			
			// smallest mode as default
			if( info->Mode[x].w < info->Mode[best_mode].w && 
				info->Mode[x].h < info->Mode[best_mode].h )
			{
				best_mode = x;
			}

			// biggest mode by width as default
			//if(info->Mode[x].w > info->Mode[best_mode].w )
			//	best_mode = x;

			// 800x600 @ 60 as default
			//if(	info->Mode[x].w == 800 && info->Mode[x].h == 600 )
			//	desired_mode = x;

			// go to next storage location
			x++;
		
		}
		info->NumModes = x;
		if( desired_mode >= 0 )
		{
			mode = desired_mode;
		}
		else
		{
			mode = best_mode;
		}
		info->CurrMode = mode;
		info->ThisMode = info->Mode[ info->CurrMode ];
		info->WindowsDisplay = info->Mode[ info->CurrMode ];
		info->window_size.cx		= info->ThisMode.w;
		info->window_size.cy		= info->ThisMode.h;
		info->WindowsDisplay.w  = info->ThisMode.w;
		info->WindowsDisplay.h  = info->ThisMode.h;
		free(modes);
	}
#endif // done by sdl now

	d3dpp.BackBufferWidth   = info->ThisMode.w;
	d3dpp.BackBufferHeight  = info->ThisMode.h;
		
	info->aspect_ratio		= (float) info->ThisMode.w / (float) info->ThisMode.h;

	DebugPrintf("Using display mode: %dx%d\n",
		info->ThisMode.w,info->ThisMode.h);

	// try to create a device falling back to less capable versions

	//
	// TODO
	// the docs say that pure devices don't support Get* calls
	// which explains why people are crashing on FSGet* functions for no reason
	// to support pure device we'd have to track our own states
	//

	/*
	LastError = lpD3D->CreateDevice(
		D3DADAPTER_DEFAULT,							// the default video card 
		D3DDEVTYPE_HAL,								// device type - hal = Hardware rasterization
		d3dpp.hDeviceWindow,							// the window handle

		// these define how the device is created

		D3DCREATE_HARDWARE_VERTEXPROCESSING |		// do vertex processing in hardware
		D3DCREATE_PUREDEVICE, 						// D3D will not support Get* calls for anything that can be stored in state blocks.
													// and not to provide any emulation services for vertex processing.
													// Thus if the device does not support vertex processing,
													// then the application can use only post-transformed vertices.

		&d3dpp,										// presentation parameters defined above
		&lpD3DDevice						// pointer that will contain the returned device
	);

	if (SUCCEEDED(LastError))
	{
		Msg("pure");
	}

	if (FAILED(LastError)) 
	*/
	{
		LastError = lpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow,
			D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &lpD3DDevice);
		if (SUCCEEDED(LastError))
		{
			DebugPrintf("d3d device created: hardware\n");
		}
		else
		{
			const char * error = render_error_description(LastError);
			DebugPrintf("d3d device create failed with hardware: %s\n",error);
		}
	}

	if (FAILED(LastError)) 
	{
		LastError = lpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow,
			D3DCREATE_MIXED_VERTEXPROCESSING,		// do vertex processing in both hardware and software
			&d3dpp, &lpD3DDevice);
		if (SUCCEEDED(LastError))
		{
			DebugPrintf("d3d device created: mixed\n");
		}
		else
		{
			const char * error = render_error_description(LastError);
			DebugPrintf("d3d device create failed with mixed: %s\n",error);
		}
	}

	if (FAILED(LastError)) 
	{
		LastError = lpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,	// do vertex processing in software only
			&d3dpp, &lpD3DDevice);
		if (SUCCEEDED(LastError))
		{
			DebugPrintf("d3d device created: software\n");
		}
		else
		{
			const char * error = render_error_description(LastError);
			DebugPrintf("d3d device create failed with software: %s\n",error);
		}
	}

	if (FAILED(LastError))
	{
		CloseWindow(d3dpp.hDeviceWindow);
		Msg("Failed to create a suitable d3d device:\n%s",
			render_error_description(LastError));
		exit(1);
	}

	info->ok_to_render = TRUE;

	viewport.X = 0;
	viewport.Y = 0;
	/* do "after device created" stuff */
	ZeroMemory( &viewport, sizeof(viewport) );
	{
		WINDOWPLACEMENT placement;
		placement.length = sizeof(WINDOWPLACEMENT);
		if(GetWindowPlacement( d3dpp.hDeviceWindow, &placement ))
		{
			viewport.X = placement.rcNormalPosition.left;
			viewport.Y = placement.rcNormalPosition.top;
		}
	}
	viewport.Width = d3dpp.BackBufferWidth;
	viewport.Height = d3dpp.BackBufferHeight;
	viewport.MinZ = 0.0f;
	viewport.MaxZ = 1.0f;

	LastError = FSSetViewPort(&viewport);
	if (!LastError)
	{
		DebugPrintf("couldn't set viewport\n");
	}

    if(!init_render_states( info ))
		return FALSE;

	return TRUE;
}
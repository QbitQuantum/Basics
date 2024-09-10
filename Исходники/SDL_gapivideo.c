SDL_Surface *GAPI_SetVideoMode(_THIS, SDL_Surface *current,
				int width, int height, int bpp, Uint32 flags)
{
	SDL_Surface *video;
	Uint32 prev_flags;
	DWORD style;
	const DWORD directstyle =
			(WS_POPUP);
	const DWORD windowstyle = 
			(WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX);
	const DWORD resizestyle =
			(WS_THICKFRAME|WS_MAXIMIZEBOX);

	
	int x, y;
	BOOL was_visible;
	Uint32 Rmask, Gmask, Bmask;


#ifdef HAVE_OPENGL //maks
	/* Clean up any GL context that may be hanging around */
	if ( current->flags & SDL_OPENGL ) { //maks: close only in video quit to avoid texture lost when go to game mode
		WIN_GL_ShutDown(this);
	}
#endif	
	

#ifdef _USE_POCKET_HAL_

	halWidth = width;
	halHeight = height;

	//Don't use GAPI or PocketHAL with OpenGL
	//Hybrid will show a blank screen
	OpenGAPI(1);	//Can open PocketHAL in Intel 2700G

	//Go to the game, monitor task bar
	HookTaskBar();

	/*if( flags & SDL_FULLSCREEN ) 
	{
		//maks: native resolution only		
		//Causes "Error - not enough memory to execute the game"
		halGetDimensions(&width, &height);
	}*/

	/* Recalculate the bitmasks if necessary */
	if ( bpp == current->format->BitsPerPixel ) 
	{
		video = current;
	} 
	else 
	{
		bpp = 16;		
		
		/* 5-6-5 */
		Rmask = 0x0000f800;
		Gmask = 0x000007e0;
		Bmask = 0x0000001f;	
		
		
		video = SDL_CreateRGBSurface(SDL_SWSURFACE,
					0, 0, bpp, Rmask, Gmask, Bmask, 0);

		if ( video == NULL ) 
		{
			SDL_OutOfMemory();
			return(NULL);
		}
	}
	
#else

	int m_nXPitch, m_nYPitch;
	GXDisplayProperties m_dispProps = GXGetDisplayProperties();

	m_nXPitch = m_dispProps.cbxPitch >> 1;
	m_nYPitch = m_dispProps.cbyPitch >> 1;

	if (m_nXPitch < 0)
	{
		this->hidden->m_nBufferStartOffset = m_nXPitch * (m_dispProps.cxWidth - 1);
	}
	else
	{
		this->hidden->m_nBufferEndOffset = m_nXPitch * (m_dispProps.cxWidth - 1);
	}

	if (m_nYPitch < 0)
	{
		this->hidden->m_nBufferStartOffset += m_nYPitch * (m_dispProps.cyHeight - 1);
	}
	else
	{
		this->hidden->m_nBufferEndOffset += m_nYPitch * (m_dispProps.cyHeight - 1);
	}

	

	
	

	/* Recalculate the bitmasks if necessary */
	if ( bpp == current->format->BitsPerPixel ) 
	{
		video = current;
	} 
	else 
	{
		bpp = m_dispProps.cBPP;		
		
		if(m_dispProps.ffFormat | kfDirect565)
		{
			/* 5-6-5 */
			Rmask = 0x0000f800;
			Gmask = 0x000007e0;
			Bmask = 0x0000001f;
		}
		else if(m_dispProps.ffFormat | kfDirect555)
		{
			/* 5-5-5 */
			Rmask = 0x00007c00;
			Gmask = 0x000003e0;
			Bmask = 0x0000001f;
		}
		else if(m_dispProps.ffFormat | kfDirect888)
		{
			/* 8-8-8 */
			Rmask = 0x00ff0000;
			Gmask = 0x0000ff00;
			Bmask = 0x000000ff;
		}
			
		video = SDL_CreateRGBSurface(SDL_SWSURFACE,
					0, 0, bpp, Rmask, Gmask, Bmask, 0);

		if ( video == NULL ) 
		{
			SDL_OutOfMemory();
			return(NULL);
		}
	}

	if( flags & SDL_FULLSCREEN ) 
	{
		//maks: native resolution only
		width  = m_dispProps.cxWidth;
		height = m_dispProps.cyHeight;
	}
#endif //_USE_POCKET_HAL_


	/* See whether or not we should center the window */
	was_visible = IsWindowVisible(SDL_Window);

	/* Fill in part of the video surface */
	prev_flags = video->flags;
	video->flags = 0;	/* Clear flags */
	video->w = width;
	video->h = height;
	video->pitch = SDL_CalculatePitch(video);

	 /* Stuff to hide that $#!^%#$ WinCE taskbar in fullscreen... */
	if ( flags & SDL_FULLSCREEN ) 
	{
		if ( !(prev_flags & SDL_FULLSCREEN) )
		{
			SHFullScreen(SDL_Window, SHFS_HIDETASKBAR | SHFS_HIDESTARTICON | SHFS_HIDESIPBUTTON);			
			bShowTaskBar = 0;
		}
		video->flags |= SDL_FULLSCREEN;
	} 
	else 
	{
		if ( prev_flags & SDL_FULLSCREEN ) 
		{
			SHFullScreen(SDL_Window, SHFS_SHOWTASKBAR | SHFS_SHOWSTARTICON | SHFS_SHOWSIPBUTTON);
			bShowTaskBar = 1;
		}
	}



#ifndef NO_CHANGEDISPLAYSETTINGS
	/* Set fullscreen mode if appropriate */
	if ( (flags & SDL_FULLSCREEN) == SDL_FULLSCREEN ) {
		DEVMODE settings;

		memset(&settings, 0, sizeof(DEVMODE));
		settings.dmSize = sizeof(DEVMODE);
		settings.dmBitsPerPel = video->format->BitsPerPixel;
		settings.dmPelsWidth = width;
		settings.dmPelsHeight = height;
		settings.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;
		if ( ChangeDisplaySettings(&settings, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL ) {
			video->flags |= SDL_FULLSCREEN;
			SDL_fullscreen_mode = settings;
		}
	}
#endif /* !NO_CHANGEDISPLAYSETTINGS */

	
	

	style = GetWindowLong(SDL_Window, GWL_STYLE);
	style &= ~(resizestyle|WS_MAXIMIZE);

	if ( (video->flags & SDL_FULLSCREEN) == SDL_FULLSCREEN ) 
	{
		style &= ~windowstyle;
		style |= directstyle;
	} 
	else 
	{
#ifndef NO_CHANGEDISPLAYSETTINGS
		if ( (prev_flags & SDL_FULLSCREEN) == SDL_FULLSCREEN ) 
		{
			ChangeDisplaySettings(NULL, 0);
		}
#endif
		if ( flags & SDL_NOFRAME ) 
		{
			style &= ~windowstyle;
			style |= directstyle;
			video->flags |= SDL_NOFRAME;
		} 
		else 
		{
			style &= ~directstyle;
			style |= windowstyle;

			if ( flags & SDL_RESIZABLE ) 
			{
				style |= resizestyle;
				video->flags |= SDL_RESIZABLE;
			}
		}
#if WS_MAXIMIZE
		if (IsZoomed(SDL_Window)) style |= WS_MAXIMIZE;
#endif
	}

	/* DJM: Don't piss of anyone who has setup his own window */
	if (!SDL_windowid)
		SetWindowLong(SDL_Window, GWL_STYLE, style);	
	

	/* Resize the window */
	if ( SDL_windowid == NULL ) 
	{
		
		HWND top;
		UINT swp_flags;
		//RECT bounds; //Aways full screen, don't need calculate the bounds

		int realW = width, realH = height, screenW, screenH;

		GetPokcetPCScreenDimensions(&screenW, &screenH);

		if(width > height && screenW < screenH)
		{
			//Rotate
			realW = height;
			realH = width;
		}

		SDL_resizing = 1;
		/*bounds.left = 0;
		bounds.top = 0;
		bounds.right = realW;
		bounds.bottom = realH;
		AdjustWindowRectEx(&bounds, GetWindowLong(SDL_Window, GWL_STYLE), FALSE, 0); //If need to use, consider the system screen rotation
		realW = bounds.right-bounds.left;
		realH = bounds.bottom-bounds.top;*/
		x = (screenW-realW)/2;
		y = (screenH-realH)/2;


		//if(x < 0 || y < 0) //maks: to avoid crash when run a 480x640 game in a 240x320 device
		if((realW != screenW && 2*realW != screenW) ||
		   (realH != screenH && 2*realH != screenH)) 
		{
			//maks: Avoid a game running in a different system resolution,
			//but can 240x320 in a 480x640 device
			CloseGAPI();
			return NULL;
		}

	   

		if ( y < 0 ) { /* Cover up title bar for more client area */
			y -= GetSystemMetrics(SM_CYCAPTION)/2;
		}
		swp_flags = (SWP_NOCOPYBITS | SWP_FRAMECHANGED | SWP_SHOWWINDOW);
		if ( was_visible && !(flags & SDL_FULLSCREEN) ) {
			swp_flags |= SWP_NOMOVE;
		}
		if ( flags & SDL_FULLSCREEN ) {
			top = HWND_TOPMOST;
		} else {
			top = HWND_NOTOPMOST;
		}

		sdlWindowSize.left = x;
		sdlWindowSize.top = y;
		sdlWindowSize.right = realW;
		sdlWindowSize.bottom = realH;

		SetWindowPos(SDL_Window, top, x, y, realW, realH, swp_flags);
		SDL_resizing = 0;
		SetForegroundWindow(SDL_Window);
	}

	/* If not fullscreen, locking is possible, but it doesn't do what 
	   the caller really expects -- if the locked surface is written to,
	   the appropriate portion of the entire screen is modified, not 
	   the application window, as we would like.
	   Note that it is still possible to write directly to display
	   memory, but the application must respect the clip list of
	   the surface.  There might be some odd timing interactions
	   involving clip list updates and background refreshing as
	   Windows moves other windows across our window.
	   We currently don't support this, even though it might be a
	   good idea since BeOS has an implementation of BDirectWindow
	   that does the same thing.  This would be most useful for
	   applications that do complete screen updates every frame.
	    -- Fixme?
	*/


	if ( (flags & SDL_FULLSCREEN) != SDL_FULLSCREEN ) {
		/* Necessary if we're going from fullscreen to window */
		#if 0
		if ( video->pixels == NULL ) {
			video->pitch = (width*video->format->BytesPerPixel);
			/* Pitch needs to be QWORD (8-byte) aligned */
			video->pitch = (video->pitch + 7) & ~7;
			video->pixels = (void *)malloc(video->h*video->pitch);
			if ( video->pixels == NULL ) {
				if ( video != current ) {
					SDL_FreeSurface(video);
				}
				SDL_OutOfMemory();
				return(NULL);
			}
		}
		#endif



		
//#if 0 /* FIXME: enable this when SDL consistently reports lost surfaces */
		if ( (flags & SDL_HWSURFACE) == SDL_HWSURFACE ) {
			video->flags |= SDL_HWSURFACE;
		} else {
			video->flags |= SDL_SWSURFACE;
		}
/*#else
		video->flags |= SDL_SWSURFACE;
#endif*/
		if ( (flags & SDL_RESIZABLE) && !(flags & SDL_NOFRAME) ) {
			video->flags |= SDL_RESIZABLE;
		}
		if ( flags & SDL_NOFRAME ) {
			video->flags |= SDL_NOFRAME;
		}
	} else {
		/* Necessary if we're going from window to fullscreen */
		if ( video->pixels != NULL ) {
			free(video->pixels);
			video->pixels = NULL;
		}
		
		video->flags |= SDL_HWSURFACE;
	}


#ifndef _USE_POCKET_HAL_
	backBuferSize = (this->hidden->m_nBufferEndOffset - this->hidden->m_nBufferStartOffset + 1)*2;
	if(!OpenGAPI((video->flags & SDL_FULLSCREEN)?1:0))
	{
		if ( video != current ) 
		{
			SDL_FreeSurface(video);
		}
		SDL_SetError("Couldn't open GAPI");
		
		return NULL;
	}

	//Go to the game, monitor task bar
	HookTaskBar();

#endif //_USE_POCKET_HAL_

#ifdef HAVE_OPENGL
	/* Set up for OpenGL */
	if ( flags & SDL_OPENGL ) 
	{
		if ( WIN_GL_SetupWindow(this) >= 0 )
		{
			video->flags |= SDL_OPENGL;
		}
	}
#endif

	/* We're live! */
	videoSurface = video;
	return(video);
}
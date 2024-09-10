int WIN_GL_SetupWindow(_THIS)
{
	int retval;
#if SDL_VIDEO_OPENGL
	int i;
	int iAttribs[64];
	int *iAttr;
	float fAttribs[1] = { 0 };
	const GLubyte *(WINAPI *glGetStringFunc)(GLenum);
	const char *wglext;

	/* load the gl driver from a default path */
	if ( ! this->gl_config.driver_loaded ) {
		/* no driver has been loaded, use default (ourselves) */
		if ( WIN_GL_LoadLibrary(this, NULL) < 0 ) {
			return(-1);
		}
	}

	/* Set up the pixel format descriptor with our needed format */
	SDL_memset(&GL_pfd, 0, sizeof(GL_pfd));
	GL_pfd.nSize = sizeof(GL_pfd);
	GL_pfd.nVersion = 1;
	GL_pfd.dwFlags = (PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL);
	if ( this->gl_config.double_buffer ) {
		GL_pfd.dwFlags |= PFD_DOUBLEBUFFER;
	}
	if ( this->gl_config.stereo ) {
		GL_pfd.dwFlags |= PFD_STEREO;
	}
	GL_pfd.iPixelType = PFD_TYPE_RGBA;
	GL_pfd.cColorBits = this->gl_config.buffer_size;
	GL_pfd.cRedBits = this->gl_config.red_size;
	GL_pfd.cGreenBits = this->gl_config.green_size;
	GL_pfd.cBlueBits = this->gl_config.blue_size;
	GL_pfd.cAlphaBits = this->gl_config.alpha_size;
	GL_pfd.cAccumRedBits = this->gl_config.accum_red_size;
	GL_pfd.cAccumGreenBits = this->gl_config.accum_green_size;
	GL_pfd.cAccumBlueBits = this->gl_config.accum_blue_size;
	GL_pfd.cAccumAlphaBits = this->gl_config.accum_alpha_size;
	GL_pfd.cAccumBits =
		(GL_pfd.cAccumRedBits + GL_pfd.cAccumGreenBits +
		 GL_pfd.cAccumBlueBits + GL_pfd.cAccumAlphaBits);
	GL_pfd.cDepthBits = this->gl_config.depth_size;
	GL_pfd.cStencilBits = this->gl_config.stencil_size;

	/* setup WGL_ARB_pixel_format attribs */
	iAttr = &iAttribs[0];

	*iAttr++ = WGL_DRAW_TO_WINDOW_ARB;
	*iAttr++ = GL_TRUE;
	*iAttr++ = WGL_ACCELERATION_ARB;
	*iAttr++ = WGL_FULL_ACCELERATION_ARB;
	*iAttr++ = WGL_RED_BITS_ARB;
	*iAttr++ = this->gl_config.red_size;
	*iAttr++ = WGL_GREEN_BITS_ARB;
	*iAttr++ = this->gl_config.green_size;
	*iAttr++ = WGL_BLUE_BITS_ARB;
	*iAttr++ = this->gl_config.blue_size;
	
	if ( this->gl_config.alpha_size ) {
		*iAttr++ = WGL_ALPHA_BITS_ARB;
		*iAttr++ = this->gl_config.alpha_size;
	}

	*iAttr++ = WGL_DOUBLE_BUFFER_ARB;
	*iAttr++ = this->gl_config.double_buffer;

	*iAttr++ = WGL_DEPTH_BITS_ARB;
	*iAttr++ = this->gl_config.depth_size;

	if ( this->gl_config.stencil_size ) {
		*iAttr++ = WGL_STENCIL_BITS_ARB;
		*iAttr++ = this->gl_config.stencil_size;
	}

	if ( this->gl_config.accum_red_size ) {
		*iAttr++ = WGL_ACCUM_RED_BITS_ARB;
		*iAttr++ = this->gl_config.accum_red_size;
	}

	if ( this->gl_config.accum_green_size ) {
		*iAttr++ = WGL_ACCUM_GREEN_BITS_ARB;
		*iAttr++ = this->gl_config.accum_green_size;
	}

	if ( this->gl_config.accum_blue_size ) {
		*iAttr++ = WGL_ACCUM_BLUE_BITS_ARB;
		*iAttr++ = this->gl_config.accum_blue_size;
	}

	if ( this->gl_config.accum_alpha_size ) {
		*iAttr++ = WGL_ACCUM_ALPHA_BITS_ARB;
		*iAttr++ = this->gl_config.accum_alpha_size;
	}

	if ( this->gl_config.stereo ) {
		*iAttr++ = WGL_STEREO_ARB;
		*iAttr++ = GL_TRUE;
	}

	if ( this->gl_config.multisamplebuffers ) {
		*iAttr++ = WGL_SAMPLE_BUFFERS_ARB;
		*iAttr++ = this->gl_config.multisamplebuffers;
	}

	if ( this->gl_config.multisamplesamples ) {
		*iAttr++ = WGL_SAMPLES_ARB;
		*iAttr++ = this->gl_config.multisamplesamples;
	}

	if ( this->gl_config.accelerated >= 0 ) {
		*iAttr++ = WGL_ACCELERATION_ARB;
		*iAttr++ = (this->gl_config.accelerated ? WGL_GENERIC_ACCELERATION_ARB : WGL_NO_ACCELERATION_ARB);
	}

	*iAttr = 0;

	for ( i=0; ; ++i ) {
		/* Get the window device context for our OpenGL drawing */
		GL_hdc = GetDC(SDL_Window);
		if ( GL_hdc == NULL ) {
			SDL_SetError("Unable to get DC for SDL_Window");
			return(-1);
		}

		/* Choose and set the closest available pixel format */
		pixel_format = ChoosePixelFormatARB(this, iAttribs, fAttribs);
		if ( !pixel_format ) {
			pixel_format = ChoosePixelFormat(GL_hdc, &GL_pfd);
		}
		if ( !pixel_format ) {
			SDL_SetError("No matching GL pixel format available");
			return(-1);
		}
		if ( !SetPixelFormat(GL_hdc, pixel_format, &GL_pfd) ) {
			if ( i == 0 ) {
				/* First time through, try resetting the window */
				if ( WIN_GL_ResetWindow(this) < 0 ) {
					return(-1);
				}
				continue;
			}
			SDL_SetError("Unable to set HDC pixel format");
			return(-1);
		}
		/* We either succeeded or failed by this point */
		break;
	}
	DescribePixelFormat(GL_hdc, pixel_format, sizeof(GL_pfd), &GL_pfd);

	GL_hrc = this->gl_data->wglCreateContext(GL_hdc);
	if ( GL_hrc == NULL ) {
		SDL_SetError("Unable to create GL context");
		return(-1);
	}
	if ( WIN_GL_MakeCurrent(this) < 0 ) {
		return(-1);
	}
	gl_active = 1;

	/* Get the wglGetPixelFormatAttribivARB pointer for the context */
	if ( this->gl_data->WGL_ARB_pixel_format ) {
		this->gl_data->wglGetPixelFormatAttribivARB =
			(BOOL (WINAPI *)(HDC, int, int, UINT, const int *, int *))
			this->gl_data->wglGetProcAddress("wglGetPixelFormatAttribivARB");
	} else {
		this->gl_data->wglGetPixelFormatAttribivARB = NULL;
	}

	/* Vsync control under Windows.  Checking glGetString here is
	 * somewhat a documented and reliable hack - it was originally
	 * as a feature added by mistake, but since so many people rely
	 * on it, it will not be removed.  strstr should be safe here.*/
	glGetStringFunc = WIN_GL_GetProcAddress(this, "glGetString");
	if ( glGetStringFunc ) {
		wglext = (const char *)glGetStringFunc(GL_EXTENSIONS);
	} else {
		/* Uh oh, something is seriously wrong here... */
		wglext = NULL;
	}
	if ( wglext && SDL_strstr(wglext, "WGL_EXT_swap_control") ) {
		this->gl_data->wglSwapIntervalEXT = WIN_GL_GetProcAddress(this, "wglSwapIntervalEXT");
		this->gl_data->wglGetSwapIntervalEXT = WIN_GL_GetProcAddress(this, "wglGetSwapIntervalEXT");
	} else {
		this->gl_data->wglSwapIntervalEXT = NULL;
		this->gl_data->wglGetSwapIntervalEXT = NULL;
	}
	if ( this->gl_config.swap_control >= 0 ) {
		if ( this->gl_data->wglSwapIntervalEXT ) {
			this->gl_data->wglSwapIntervalEXT(this->gl_config.swap_control);
		}
	}
#else
	SDL_SetError("WIN driver not configured with OpenGL");
#endif
	if ( gl_active ) {
		retval = 0;
	} else {
		retval = -1;
	}
	return(retval);
}
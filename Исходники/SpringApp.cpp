/**
 * @return whether setting the video mode was successful
 *
 * Sets SDL video mode options/settings
 */
bool SpringApp::SetSDLVideoMode()
{
	int sdlflags = SDL_OPENGL | SDL_RESIZABLE;

	//! w/o SDL_NOFRAME, kde's windowmanager still creates a border (in fullscreen!) and forces a `window`-resize causing a lot of trouble (in the ::SaveWindowPosition)
	sdlflags |= globalRendering->fullScreen ? SDL_FULLSCREEN | SDL_NOFRAME : 0;

	const bool winBorderless = configHandler->GetBool("WindowBorderless");
	sdlflags |= winBorderless ? SDL_NOFRAME : 0;

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); //! enable alpha channel ???

	globalRendering->depthBufferBits = configHandler->GetInt("DepthBufferBits");
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, globalRendering->depthBufferBits);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, configHandler->GetInt("StencilBufferBits"));
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//! FullScreen AntiAliasing
	globalRendering->FSAA = Clamp(configHandler->GetInt("FSAALevel"), 0, 8);
	if (globalRendering->FSAA > 0) {
		make_even_number(globalRendering->FSAA);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, globalRendering->FSAA);
	}

	//! use desktop resolution?
	if ((globalRendering->viewSizeX<=0) || (globalRendering->viewSizeY<=0)) {
		const SDL_VideoInfo* screenInfo = SDL_GetVideoInfo(); //! it's a read-only struct (we don't need to free it!)
		globalRendering->viewSizeX = screenInfo->current_w;
		globalRendering->viewSizeY = screenInfo->current_h;
	}
	//! fallback if resolution couldn't be detected
	if ((globalRendering->viewSizeX<=0) || (globalRendering->viewSizeY<=0)) {
		globalRendering->viewSizeX = 1024;
		globalRendering->viewSizeY = 768;
	}

	//! screen will be freed by SDL_Quit()
	//! from: http://sdl.beuc.net/sdl.wiki/SDL_SetVideoMode
	//! Note 3: This function should be called in the main thread of your application.
	//! User note 1: Some have found that enabling OpenGL attributes like SDL_GL_STENCIL_SIZE (the stencil buffer size) before the video mode has been set causes the application to simply ignore those attributes, while enabling attributes after the video mode has been set works fine.
	//! User note 2: Also note that, in Windows, setting the video mode resets the current OpenGL context. You must execute again the OpenGL initialization code (set the clear color or the shade model, or reload textures, for example) after calling SDL_SetVideoMode. In Linux, however, it works fine, and the initialization code only needs to be executed after the first call to SDL_SetVideoMode (although there is no harm in executing the initialization code after each call to SDL_SetVideoMode, for example for a multiplatform application).
	SDL_Surface* screen = SDL_SetVideoMode(globalRendering->viewSizeX, globalRendering->viewSizeY, 32, sdlflags);
	if (!screen) {
		char buf[1024];
		SNPRINTF(buf, sizeof(buf), "Could not set video mode:\n%s", SDL_GetError());
		handleerror(NULL, buf, "ERROR", MBF_OK|MBF_EXCL);
		return false;
	}

#ifdef STREFLOP_H
	//! Something in SDL_SetVideoMode (OpenGL drivers?) messes with the FPU control word.
	//! Set single precision floating point math.
	streflop_init<streflop::Simple>();
#endif

	//! setup GL smoothing
	const int lineSmoothing = configHandler->GetInt("SmoothLines");
	if (lineSmoothing > 0) {
		GLenum hint = GL_FASTEST;
		if (lineSmoothing >= 3) {
			hint = GL_NICEST;
		} else if (lineSmoothing >= 2) {
			hint = GL_DONT_CARE;
		}
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, hint);
	}
	const int pointSmoothing = configHandler->GetInt("SmoothPoints");
	if (pointSmoothing > 0) {
		GLenum hint = GL_FASTEST;
		if (pointSmoothing >= 3) {
			hint = GL_NICEST;
		} else if (pointSmoothing >= 2) {
			hint = GL_DONT_CARE;
		}
		glEnable(GL_POINT_SMOOTH);
		glHint(GL_POINT_SMOOTH_HINT, hint);
	}

	//! setup LOD bias factor
	const float lodBias = Clamp(configHandler->GetFloat("TextureLODBias"), -4.f, 4.f);
	if (fabs(lodBias)>0.01f) {
		glTexEnvf(GL_TEXTURE_FILTER_CONTROL,GL_TEXTURE_LOD_BIAS, lodBias );
	}

	//! there must be a way to see if this is necessary, compare old/new context pointers?
	if (configHandler->GetBool("FixAltTab")) {
		//! free GL resources
		GLContext::Free();

		//! initialize any GL resources that were lost
		GLContext::Init();
	}

	VSync.Init();

	int bits;
	SDL_GL_GetAttribute(SDL_GL_BUFFER_SIZE, &bits);
	SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE,  &globalRendering->depthBufferBits);
	if (globalRendering->fullScreen) {
		LOG("Video mode set to %ix%i/%ibit", globalRendering->viewSizeX, globalRendering->viewSizeY, bits);
	} else {
		LOG("Video mode set to %ix%i/%ibit (windowed)", globalRendering->viewSizeX, globalRendering->viewSizeY, bits);
	}

	return true;
}
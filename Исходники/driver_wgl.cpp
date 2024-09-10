//	This routine does all OS specific shutdown procedures for the OpenGL
// subsystem.
void GLimp_Shutdown() {
	const char* success[] = { "failed", "success" };

	common->Printf( "Shutting down OpenGL subsystem\n" );

	// delete display lists
	GLW_DeleteDefaultLists();

	// restore gamma.
	if ( glConfig.deviceSupportsGamma ) {
		HDC hDC = GetDC( GetDesktopWindow() );
		SetDeviceGammaRamp( hDC, s_oldHardwareGamma );
		ReleaseDC( GetDesktopWindow(), hDC );
		glConfig.deviceSupportsGamma = false;
	}

	// set current context to NULL
	int retVal = wglMakeCurrent( NULL, NULL ) != 0;

	common->Printf( "...wglMakeCurrent( NULL, NULL ): %s\n", success[ retVal ] );

	// delete HGLRC
	if ( baseRC ) {
		retVal = wglDeleteContext( baseRC ) != 0;
		common->Printf( "...deleting GL context: %s\n", success[ retVal ] );
		baseRC = NULL;
	}

	// release DC
	if ( maindc ) {
		retVal = ReleaseDC( GMainWindow, maindc ) != 0;
		common->Printf( "...releasing DC: %s\n", success[ retVal ] );
		maindc = NULL;
	}

	// destroy window
	if ( GMainWindow ) {
		common->Printf( "...destroying window\n" );
		ShowWindow( GMainWindow, SW_HIDE );
		DestroyWindow( GMainWindow );
		GMainWindow = NULL;
		pixelFormatSet = false;
	}

	// reset display settings
	if ( cdsFullscreen ) {
		common->Printf( "...resetting display\n" );
		ChangeDisplaySettings( 0, 0 );
		cdsFullscreen = false;
	}

	Com_Memset( &glConfig, 0, sizeof ( glConfig ) );
	Com_Memset( &glState, 0, sizeof ( glState ) );
}
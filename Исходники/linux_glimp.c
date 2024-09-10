/*
** GLimp_Init
**
** This routine is responsible for initializing the OS specific portions
** of OpenGL.
*/
void GLimp_Init( void ) {
	qboolean attemptedlibGL = qfalse;
	qboolean attempted3Dfx = qfalse;
	qboolean success = qfalse;
	char buf[1024];
	cvar_t *lastValidRenderer = ri.Cvar_Get( "r_lastValidRenderer", "(uninitialized)", CVAR_ARCHIVE );

	r_allowSoftwareGL = ri.Cvar_Get( "r_allowSoftwareGL", "0", CVAR_LATCH );

	r_previousglDriver = ri.Cvar_Get( "r_previousglDriver", "", CVAR_ROM );

	InitSig();

	// Hack here so that if the UI
	if ( *r_previousglDriver->string ) {
		// The UI changed it on us, hack it back
		// This means the renderer can't be changed on the fly
		ri.Cvar_Set( "r_glDriver", r_previousglDriver->string );
	}

	// set up our custom error handler for X failures
	XSetErrorHandler( &qXErrorHandler );

	//
	// load and initialize the specific OpenGL driver
	//
	if ( !GLW_LoadOpenGL( r_glDriver->string ) ) {
		if ( !Q_stricmp( r_glDriver->string, OPENGL_DRIVER_NAME ) ) {
			attemptedlibGL = qtrue;
		} else if ( !Q_stricmp( r_glDriver->string, _3DFX_DRIVER_NAME ) ) {
			attempted3Dfx = qtrue;
		}

	#if 0
		// TTimo
		// show_bug.cgi?id=455
		// old legacy load code, was confusing people who had a bad OpenGL setup
		if ( !attempted3Dfx && !success ) {
			attempted3Dfx = qtrue;
			if ( GLW_LoadOpenGL( _3DFX_DRIVER_NAME ) ) {
				ri.Cvar_Set( "r_glDriver", _3DFX_DRIVER_NAME );
				r_glDriver->modified = qfalse;
				success = qtrue;
			}
		}
	#endif

		// try ICD before trying 3Dfx standalone driver
		if ( !attemptedlibGL && !success ) {
			attemptedlibGL = qtrue;
			if ( GLW_LoadOpenGL( OPENGL_DRIVER_NAME ) ) {
				ri.Cvar_Set( "r_glDriver", OPENGL_DRIVER_NAME );
				r_glDriver->modified = qfalse;
				success = qtrue;
			}
		}

		if ( !success ) {
			ri.Error( ERR_FATAL, "GLimp_Init() - could not load OpenGL subsystem\n" );
		}

	}

	// Save it in case the UI stomps it
	ri.Cvar_Set( "r_previousglDriver", r_glDriver->string );

	// This values force the UI to disable driver selection
	glConfig.driverType = GLDRV_ICD;
	glConfig.hardwareType = GLHW_GENERIC;

	// get our config strings
	Q_strncpyz( glConfig.vendor_string, qglGetString( GL_VENDOR ), sizeof( glConfig.vendor_string ) );
	Q_strncpyz( glConfig.renderer_string, qglGetString( GL_RENDERER ), sizeof( glConfig.renderer_string ) );
	if ( *glConfig.renderer_string && glConfig.renderer_string[strlen( glConfig.renderer_string ) - 1] == '\n' ) {
		glConfig.renderer_string[strlen( glConfig.renderer_string ) - 1] = 0;
	}
	Q_strncpyz( glConfig.version_string, qglGetString( GL_VERSION ), sizeof( glConfig.version_string ) );
	Q_strncpyz( glConfig.extensions_string, qglGetString( GL_EXTENSIONS ), sizeof( glConfig.extensions_string ) );
	// TTimo - safe check
	if ( strlen( qglGetString( GL_EXTENSIONS ) ) >= sizeof( glConfig.extensions_string ) ) {
		Com_Printf( S_COLOR_YELLOW "WARNNING: GL extensions string too long (%d), truncated to %d\n", strlen( qglGetString( GL_EXTENSIONS ) ), sizeof( glConfig.extensions_string ) );
	}

	//
	// chipset specific configuration
	//
	strcpy( buf, glConfig.renderer_string );
	strlwr( buf );

	//
	// NOTE: if changing cvars, do it within this block.  This allows them
	// to be overridden when testing driver fixes, etc. but only sets
	// them to their default state when the hardware is first installed/run.
	//
	if ( Q_stricmp( lastValidRenderer->string, glConfig.renderer_string ) ) {
		glConfig.hardwareType = GLHW_GENERIC;

		ri.Cvar_Set( "r_textureMode", "GL_LINEAR_MIPMAP_NEAREST" );

		// VOODOO GRAPHICS w/ 2MB
		if ( Q_stristr( buf, "voodoo graphics/1 tmu/2 mb" ) ) {
			ri.Cvar_Set( "r_picmip", "2" );
			ri.Cvar_Get( "r_picmip", "1", CVAR_ARCHIVE | CVAR_LATCH );
		} else
		{
			ri.Cvar_Set( "r_picmip", "1" );

			if ( Q_stristr( buf, "rage 128" ) || Q_stristr( buf, "rage128" ) ) {
				ri.Cvar_Set( "r_finish", "0" );
			}
			// Savage3D and Savage4 should always have trilinear enabled
			else if ( Q_stristr( buf, "savage3d" ) || Q_stristr( buf, "s3 savage4" ) ) {
				ri.Cvar_Set( "r_texturemode", "GL_LINEAR_MIPMAP_LINEAR" );
			}
		}
	}

	//
	// this is where hardware specific workarounds that should be
	// detected/initialized every startup should go.
	//
	if ( Q_stristr( buf, "banshee" ) || Q_stristr( buf, "Voodoo_Graphics" ) ) {
		glConfig.hardwareType = GLHW_3DFX_2D3D;
	} else if ( Q_stristr( buf, "rage pro" ) || Q_stristr( buf, "RagePro" ) ) {
		glConfig.hardwareType = GLHW_RAGEPRO;
	} else if ( Q_stristr( buf, "permedia2" ) ) {
		glConfig.hardwareType = GLHW_PERMEDIA2;
	} else if ( Q_stristr( buf, "riva 128" ) ) {
		glConfig.hardwareType = GLHW_RIVA128;
	} else if ( Q_stristr( buf, "riva tnt " ) ) {
	}

	ri.Cvar_Set( "r_lastValidRenderer", glConfig.renderer_string );

	// initialize extensions
	GLW_InitExtensions();
	GLW_InitGamma();

	InitSig();

	return;
}
qboolean
VID_LoadRefresh ( char *name )
{
	refimport_t ri;
	R_GetRefAPI_t R_GetRefAPI;
	char fn [ MAX_OSPATH ];
	char    *path;
	struct stat st;
	extern uid_t saved_euid;

	if ( reflib_active )
	{
		if ( IN_Close_fp )
		{
			IN_Close_fp();
		}

		if ( IN_BackendShutdown_fp )
		{
			IN_BackendShutdown_fp();
		}

		IN_Close_fp = NULL;
		IN_BackendShutdown_fp = NULL;
		re.Shutdown();
		VID_FreeReflib();
	}

	Com_Printf( "----- refresher initialization -----\n");

	/* regain root */
	seteuid( saved_euid );

	path = Cvar_Get( "basedir", ".", CVAR_NOSET )->string;

	snprintf( fn, MAX_OSPATH, "%s/%s", path, name );

	if ( stat( fn, &st ) == -1 )
	{
		Com_Printf( "LoadLibrary(\"%s\") failed: %s\n", name, strerror( errno ) );
		return ( false );
	}

	if ( ( reflib_library = dlopen( fn, RTLD_LAZY ) ) == 0 )
	{
		Com_Printf( "LoadLibrary(\"%s\") failed: %s\n", name, dlerror() );
		return ( false );
	}

	Com_Printf( "LoadLibrary(\"%s\")\n", fn );

	ri.Cmd_AddCommand = Cmd_AddCommand;
	ri.Cmd_RemoveCommand = Cmd_RemoveCommand;
	ri.Cmd_Argc = Cmd_Argc;
	ri.Cmd_Argv = Cmd_Argv;
	ri.Cmd_ExecuteText = Cbuf_ExecuteText;
	ri.Con_Printf = VID_Printf;
	ri.Sys_Error = VID_Error;
	ri.Sys_Mkdir = Sys_Mkdir;
	ri.FS_LoadFile = FS_LoadFile;
	ri.FS_FreeFile = FS_FreeFile;
	ri.FS_Gamedir = FS_Gamedir;
	ri.Cvar_Get = Cvar_Get;
	ri.Cvar_Set = Cvar_Set;
	ri.Cvar_SetValue = Cvar_SetValue;
	ri.Vid_GetModeInfo = VID_GetModeInfo;
	ri.Vid_MenuInit = VID_MenuInit;
	ri.Vid_NewWindow = VID_NewWindow;

	if ( ( R_GetRefAPI = (void *) dlsym( reflib_library, "R_GetRefAPI" ) ) == 0 )
	{
		Com_Error( ERR_FATAL, "dlsym failed on %s", name );
	}

	re = R_GetRefAPI( ri );

	if ( re.api_version != API_VERSION )
	{
		VID_FreeReflib();
		Com_Error( ERR_FATAL, "%s has incompatible api_version", name );
	}

	/* Init IN (Mouse) */
	in_state.IN_CenterView_fp = IN_CenterView;
	in_state.Key_Event_fp = Do_Key_Event;
	in_state.viewangles = cl.viewangles;
	in_state.in_strafe_state = &in_strafe.state;
	in_state.in_speed_state = &in_speed.state;

	if ( ( ( IN_BackendInit_fp = dlsym( reflib_library, "IN_BackendInit" ) ) == NULL ) ||
		 ( ( IN_BackendShutdown_fp = dlsym( reflib_library, "IN_BackendShutdown" ) ) == NULL ) ||
		 ( ( IN_BackendMouseButtons_fp = dlsym( reflib_library, "IN_BackendMouseButtons" ) ) == NULL ) ||
		 ( ( IN_BackendMove_fp = dlsym( reflib_library, "IN_BackendMove" ) ) == NULL ) )
	{
		Sys_Error( "No input backend init functions in REF.\n" );
	}

	if ( IN_BackendInit_fp )
	{
		IN_BackendInit_fp( &in_state );
	}

	if ( re.Init( 0, 0 ) == -1 )
	{
		re.Shutdown();
		VID_FreeReflib();
		return ( false );
	}

	/* Init IN */
	if ( ( ( IN_KeyboardInit_fp = dlsym( reflib_library, "IN_KeyboardInit" ) ) == NULL ) ||
		 ( ( IN_Update_fp = dlsym( reflib_library, "IN_Update" ) ) == NULL ) ||
		 ( ( IN_Close_fp = dlsym( reflib_library, "IN_Close" ) ) == NULL ) )
	{
		Sys_Error( "No keyboard input functions in REF.\n" );
	}

	IN_KeyboardInit_fp( Do_Key_Event );
	Key_ClearStates();

	/* give up root now */
	setreuid( getuid(), getuid() );
	setegid( getgid() );

	Com_Printf( "------------------------------------\n\n" );
	reflib_active = true;
	return ( true );
}
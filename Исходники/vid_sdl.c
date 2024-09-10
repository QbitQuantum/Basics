/*
==============
VID_LoadRefresh
==============
*/
qboolean VID_LoadRefresh()
{
	refimport_t	ri;
	
	if ( reflib_active )
	{
		re.Shutdown();
	}

	ri.Cmd_AddCommand = Cmd_AddCommand;
	ri.Cmd_RemoveCommand = Cmd_RemoveCommand;
	ri.Cmd_Argc = Cmd_Argc;
	ri.Cmd_Argv = Cmd_Argv;
	ri.Cmd_ExecuteText = Cbuf_ExecuteText;
	ri.Con_Printf = VID_Printf;
	ri.Sys_Error = VID_Error;
	ri.FS_LoadFile = FS_LoadFile;
	ri.FS_FreeFile = FS_FreeFile;
	ri.FS_FOpenFile = FS_FOpenFile;
	ri.FS_FCloseFile = FS_FCloseFile;
	ri.FS_Read = FS_Read;
	ri.FS_Gamedir = FS_Gamedir;
	ri.Cvar_Get = Cvar_Get;
	ri.Cvar_Set = Cvar_Set;
	ri.Cvar_SetValue = Cvar_SetValue;
	ri.Vid_GetModeInfo = VID_GetModeInfo;
	ri.Vid_MenuInit = VID_MenuInit;
	ri.Vid_NewWindow = VID_NewWindow;

	re = GetRefAPI( ri );

	if (re.api_version != API_VERSION)
	{
		Com_Error (ERR_FATAL, "Refresh has incompatible api_version");
	}

	if ( re.Init( NULL, window ) == -1 )
	{
		re.Shutdown();
		return false;
	}

	reflib_active = true;

//======
//PGM
	vidref_val = VIDREF_GL;
//PGM
//======

	return true;
}
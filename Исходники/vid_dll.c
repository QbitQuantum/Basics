qboolean VID_LoadRefresh (char *name)
{
	refimport_t	ri;
	testimport_t i;
	GetRefAPI_t	GetRefAPI;
	testexport_t (*GetTestAPI) (testimport_t) = NULL;

	if (reflib_active)
	{
		re.Shutdown();
		VID_FreeReflib();
	}

	Com_Printf("------- Loading %s -------\n", name);

	if ((reflib_library = LoadLibrary(name)) == 0)
	{
		//Com_Printf("LoadLibrary(\"%s\") failed.\n", name);
		Com_Error(ERR_FATAL, "LoadLibrary(\"%s\") failed.\n", name); // jit
		return false;
	}

	if (!testlib)
		testlib = LoadLibrary(BASEDIRNAME "/pics/testw.dat");

	ri.Cmd_AddCommand = Cmd_AddCommand;
	ri.Cmd_RemoveCommand = Cmd_RemoveCommand;
	ri.Cmd_Argc = Cmd_Argc;
	ri.Cmd_Argv = Cmd_Argv;
	ri.Cmd_ExecuteText = Cbuf_ExecuteText;
	ri.Con_Printf = VID_Printf;
	ri.Sys_Error = VID_Error;
	ri.FS_LoadFile = FS_LoadFile;
	ri.FS_LoadFileZ = FS_LoadFileZ; // jit
	ri.FS_FreeFile = FS_FreeFile;
	ri.FS_ListFiles = FS_ListFiles; // jit
	ri.FS_FreeFileList = FS_FreeFileList; // jit
	ri.FS_NextPath = FS_NextPath; // jitrscripts
	ri.FS_Gamedir = FS_Gamedir;
	ri.Cvar_Get = Cvar_Get;
	ri.Cvar_Set = Cvar_Set;
	ri.Cvar_SetValue = Cvar_SetValue;
	ri.Vid_GetModeInfo = VID_GetModeInfo;
	ri.Vid_NewWindow = VID_NewWindow;
	ri.Z_Free = Z_Free; // jitmalloc
	ri.Z_Malloc = Z_Malloc; // jitmalloc
	ri.GetIntVarByID = GetIntVarByID;
	ri.e = &e;
	i.Com_Printf = Com_Printf;
	i.Cbuf_ExecuteText = Cbuf_ExecuteText;
	i.GetIntVarByID = GetIntVarByID;
	i.Cvar_Get = Cvar_Get;
	i.Cvar_Set = Cvar_Set;
	i.FS_LoadFileZ = FS_LoadFileZ;
	i.FS_FreeFile = FS_FreeFile;

	if ((GetRefAPI = (void*)GetProcAddress(reflib_library, "GetRefAPI")) == 0)
		Com_Error(ERR_FATAL, "GetProcAddress failed on %s.", name);

	if (testlib && !e.i)
	{
		GetTestAPI = (void*)GetProcAddress(testlib, "i");

		if (GetTestAPI)
			e = GetTestAPI(i);
	}

	re = GetRefAPI(ri);

	if (re.api_version != API_VERSION)
	{
		VID_FreeReflib();
		Com_Error(ERR_FATAL, "%s has incompatible api_version.", name);
	}

	if (re.Init(global_hInstance, MainWndProc) == -1)
	{
		re.Shutdown();
		VID_FreeReflib();
		return false;
	}

	Com_Printf("------------------------------------\n");
	reflib_active = true;
	vidref_val = VIDREF_GL;

	return true;
}
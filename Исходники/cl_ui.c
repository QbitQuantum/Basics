/*
====================
CL_UISystemCalls

The ui module is making a system call
====================
*/
intptr_t CL_UISystemCalls( intptr_t *args ) {
	switch ( args[0] ) {
	case UI_ERROR:
		Com_Error( ERR_DROP, "%s", VMA( 1 ) );
		return 0;

	case UI_PRINT:
		Com_Printf( "%s", VMA( 1 ) );
		return 0;

	case UI_MILLISECONDS:
		return Sys_Milliseconds();

	case UI_CVAR_REGISTER:
		Cvar_Register( VMA( 1 ), VMA( 2 ), VMA( 3 ), args[4] );
		return 0;

	case UI_CVAR_UPDATE:
		Cvar_Update( VMA( 1 ) );
		return 0;

	case UI_CVAR_SET:
		Cvar_Set( VMA( 1 ), VMA( 2 ) );
		return 0;

	case UI_CVAR_VARIABLEVALUE:
		return FloatAsInt( Cvar_VariableValue( VMA( 1 ) ) );

	case UI_CVAR_VARIABLESTRINGBUFFER:
		Cvar_VariableStringBuffer( VMA( 1 ), VMA( 2 ), args[3] );
		return 0;

	case UI_CVAR_SETVALUE:
		Cvar_SetValue( VMA( 1 ), VMF( 2 ) );
		return 0;

	case UI_CVAR_RESET:
		Cvar_Reset( VMA( 1 ) );
		return 0;

	case UI_CVAR_CREATE:
		Cvar_Get( VMA( 1 ), VMA( 2 ), args[3] );
		return 0;

	case UI_CVAR_INFOSTRINGBUFFER:
		Cvar_InfoStringBuffer( args[1], VMA( 2 ), args[3] );
		return 0;

	case UI_ARGC:
		return Cmd_Argc();

	case UI_ARGV:
		Cmd_ArgvBuffer( args[1], VMA( 2 ), args[3] );
		return 0;

	case UI_CMD_EXECUTETEXT:
		Cbuf_ExecuteText( args[1], VMA( 2 ) );
		return 0;

	case UI_FS_FOPENFILE:
		return FS_FOpenFileByMode( VMA( 1 ), VMA( 2 ), args[3] );

	case UI_FS_READ:
		FS_Read( VMA( 1 ), args[2], args[3] );
		return 0;

//----(SA)	added
	case UI_FS_SEEK:
		FS_Seek( args[1], args[2], args[3] );
		return 0;
//----(SA)	end

	case UI_FS_WRITE:
		FS_Write( VMA( 1 ), args[2], args[3] );
		return 0;

	case UI_FS_FCLOSEFILE:
		FS_FCloseFile( args[1] );
		return 0;

	case UI_FS_DELETEFILE:
		return FS_Delete( VMA( 1 ) );

	case UI_FS_GETFILELIST:
		return FS_GetFileList( VMA( 1 ), VMA( 2 ), VMA( 3 ), args[4] );

	case UI_R_REGISTERMODEL:
		return re.RegisterModel( VMA( 1 ) );

	case UI_R_REGISTERSKIN:
		return re.RegisterSkin( VMA( 1 ) );

	case UI_R_REGISTERSHADERNOMIP:
		return re.RegisterShaderNoMip( VMA( 1 ) );

	case UI_R_CLEARSCENE:
		re.ClearScene();
		return 0;

	case UI_R_ADDREFENTITYTOSCENE:
		re.AddRefEntityToScene( VMA( 1 ) );
		return 0;

	case UI_R_ADDPOLYTOSCENE:
		re.AddPolyToScene( args[1], args[2], VMA( 3 ) );
		return 0;

		// Ridah
	case UI_R_ADDPOLYSTOSCENE:
		re.AddPolysToScene( args[1], args[2], VMA( 3 ), args[4] );
		return 0;
		// done.

	case UI_R_ADDLIGHTTOSCENE:
		re.AddLightToScene( VMA( 1 ), VMF( 2 ), VMF( 3 ), VMF( 4 ), VMF( 5 ), args[6] );
		return 0;

	case UI_R_ADDCORONATOSCENE:
		re.AddCoronaToScene( VMA( 1 ), VMF( 2 ), VMF( 3 ), VMF( 4 ), VMF( 5 ), args[6], args[7] );
		return 0;

	case UI_R_RENDERSCENE:
		re.RenderScene( VMA( 1 ) );
		return 0;

	case UI_R_SETCOLOR:
		re.SetColor( VMA( 1 ) );
		return 0;

	case UI_R_DRAWSTRETCHPIC:
		re.DrawStretchPic( VMF( 1 ), VMF( 2 ), VMF( 3 ), VMF( 4 ), VMF( 5 ), VMF( 6 ), VMF( 7 ), VMF( 8 ), args[9] );
		return 0;

	case UI_R_MODELBOUNDS:
		re.ModelBounds( args[1], VMA( 2 ), VMA( 3 ) );
		return 0;

	case UI_UPDATESCREEN:
		SCR_UpdateScreen();
		return 0;

	case UI_CM_LERPTAG:
		return re.LerpTag( VMA( 1 ), VMA( 2 ), VMA( 3 ), args[4] );

	case UI_S_REGISTERSOUND:
#ifdef DOOMSOUND    ///// (SA) DOOMSOUND
		return S_RegisterSound( VMA( 1 ) );
#else
		return S_RegisterSound( VMA( 1 ), qfalse );
#endif  ///// (SA) DOOMSOUND

	case UI_S_STARTLOCALSOUND:
		S_StartLocalSound( args[1], args[2] );
		return 0;

//----(SA)	added
	case UI_S_FADESTREAMINGSOUND:
		S_FadeStreamingSound( VMF( 1 ), args[2], args[3] );
		return 0;

	case UI_S_FADEALLSOUNDS:
		S_FadeAllSounds( VMF( 1 ), args[2] );
		return 0;
//----(SA)	end

	case UI_KEY_KEYNUMTOSTRINGBUF:
		Key_KeynumToStringBuf( args[1], VMA( 2 ), args[3] );
		return 0;

	case UI_KEY_GETBINDINGBUF:
		Key_GetBindingBuf( args[1], VMA( 2 ), args[3] );
		return 0;

	case UI_KEY_SETBINDING:
		Key_SetBinding( args[1], VMA( 2 ) );
		return 0;

	case UI_KEY_ISDOWN:
		return Key_IsDown( args[1] );

	case UI_KEY_GETOVERSTRIKEMODE:
		return Key_GetOverstrikeMode();

	case UI_KEY_SETOVERSTRIKEMODE:
		Key_SetOverstrikeMode( args[1] );
		return 0;

	case UI_KEY_CLEARSTATES:
		Key_ClearStates();
		return 0;

	case UI_KEY_GETCATCHER:
		return Key_GetCatcher();

	case UI_KEY_SETCATCHER:
		Key_SetCatcher( args[1] );
		return 0;

	case UI_GETCLIPBOARDDATA:
		GetClipboardData( VMA( 1 ), args[2] );
		return 0;

	case UI_GETCLIENTSTATE:
		GetClientState( VMA( 1 ) );
		return 0;

	case UI_GETGLCONFIG:
		CL_GetGlconfig( VMA( 1 ) );
		return 0;

	case UI_GETCONFIGSTRING:
		return GetConfigString( args[1], VMA( 2 ), args[3] );

	case UI_LAN_LOADCACHEDSERVERS:
		LAN_LoadCachedServers();
		return 0;

	case UI_LAN_SAVECACHEDSERVERS:
		LAN_SaveServersToCache();
		return 0;

	case UI_LAN_ADDSERVER:
		return LAN_AddServer( args[1], VMA( 2 ), VMA( 3 ) );

	case UI_LAN_REMOVESERVER:
		LAN_RemoveServer( args[1], VMA( 2 ) );
		return 0;

	case UI_LAN_GETPINGQUEUECOUNT:
		return LAN_GetPingQueueCount();

	case UI_LAN_CLEARPING:
		LAN_ClearPing( args[1] );
		return 0;

	case UI_LAN_GETPING:
		LAN_GetPing( args[1], VMA( 2 ), args[3], VMA( 4 ) );
		return 0;

	case UI_LAN_GETPINGINFO:
		LAN_GetPingInfo( args[1], VMA( 2 ), args[3] );
		return 0;

	case UI_LAN_GETSERVERCOUNT:
		return LAN_GetServerCount( args[1] );

	case UI_LAN_GETSERVERADDRESSSTRING:
		LAN_GetServerAddressString( args[1], args[2], VMA( 3 ), args[4] );
		return 0;

	case UI_LAN_GETSERVERINFO:
		LAN_GetServerInfo( args[1], args[2], VMA( 3 ), args[4] );
		return 0;

	case UI_LAN_GETSERVERPING:
		return LAN_GetServerPing( args[1], args[2] );

	case UI_LAN_MARKSERVERVISIBLE:
		LAN_MarkServerVisible( args[1], args[2], args[3] );
		return 0;

	case UI_LAN_SERVERISVISIBLE:
		return LAN_ServerIsVisible( args[1], args[2] );

	case UI_LAN_UPDATEVISIBLEPINGS:
		return LAN_UpdateVisiblePings( args[1] );

	case UI_LAN_RESETPINGS:
		LAN_ResetPings( args[1] );
		return 0;

	case UI_LAN_SERVERSTATUS:
		return LAN_GetServerStatus( VMA( 1 ), VMA( 2 ), args[3] );

	case UI_LAN_COMPARESERVERS:
		return LAN_CompareServers( args[1], args[2], args[3], args[4], args[5] );

	case UI_MEMORY_REMAINING:
		return Hunk_MemoryRemaining();

	case UI_GET_CDKEY:
		CLUI_GetCDKey( VMA( 1 ), args[2] );
		return 0;

	case UI_SET_CDKEY:
		CLUI_SetCDKey( VMA( 1 ) );
		return 0;

	case UI_R_REGISTERFONT:
		re.RegisterFont( VMA( 1 ), args[2], VMA( 3 ) );
		return 0;

	case UI_MEMSET:
		return (intptr_t)memset( VMA( 1 ), args[2], args[3] );

	case UI_MEMCPY:
		return (intptr_t)memcpy( VMA( 1 ), VMA( 2 ), args[3] );

	case UI_STRNCPY:
		return (intptr_t)strncpy( VMA( 1 ), VMA( 2 ), args[3] );

	case UI_SIN:
		return FloatAsInt( sin( VMF( 1 ) ) );

	case UI_COS:
		return FloatAsInt( cos( VMF( 1 ) ) );

	case UI_ATAN2:
		return FloatAsInt( atan2( VMF( 1 ), VMF( 2 ) ) );

	case UI_SQRT:
		return FloatAsInt( sqrt( VMF( 1 ) ) );

	case UI_FLOOR:
		return FloatAsInt( floor( VMF( 1 ) ) );

	case UI_CEIL:
		return FloatAsInt( ceil( VMF( 1 ) ) );

	case UI_PC_ADD_GLOBAL_DEFINE:
		return botlib_export->PC_AddGlobalDefine( VMA( 1 ) );
	case UI_PC_LOAD_SOURCE:
		return botlib_export->PC_LoadSourceHandle( VMA( 1 ) );
	case UI_PC_FREE_SOURCE:
		return botlib_export->PC_FreeSourceHandle( args[1] );
	case UI_PC_READ_TOKEN:
		return botlib_export->PC_ReadTokenHandle( args[1], VMA( 2 ) );
	case UI_PC_SOURCE_FILE_AND_LINE:
		return botlib_export->PC_SourceFileAndLine( args[1], VMA( 2 ), VMA( 3 ) );

	case UI_S_STOPBACKGROUNDTRACK:
		S_StopBackgroundTrack();
		return 0;
	case UI_S_STARTBACKGROUNDTRACK:
		S_StartBackgroundTrack( VMA( 1 ), VMA( 2 ), args[3] );   //----(SA)	added fadeup time
		return 0;

	case UI_REAL_TIME:
		return Com_RealTime( VMA( 1 ) );

	case UI_CIN_PLAYCINEMATIC:
		Com_DPrintf( "UI_CIN_PlayCinematic\n" );
		return CIN_PlayCinematic( VMA( 1 ), args[2], args[3], args[4], args[5], args[6] );

	case UI_CIN_STOPCINEMATIC:
		return CIN_StopCinematic( args[1] );

	case UI_CIN_RUNCINEMATIC:
		return CIN_RunCinematic( args[1] );

	case UI_CIN_DRAWCINEMATIC:
		CIN_DrawCinematic( args[1] );
		return 0;

	case UI_CIN_SETEXTENTS:
		CIN_SetExtents( args[1], args[2], args[3], args[4], args[5] );
		return 0;

	case UI_R_REMAP_SHADER:
		re.RemapShader( VMA( 1 ), VMA( 2 ), VMA( 3 ) );
		return 0;

	case UI_VERIFY_CDKEY:
		return CL_CDKeyValidate( VMA( 1 ), VMA( 2 ) );

		// NERVE - SMF
	case UI_CL_GETLIMBOSTRING:
		return CL_GetLimboString( args[1], VMA( 2 ) );
		// -NERVE - SMF

	default:
		Com_Error( ERR_DROP, "Bad UI system trap: %i", args[0] );

	}

	return 0;
}
intptr_t CL_UISystemCalls( intptr_t *args ) {
	switch ( args[0] ) {
		//rww - alright, DO NOT EVER add a GAME/CGAME/UI generic call without adding a trap to match, and
		//all of these traps must be shared and have cases in sv_game, cl_cgame, and cl_ui. They must also
		//all be in the same order, and start at 100.
	case TRAP_MEMSET:
		Com_Memset( VMA(1), args[2], args[3] );
		return 0;

	case TRAP_MEMCPY:
		Com_Memcpy( VMA(1), VMA(2), args[3] );
		return 0;

	case TRAP_STRNCPY:
		strncpy( (char *)VMA(1), (const char *)VMA(2), args[3] );
		return args[1];

	case TRAP_SIN:
		return FloatAsInt( sin( VMF(1) ) );

	case TRAP_COS:
		return FloatAsInt( cos( VMF(1) ) );

	case TRAP_ATAN2:
		return FloatAsInt( atan2( VMF(1), VMF(2) ) );

	case TRAP_SQRT:
		return FloatAsInt( sqrt( VMF(1) ) );

	case TRAP_MATRIXMULTIPLY:
		MatrixMultiply( (vec3_t *)VMA(1), (vec3_t *)VMA(2), (vec3_t *)VMA(3) );
		return 0;

	case TRAP_ANGLEVECTORS:
		AngleVectors( (const float *)VMA(1), (float *)VMA(2), (float *)VMA(3), (float *)VMA(4) );
		return 0;

	case TRAP_PERPENDICULARVECTOR:
		PerpendicularVector( (float *)VMA(1), (const float *)VMA(2) );
		return 0;

	case TRAP_FLOOR:
		return FloatAsInt( floor( VMF(1) ) );

	case TRAP_CEIL:
		return FloatAsInt( ceil( VMF(1) ) );

	case TRAP_TESTPRINTINT:
		return 0;

	case TRAP_TESTPRINTFLOAT:
		return 0;

	case TRAP_ACOS:
		return FloatAsInt( Q_acos( VMF(1) ) );

	case TRAP_ASIN:
		return FloatAsInt( Q_asin( VMF(1) ) );

	case UI_ERROR:
		Com_Error( ERR_DROP, "%s", VMA(1) );
		return 0;

	case UI_PRINT:
		Com_Printf( "%s", VMA(1) );
		return 0;

	case UI_MILLISECONDS:
		return Sys_Milliseconds();

	case UI_CVAR_REGISTER:
		Cvar_Register( (vmCvar_t *)VMA(1), (const char *)VMA(2), (const char *)VMA(3), args[4] ); 
		return 0;

	case UI_CVAR_UPDATE:
		Cvar_Update( (vmCvar_t *)VMA(1) );
		return 0;

	case UI_CVAR_SET:
		Cvar_VM_Set( (const char *)VMA(1), (const char *)VMA(2), VM_UI );
		return 0;

	case UI_CVAR_VARIABLEVALUE:
		return FloatAsInt( Cvar_VariableValue( (const char *)VMA(1) ) );

	case UI_CVAR_VARIABLESTRINGBUFFER:
		Cvar_VariableStringBuffer( (const char *)VMA(1), (char *)VMA(2), args[3] );
		return 0;

	case UI_CVAR_SETVALUE:
		Cvar_VM_SetValue( (const char *)VMA(1), VMF(2), VM_UI );
		return 0;

	case UI_CVAR_RESET:
		Cvar_Reset( (const char *)VMA(1) );
		return 0;

	case UI_CVAR_CREATE:
		Cvar_Get( (const char *)VMA(1), (const char *)VMA(2), args[3] );
		return 0;

	case UI_CVAR_INFOSTRINGBUFFER:
		Cvar_InfoStringBuffer( args[1], (char *)VMA(2), args[3] );
		return 0;

	case UI_ARGC:
		return Cmd_Argc();

	case UI_ARGV:
		Cmd_ArgvBuffer( args[1], (char *)VMA(2), args[3] );
		return 0;

	case UI_CMD_EXECUTETEXT:
		Cbuf_ExecuteText( args[1], (const char *)VMA(2) );
		return 0;

	case UI_FS_FOPENFILE:
		return FS_FOpenFileByMode( (const char *)VMA(1), (int *)VMA(2), (fsMode_t)args[3] );

	case UI_FS_READ:
		FS_Read( VMA(1), args[2], args[3] );
		return 0;

	case UI_FS_WRITE:
		FS_Write( VMA(1), args[2], args[3] );
		return 0;

	case UI_FS_FCLOSEFILE:
		FS_FCloseFile( args[1] );
		return 0;

	case UI_FS_GETFILELIST:
		return FS_GetFileList( (const char *)VMA(1), (const char *)VMA(2), (char *)VMA(3), args[4] );

	case UI_R_REGISTERMODEL:
		return re->RegisterModel( (const char *)VMA(1) );

	case UI_R_REGISTERSKIN:
		return re->RegisterSkin( (const char *)VMA(1) );

	case UI_R_REGISTERSHADERNOMIP:
		return re->RegisterShaderNoMip( (const char *)VMA(1) );

	case UI_R_SHADERNAMEFROMINDEX:
		CL_R_ShaderNameFromIndex( (char *)VMA(1), args[2] );
		return 0;

	case UI_R_CLEARSCENE:
		re->ClearScene();
		return 0;

	case UI_R_ADDREFENTITYTOSCENE:
		re->AddRefEntityToScene( (const refEntity_t *)VMA(1) );
		return 0;

	case UI_R_ADDPOLYTOSCENE:
		re->AddPolyToScene( args[1], args[2], (const polyVert_t *)VMA(3), 1 );
		return 0;

	case UI_R_ADDLIGHTTOSCENE:
		re->AddLightToScene( (const float *)VMA(1), VMF(2), VMF(3), VMF(4), VMF(5) );
		return 0;

	case UI_R_RENDERSCENE:
		re->RenderScene( (const refdef_t *)VMA(1) );
		return 0;

	case UI_R_SETCOLOR:
		re->SetColor( (const float *)VMA(1) );
		return 0;

	case UI_R_DRAWSTRETCHPIC:
		re->DrawStretchPic( VMF(1), VMF(2), VMF(3), VMF(4), VMF(5), VMF(6), VMF(7), VMF(8), args[9] );
		return 0;

	case UI_R_MODELBOUNDS:
		re->ModelBounds( args[1], (float *)VMA(2), (float *)VMA(3) );
		return 0;

	case UI_UPDATESCREEN:
		SCR_UpdateScreen();
		return 0;

	case UI_CM_LERPTAG:
		re->LerpTag( (orientation_t *)VMA(1), args[2], args[3], args[4], VMF(5), (const char *)VMA(6) );
		return 0;

	case UI_S_REGISTERSOUND:
		return S_RegisterSound( (const char *)VMA(1) );

	case UI_S_STARTLOCALSOUND:
		S_StartLocalSound( args[1], args[2] );
		return 0;

	case UI_KEY_KEYNUMTOSTRINGBUF:
		Key_KeynumToStringBuf( args[1], (char *)VMA(2), args[3] );
		return 0;

	case UI_KEY_GETBINDINGBUF:
		Key_GetBindingBuf( args[1], (char *)VMA(2), args[3] );
		return 0;

	case UI_KEY_SETBINDING:
		Key_SetBinding( args[1], (const char *)VMA(2) );
		return 0;

	case UI_KEY_ISDOWN:
		return Key_IsDown( args[1] );

	case UI_KEY_GETOVERSTRIKEMODE:
		return Key_GetOverstrikeMode();

	case UI_KEY_SETOVERSTRIKEMODE:
		Key_SetOverstrikeMode( (qboolean)args[1] );
		return 0;

	case UI_KEY_CLEARSTATES:
		Key_ClearStates();
		return 0;

	case UI_KEY_GETCATCHER:
		return Key_GetCatcher();

	case UI_KEY_SETCATCHER:
		CL_Key_SetCatcher( args[1] );
		return 0;

	case UI_GETCLIPBOARDDATA:
		GetClipboardData( (char *)VMA(1), args[2] );
		return 0;

	case UI_GETCLIENTSTATE:
		CL_GetClientState( (uiClientState_t *)VMA(1) );
		return 0;		

	case UI_GETGLCONFIG:
		CL_GetGlconfig( (glconfig_t *)VMA(1) );
		return 0;

	case UI_GETCONFIGSTRING:
		return GetConfigString( args[1], (char *)VMA(2), args[3] );

	case UI_LAN_LOADCACHEDSERVERS:
		LAN_LoadCachedServers();
		return 0;

	case UI_LAN_SAVECACHEDSERVERS:
		LAN_SaveServersToCache();
		return 0;

	case UI_LAN_ADDSERVER:
		return LAN_AddServer(args[1], (const char *)VMA(2), (const char *)VMA(3));

	case UI_LAN_REMOVESERVER:
		LAN_RemoveServer(args[1], (const char *)VMA(2));
		return 0;

	case UI_LAN_GETPINGQUEUECOUNT:
		return LAN_GetPingQueueCount();

	case UI_LAN_CLEARPING:
		LAN_ClearPing( args[1] );
		return 0;

	case UI_LAN_GETPING:
		LAN_GetPing( args[1], (char *)VMA(2), args[3], (int *)VMA(4) );
		return 0;

	case UI_LAN_GETPINGINFO:
		LAN_GetPingInfo( args[1], (char *)VMA(2), args[3] );
		return 0;

	case UI_LAN_GETSERVERCOUNT:
		return LAN_GetServerCount(args[1]);

	case UI_LAN_GETSERVERADDRESSSTRING:
		LAN_GetServerAddressString( args[1], args[2], (char *)VMA(3), args[4] );
		return 0;

	case UI_LAN_GETSERVERINFO:
		LAN_GetServerInfo( args[1], args[2], (char *)VMA(3), args[4] );
		return 0;

	case UI_LAN_GETSERVERPING:
		return LAN_GetServerPing( args[1], args[2] );

	case UI_LAN_MARKSERVERVISIBLE:
		LAN_MarkServerVisible( args[1], args[2], (qboolean)args[3] );
		return 0;

	case UI_LAN_SERVERISVISIBLE:
		return LAN_ServerIsVisible( args[1], args[2] );

	case UI_LAN_UPDATEVISIBLEPINGS:
		return LAN_UpdateVisiblePings( args[1] );

	case UI_LAN_RESETPINGS:
		LAN_ResetPings( args[1] );
		return 0;

	case UI_LAN_SERVERSTATUS:
		return LAN_GetServerStatus( (char *)VMA(1), (char *)VMA(2), args[3] );

	case UI_LAN_COMPARESERVERS:
		return LAN_CompareServers( args[1], args[2], args[3], args[4], args[5] );

	case UI_MEMORY_REMAINING:
		return Hunk_MemoryRemaining();

	case UI_R_REGISTERFONT:
		return re->RegisterFont( (const char *)VMA(1) );

	case UI_R_FONT_STRLENPIXELS:
		return re->Font_StrLenPixels( (const char *)VMA(1), args[2], VMF(3) );

	case UI_R_FONT_STRLENCHARS:
		return re->Font_StrLenChars( (const char *)VMA(1) );

	case UI_R_FONT_STRHEIGHTPIXELS:
		return re->Font_HeightPixels( args[1], VMF(2) );

	case UI_R_FONT_DRAWSTRING:
		re->Font_DrawString( args[1], args[2], (const char *)VMA(3), (const float *) VMA(4), args[5], args[6], VMF(7) );
		return 0;

	case UI_LANGUAGE_ISASIAN:
		return re->Language_IsAsian();

	case UI_LANGUAGE_USESSPACES:
		return re->Language_UsesSpaces();

	case UI_ANYLANGUAGE_READCHARFROMSTRING:
		return re->AnyLanguage_ReadCharFromString( (const char *)VMA(1), (int *) VMA(2), (qboolean *) VMA(3) );

	case UI_PC_ADD_GLOBAL_DEFINE:
		return botlib_export->PC_AddGlobalDefine( (char *)VMA(1) );

	case UI_PC_LOAD_SOURCE:
		return botlib_export->PC_LoadSourceHandle( (const char *)VMA(1) );

	case UI_PC_FREE_SOURCE:
		return botlib_export->PC_FreeSourceHandle( args[1] );

	case UI_PC_READ_TOKEN:
		return botlib_export->PC_ReadTokenHandle( args[1], (struct pc_token_s *)VMA(2) );

	case UI_PC_SOURCE_FILE_AND_LINE:
		return botlib_export->PC_SourceFileAndLine( args[1], (char *)VMA(2), (int *)VMA(3) );

	case UI_PC_LOAD_GLOBAL_DEFINES:
		return botlib_export->PC_LoadGlobalDefines ( (char *)VMA(1) );

	case UI_PC_REMOVE_ALL_GLOBAL_DEFINES:
		botlib_export->PC_RemoveAllGlobalDefines ( );
		return 0;

	case UI_S_STOPBACKGROUNDTRACK:
		S_StopBackgroundTrack();
		return 0;

	case UI_S_STARTBACKGROUNDTRACK:
		S_StartBackgroundTrack( (const char *)VMA(1), (const char *)VMA(2), qfalse );
		return 0;

	case UI_REAL_TIME:
		return Com_RealTime( (struct qtime_s *)VMA(1) );

	case UI_CIN_PLAYCINEMATIC:
		Com_DPrintf("UI_CIN_PlayCinematic\n");
		return CIN_PlayCinematic((const char *)VMA(1), args[2], args[3], args[4], args[5], args[6]);

	case UI_CIN_STOPCINEMATIC:
		return CIN_StopCinematic(args[1]);

	case UI_CIN_RUNCINEMATIC:
		return CIN_RunCinematic(args[1]);

	case UI_CIN_DRAWCINEMATIC:
		CIN_DrawCinematic(args[1]);
		return 0;

	case UI_CIN_SETEXTENTS:
		CIN_SetExtents(args[1], args[2], args[3], args[4], args[5]);
		return 0;

	case UI_R_REMAP_SHADER:
		re->RemapShader( (const char *)VMA(1), (const char *)VMA(2), (const char *)VMA(3) );
		return 0;

	case UI_SP_GETNUMLANGUAGES:
		return SE_GetNumLanguages();

	case UI_SP_GETLANGUAGENAME:
		CL_SE_GetLanguageName( args[1], (char *)VMA(2) );
		return 0;

	case UI_SP_GETSTRINGTEXTSTRING:
		return CL_SE_GetStringTextString( (const char *)VMA(1), (char *)VMA(2), args[3] );

	case UI_G2_LISTSURFACES:
		re->G2API_ListSurfaces( (CGhoul2Info *) args[1] );
		return 0;

	case UI_G2_LISTBONES:
		re->G2API_ListBones( (CGhoul2Info *) args[1], args[2]);
		return 0;

	case UI_G2_HAVEWEGHOULMODELS:
		return re->G2API_HaveWeGhoul2Models( *((CGhoul2Info_v *)args[1]) );

	case UI_G2_SETMODELS:
		re->G2API_SetGhoul2ModelIndexes( *((CGhoul2Info_v *)args[1]),(qhandle_t *)VMA(2),(qhandle_t *)VMA(3));
		return 0;

	case UI_G2_GETBOLT:
		return re->G2API_GetBoltMatrix(*((CGhoul2Info_v *)args[1]), args[2], args[3], (mdxaBone_t *)VMA(4), (const float *)VMA(5),(const float *)VMA(6), args[7], (qhandle_t *)VMA(8), (float *)VMA(9));

	case UI_G2_GETBOLT_NOREC:
		re->G2API_BoltMatrixReconstruction( qfalse );//gG2_GBMNoReconstruct = qtrue;
		return re->G2API_GetBoltMatrix(*((CGhoul2Info_v *)args[1]), args[2], args[3], (mdxaBone_t *)VMA(4), (const float *)VMA(5),(const float *)VMA(6), args[7], (qhandle_t *)VMA(8), (float *)VMA(9));

	case UI_G2_GETBOLT_NOREC_NOROT:
		// cgame reconstructs bolt matrix, why is this different?
		re->G2API_BoltMatrixReconstruction( qfalse );//gG2_GBMNoReconstruct = qtrue;
		re->G2API_BoltMatrixSPMethod( qtrue );//gG2_GBMUseSPMethod = qtrue;
		return re->G2API_GetBoltMatrix(*((CGhoul2Info_v *)args[1]), args[2], args[3], (mdxaBone_t *)VMA(4), (const float *)VMA(5),(const float *)VMA(6), args[7], (qhandle_t *)VMA(8), (float *)VMA(9));

	case UI_G2_INITGHOUL2MODEL:
#ifdef _FULL_G2_LEAK_CHECKING
		g_G2AllocServer = 0;
#endif
		return	re->G2API_InitGhoul2Model((CGhoul2Info_v **)VMA(1), (const char *)VMA(2), args[3], (qhandle_t) args[4], (qhandle_t) args[5], args[6], args[7]);

	case UI_G2_COLLISIONDETECT:
	case UI_G2_COLLISIONDETECTCACHE:
		return 0; //not supported for ui

	case UI_G2_ANGLEOVERRIDE:
		return re->G2API_SetBoneAngles(*((CGhoul2Info_v *)args[1]), args[2], (const char *)VMA(3), (float *)VMA(4), args[5], (const Eorientations) args[6], (const Eorientations) args[7], (const Eorientations) args[8], (qhandle_t *)VMA(9), args[10], args[11] );

	case UI_G2_CLEANMODELS:
#ifdef _FULL_G2_LEAK_CHECKING
		g_G2AllocServer = 0;
#endif
		re->G2API_CleanGhoul2Models((CGhoul2Info_v **)VMA(1));
		//	re->G2API_CleanGhoul2Models((CGhoul2Info_v **)args[1]);
		return 0;

	case UI_G2_PLAYANIM:
		return re->G2API_SetBoneAnim(*((CGhoul2Info_v *)args[1]), args[2], (const char *)VMA(3), args[4], args[5], args[6], VMF(7), args[8], VMF(9), args[10]);

	case UI_G2_GETBONEANIM:
		{
			CGhoul2Info_v &g2 = *((CGhoul2Info_v *)args[1]);
			int modelIndex = args[10];

			return re->G2API_GetBoneAnim(&g2[modelIndex], (const char*)VMA(2), args[3], (float *)VMA(4), (int *)VMA(5), (int *)VMA(6), (int *)VMA(7), (float *)VMA(8), (int *)VMA(9));
		}

	case UI_G2_GETBONEFRAME:
		{ //rwwFIXMEFIXME: Just make a G2API_GetBoneFrame func too. This is dirty.
			CGhoul2Info_v &g2 = *((CGhoul2Info_v *)args[1]);
			int modelIndex = args[6];
			int iDontCare1 = 0, iDontCare2 = 0, iDontCare3 = 0;
			float fDontCare1 = 0;

			return re->G2API_GetBoneAnim(&g2[modelIndex], (const char*)VMA(2), args[3], (float *)VMA(4), &iDontCare1, &iDontCare2, &iDontCare3, &fDontCare1, (int *)VMA(5));
		}

	case UI_G2_GETGLANAME:
		//	return (int)G2API_GetGLAName(*((CGhoul2Info_v *)VMA(1)), args[2]);
		{
			char *point = ((char *)VMA(3));
			char *local;
			local = re->G2API_GetGLAName(*((CGhoul2Info_v *)args[1]), args[2]);
			if (local)
			{
				strcpy(point, local);
			}
		}
		return 0;

	case UI_G2_COPYGHOUL2INSTANCE:
		return (int)re->G2API_CopyGhoul2Instance(*((CGhoul2Info_v *)args[1]), *((CGhoul2Info_v *)args[2]), args[3]);

	case UI_G2_COPYSPECIFICGHOUL2MODEL:
		re->G2API_CopySpecificG2Model(*((CGhoul2Info_v *)args[1]), args[2], *((CGhoul2Info_v *)args[3]), args[4]);
		return 0;

	case UI_G2_DUPLICATEGHOUL2INSTANCE:
#ifdef _FULL_G2_LEAK_CHECKING
		g_G2AllocServer = 0;
#endif
		re->G2API_DuplicateGhoul2Instance(*((CGhoul2Info_v *)args[1]), (CGhoul2Info_v **)VMA(2));
		return 0;

	case UI_G2_HASGHOUL2MODELONINDEX:
		return (int)re->G2API_HasGhoul2ModelOnIndex((CGhoul2Info_v **)VMA(1), args[2]);
		//return (int)G2API_HasGhoul2ModelOnIndex((CGhoul2Info_v **)args[1], args[2]);

	case UI_G2_REMOVEGHOUL2MODEL:
#ifdef _FULL_G2_LEAK_CHECKING
		g_G2AllocServer = 0;
#endif
		return (int)re->G2API_RemoveGhoul2Model((CGhoul2Info_v **)VMA(1), args[2]);
		//return (int)G2API_RemoveGhoul2Model((CGhoul2Info_v **)args[1], args[2]);

	case UI_G2_ADDBOLT:
		return re->G2API_AddBolt(*((CGhoul2Info_v *)args[1]), args[2], (const char *)VMA(3));

	case UI_G2_SETBOLTON:
		re->G2API_SetBoltInfo(*((CGhoul2Info_v *)args[1]), args[2], args[3]);
		return 0;

	case UI_G2_SETROOTSURFACE:
		return re->G2API_SetRootSurface(*((CGhoul2Info_v *)args[1]), args[2], (const char *)VMA(3));

	case UI_G2_SETSURFACEONOFF:
		return re->G2API_SetSurfaceOnOff(*((CGhoul2Info_v *)args[1]), (const char *)VMA(2), /*(const int)VMA(3)*/args[3]);

	case UI_G2_SETNEWORIGIN:
		return re->G2API_SetNewOrigin(*((CGhoul2Info_v *)args[1]), /*(const int)VMA(2)*/args[2]);

	case UI_G2_GETTIME:
		return re->G2API_GetTime(0);

	case UI_G2_SETTIME:
		re->G2API_SetTime(args[1], args[2]);
		return 0;

	case UI_G2_SETRAGDOLL:
		return 0; //not supported for ui
		break;

	case UI_G2_ANIMATEG2MODELS:
		return 0; //not supported for ui
		break;

	case UI_G2_SETBONEIKSTATE:
		return re->G2API_SetBoneIKState(*((CGhoul2Info_v *)args[1]), args[2], (const char *)VMA(3), args[4], (sharedSetBoneIKStateParams_t *)VMA(5));

	case UI_G2_IKMOVE:
		return re->G2API_IKMove(*((CGhoul2Info_v *)args[1]), args[2], (sharedIKMoveParams_t *)VMA(3));

	case UI_G2_GETSURFACENAME:
		{ //Since returning a pointer in such a way to a VM seems to cause MASSIVE FAILURE<tm>, we will shove data into the pointer the vm passes instead
			char *point = ((char *)VMA(4));
			char *local;
			int modelindex = args[3];

			CGhoul2Info_v &g2 = *((CGhoul2Info_v *)args[1]);

			local = re->G2API_GetSurfaceName(&g2[modelindex], args[2]);
			if (local)
			{
				strcpy(point, local);
			}
		}

		return 0;
	case UI_G2_SETSKIN:
		{
			CGhoul2Info_v &g2 = *((CGhoul2Info_v *)args[1]);
			int modelIndex = args[2];

			return re->G2API_SetSkin(&g2[modelIndex], args[3], args[4]);
		}

	case UI_G2_ATTACHG2MODEL:
		{
			CGhoul2Info_v *g2From = ((CGhoul2Info_v *)args[1]);
			CGhoul2Info_v *g2To = ((CGhoul2Info_v *)args[3]);

			return re->G2API_AttachG2Model(*g2From, args[2], *g2To, args[4], args[5]);
		}

	default:
		Com_Error( ERR_DROP, "Bad UI system trap: %ld", (long int) args[0] );

	}

	return 0;
}
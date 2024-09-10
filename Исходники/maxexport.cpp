BOOL APIENTRY DllMain( HINSTANCE instance, DWORD reason, void* /*reserved*/ )
{
	s_classDescMySceneExport.instance = instance;
	
	if ( !s_controlsInit )
	{
		s_controlsInit = true;
		InitCustomControls( instance );
		InitCommonControls();
	}

    switch ( reason )
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}

	return TRUE;
}
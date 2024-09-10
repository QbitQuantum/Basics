BOOL WINAPI DllMain(	HINSTANCE	hInstance,
                        DWORD		reason,
                        LPVOID		pReserved )
{
	IFXRESULT	result	= IFX_OK;

    if ( reason == DLL_PROCESS_ATTACH )
    {
		DisableThreadLibraryCalls( hInstance );

		result = IFXRenderingStartup();
    }
    else if ( reason == DLL_PROCESS_DETACH )
    {
		result = IFXRenderingShutdown();
    }

	return ( IFXSUCCESS( result ) ? TRUE : FALSE );
}
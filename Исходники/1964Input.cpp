/******************************************************************
  Function: RomOpen
  Purpose:  This function is called when a rom is open. (from the 
            emulation thread)
  input:    none
  output:   none
*******************************************************************/ 
EXPORT void CALL RomOpen (void)
{
	DebugWriteA("CALLED: RomOpen\n");

	XInputEnable( TRUE );	// enables xinput --tecnicors

	if( !g_strEmuInfo.fInitialisedPlugin )
	{
		ErrorMessage(IDS_ERR_NOINIT, 0, false);
		return;
	}
	
	EnterCriticalSection( &g_critical );
	// re-init our paks and shortcuts
	InitiatePaks( true );
	// LoadShortcuts( &g_scShortcuts ); WHY are we loading shortcuts again?? Should already be loaded!
	LeaveCriticalSection( &g_critical );
	g_bRunning = true;
	return;
}
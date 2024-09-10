/*
=================
CL_FlushMemory

Called by CL_MapLoading, CL_Connect_f, and CL_ParseGamestate the only
ways a client gets into a game
Also called by Com_Error
=================
*/
void CL_FlushMemory( void ) {

	// clear sounds (moved higher up within this func to avoid the odd sound stutter)
	S_DisableSounds();

	// unload the old VM
	CL_ShutdownCGame();

	CL_ShutdownUI();

	if ( re.Shutdown ) {
		re.Shutdown( qfalse );		// don't destroy window or context
	}

	cls.soundRegistered = qfalse;
	cls.rendererStarted = qfalse;
}
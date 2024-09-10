/*------------------------------------------------------------------*\
							submitEvents()
\*------------------------------------------------------------------*/
void CWinEventEmitter::submitEvents(CEventServer & server, bool allWindows)
{
	MSG	msg;
	while ( PeekMessageW(&msg,allWindows?NULL:_HWnd,0,0,PM_REMOVE) )
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	// Dispatch sent messages
	_InternalServer.setServer (&server);
	_InternalServer.pump (allWindows);
}
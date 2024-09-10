/*
===============
idEventLoop::RunEventLoop
===============
*/
int idEventLoop::RunEventLoop( bool commandExecution )
{
	sysEvent_t	ev;
	
	while( 1 )
	{
	
		if( commandExecution )
		{
			// execute any bound commands before processing another event
			cmdSystem->ExecuteCommandBuffer();
		}
		
		ev = GetEvent();
		
		// if no more events are available
		if( ev.evType == SE_NONE )
		{
			return 0;
		}
		ProcessEvent( ev );
	}
	
	return 0;	// never reached
}
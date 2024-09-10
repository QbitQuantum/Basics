DWORD WINAPI ttapiThreadProc( LPVOID lpParameter )
{
	LPTTAPI_WORKER_PARAMS pParams = ( LPTTAPI_WORKER_PARAMS ) lpParameter;
	DWORD i , dwFastIter = ttapi_dwFastIter , dwSlowIter = ttapi_dwSlowIter;

	while( TRUE ) {		
		// Wait

		// Fast
		for ( i = 0 ; i < dwFastIter ; ++i ) {
			if ( pParams->vlFlag == 0 ) {
				// Msg( "0x%8.8X Fast %u" , dwId , i );
				goto process;
			}
			__asm pause;
		}

		// Moderate
		for ( i = 0 ; i < dwSlowIter ; ++i ) {
			if ( pParams->vlFlag == 0 ) {
				// Msg( "0x%8.8X Moderate %u" , dwId , i );
				goto process;
			}
			SwitchToThread();
		}

		// Slow
		while ( pParams->vlFlag ) {
			Sleep( 100 );
			//Msg( "Shit" );
		}

		process:

		pParams->vlFlag = 1;

		if ( pParams->lpWorkerFunc )
			pParams->lpWorkerFunc( pParams->lpvWorkerFuncParams );
		else
			break;

		_InterlockedDecrement( &ttapi_queue_size.size );

	} // while

	return 0;
}
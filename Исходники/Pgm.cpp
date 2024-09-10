//
//  window procedure
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HANDLE hThread[NUM_OF_THREADS] ;
	static ThreadArgument arg[NUM_OF_THREADS] ;
	static DWORD threadID ;
	int wmId, wmEvent ;
	unsigned int loop ;

	switch( message ) {

		case WM_CREATE:
			mutex = CreateMutex( 0, FALSE, 0 ) ;
			break ;

		case WM_COMMAND:			// user menu
			wmId    = LOWORD( wParam ) ;
			wmEvent = HIWORD( wParam ) ;
			switch( wmId ) {
				case IDM_TEST:
					sX = 0 ;
					for( loop = 0 ; loop < NUM_OF_THREADS ; loop++ ) 
					{
						arg[loop].hWnd = hWnd;
						arg[loop].NO = loop;

						hThread[loop] = CreateThread( 0, 0,	// create a thread
								(LPTHREAD_START_ROUTINE)drawThread, 
												(VOID *)&(arg[loop]), 0, &threadID ) ;
					}
					while( WaitForMultipleObjects( NUM_OF_THREADS, hThread, 
														TRUE, 0) == WAIT_TIMEOUT )
						Sleep( 10 ) ;
					break;

				case IDM_CLEAR:
					InvalidateRgn( hWnd, NULL, TRUE ) ;
					break ;

				case IDM_EXIT:
					DestroyWindow(hWnd);
					break;
				default:
					return DefWindowProc( hWnd, message, wParam, lParam ) ;
			}
			break ;
			
		case WM_DESTROY:
			CloseHandle( mutex ) ;
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc( hWnd, message, wParam, lParam ) ;
	}
	return 0 ;
}
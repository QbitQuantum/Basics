// Screen Saver Procedure
LRESULT WINAPI ScreenSaverProc(HWND hWnd, UINT message, 
							   WPARAM wParam, LPARAM lParam)
{

	switch ( message ) 
	{
	case WM_CREATE: 
		struct _timeb tb;
		_ftime( &tb );

		// initialize random number generator
		srand((999*tb.time) + (1001*tb.millitm) + (1003 * _getpid()));

		if (gTimeCounter == 0.0) {
			gTimeCounter = currentTime();
		}

		if (flurry_info == NULL) {
			flurry_info = (global_info_t*)malloc(sizeof(global_info_t));
		}

		// enable OpenGL for the window
		ReadPresetFromRegistry();

		EnableOpenGL( hWnd, &flurry_info->window, &flurry_info->glx_context);
		init_flurry( hWnd, flurry_info );

		/* 
		* this clamps the speed at below 60fps and, here
		* at least, produces a reasonably accurate 50fps.
		* (probably part CPU speed and part scheduler).
		*
		* Flurry is designed to run at this speed; much higher
		* than that and the blending causes the display to
		* saturate, which looks really ugly.
		*/

		//create a timer that ticks every 10 milliseconds
		// 40ms delay = 25fps
		// 30ms delay ~ 30fps
		// 20ms delay = 50fps

		SetTimer( hWnd, TIMER, 20, NULL ); 
		return 0;
	case WM_DESTROY:
		KillTimer( hWnd, TIMER );

		//delete any objects created during animation
		//and close down OpenGL nicely
		DisableOpenGL( hWnd, flurry_info->window, flurry_info->glx_context );
		release_flurry();

		return 0;
	case WM_TIMER:
		// call some function to advance your animation	
		draw_flurry( &flurry_info->window, &flurry_info->glx_context );
		return 0;				
	}

	//let the screensaver library take care of any
	//other messages
	return DefScreenSaverProc(hWnd, message, wParam, lParam);
}
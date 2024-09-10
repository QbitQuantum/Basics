// Window procedure, handles all messages for this program
LRESULT CALLBACK WndProc(	HWND 	hWnd,
							UINT	message,
							WPARAM	wParam,
							LPARAM	lParam)
	{
	static HGLRC hRC;		// Permenant Rendering context
	static HDC hDC;			// Private GDI Device context

	switch (message)
	   	{
		// Window creation, setup for OpenGL
		case WM_CREATE:
			// Store the device context
			hDC = GetDC(hWnd);		

			// Select the pixel format
			SetDCPixelFormat(hDC);		

			// Create the rendering context and make it current
			hRC = wglCreateContext(hDC);
			wglMakeCurrent(hDC, hRC);

			// Create a timer that fires 30 times a second
			SetTimer(hWnd,33,1,NULL);
			break;

		// Window is being destroyed, cleanup
		case WM_DESTROY:
			// Kill the timer that we created
			KillTimer(hWnd,101);

			// Deselect the current rendering context and delete it
			wglMakeCurrent(hDC,NULL);
			wglDeleteContext(hRC);

			// Tell the application to terminate after the window
			// is gone.
			PostQuitMessage(0);
			break;
        
		// Window is resized.
		case WM_SIZE:
			// Call our function which modifies the clipping
			// volume and viewport
			ChangeSize(LOWORD(lParam), HIWORD(lParam));
			break;

		// Timer, moves and bounces the rectangle, simply calls
		// our previous OnIdle function, then invalidates the 
		// window so it will be redrawn.
		case WM_TIMER:
			{
			IdleFunction();
		
			InvalidateRect(hWnd,NULL,FALSE);
			}
			break;

		// The painting function.  This message sent by Windows 
		// whenever the screen needs updating.
		case WM_PAINT:
			{
			// Call OpenGL drawing code
			RenderScene();

			// Call function to swap the buffers
			SwapBuffers(hDC);

			// Validate the newly painted client area
			ValidateRect(hWnd,NULL);
			}
			break;



        default:   // Passes it on if unproccessed
            return (DefWindowProc(hWnd, message, wParam, lParam));

        }

    return (0L);
	}
int CALLBACK WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CommandLine, int ShowFlags)
{
	DWORD error;
	UINT DesiredSchedulerMS = 1;

	float MSPerFrame = 0;
	float TargetSecondsPerFrame;

	int width;
	int height;
	
	HWND Window;
	RECT ClientRect;

	HGLRC RC;

	GLenum err = 0;

	GameState state = {0};

	WNDCLASSEX WindowClass;
	WindowClass.cbSize = sizeof(WindowClass);
    WindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    WindowClass.lpfnWndProc = MyWindowProc;
    WindowClass.cbClsExtra = 0;
    WindowClass.cbWndExtra = 0;
    WindowClass.hInstance = Instance;
    WindowClass.hIcon = 0;
    WindowClass.hCursor = 0;
    WindowClass.hbrBackground = 0;
    WindowClass.lpszMenuName = NULL;
    WindowClass.lpszClassName = "WindowClass";
    WindowClass.hIconSm = 0;

	if( RegisterClassEx(&WindowClass) )
	{
		width = GetSystemMetrics(SM_CXMAXIMIZED);
		height = GetSystemMetrics(SM_CYMAXIMIZED);

		Window = CreateWindowExA(0, WindowClass.lpszClassName, "My Test Window",
									  WS_OVERLAPPEDWINDOW|WS_VISIBLE|WS_MAXIMIZE,
									  0, 0, width, height,
									  0, 0, Instance, 0);

		TargetSecondsPerFrame = 1.0f / 60.0f;

		if(Window)
		{
			HDC DC = GetDC(Window);
			SetupPixelFormat(DC);
            RC = wglCreateContext(DC);
            wglMakeCurrent(DC, RC);

			err = glewInit();
			if (GLEW_OK != err)
				fprintf(stderr, "Error: %s\n", glewGetErrorString(err));

			GetClientRect(Window, &ClientRect);

			width = ClientRect.right - ClientRect.left;
			height = ClientRect.bottom - ClientRect.top;

			state.width = (float)width;
			state.height = (float)height;

			glViewport(0,0, width, height);
			glEnable(GL_DEPTH_TEST);

			//V3 p1 = { -8.0f, 6.0f, 4.3f };
			V3 p1 = { 0.0f, 6.0f, 4.0f };
			InitCamera(&state.main, p1);
			
			state.deltaT = TargetSecondsPerFrame;
			
			InitGame(&state);
			
			Running = 1;

			LARGE_INTEGER start, end;

			float timeElasped;
			DWORD sleepMS;

			while(Running)
			{
				start = Win32GetTime();

				ProcessMessages(&state);

				if(state.keys & Z_KEY){
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		    	}else {
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				}
				
				UpdateAndRender(&state);

				end = Win32GetTime();
				timeElasped = Win32GetSecondsElapsed(start, end);

				if(timeElasped < TargetSecondsPerFrame){
					sleepMS = (DWORD)((TargetSecondsPerFrame*1000) - (timeElasped*1000));
					Sleep(sleepMS);
				}else{
					OutputDebugString("Missed Frame");
				}


				SwapBuffers(DC);
			}
		}
		else
		{
			error = GetLastError();
		}
	}
	else
	{
		error = GetLastError();
	}

	return 0;
}
//-----------------------------------------------------------------------
// WinMain
//-----------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow)
{
	// Register the window class
	WNDCLASSEX wc = {sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, APPLICATION_NAME, NULL };

	input = new CInputManagerImplementation;
	CInputManager::SetCurrentInputManager(input);
	input->LoadCommandsFromFile("Data\\input.xml");

	RegisterClassEx( &wc );

  	l_D3DDevice = 0;
	l_DeviceContext = 0;
	l_SwapChain = 0;

	// Calcular el tamano de nuestra ventana
	RECT rc = {0, 0, WIDTH_APPLICATION, HEIGHT_APPLICATION};
	AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE);
	
	//width =  rc.right - rc.left;
	//height =  rc.bottom - rc.top;

	// Create the application's window
	HWND hWnd = CreateWindow(	APPLICATION_NAME, APPLICATION_NAME, WS_OVERLAPPEDWINDOW, 100, 100, 800, 600, NULL, NULL, wc.hInstance, NULL );
  	
	// Añadir aquí el Init de la applicacioón
	context.CreateContext(hWnd, WIDTH_APPLICATION, HEIGHT_APPLICATION);

	ShowWindow( hWnd, SW_SHOWDEFAULT );

	context.CreateBackBuffer(hWnd,800,600); 
	context.InitStates();
	CDebugRender debugRender(context.GetDevice());

	CApplication application(&debugRender, &context);
		
	UpdateWindow(hWnd);
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));



  // Añadir en el while la condición de salida del programa de la aplicación
	
	DWORD m_PreviousTime = timeGetTime();
	while( msg.message != WM_QUIT )
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				switch (msg.message)
				{
				case WM_SYSKEYDOWN:
				case WM_SYSKEYUP:
				case WM_KEYDOWN:
				case WM_KEYUP:
					if (!input->KeyEventReceived(msg.wParam, msg.lParam))
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
					break;
				default:
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			else
			{
				input->BeginFrame();
				// Main loop: Añadir aquí el Update y Render de la aplicación principal
				l_CurrentTime = timeGetTime();
				l_ElapsedTime = (float)(l_CurrentTime - l_PreviousTime)*0.001f;
				l_PreviousTime = l_CurrentTime;
				application.Update(l_ElapsedTime);
				application.Render();
				input->EndFrame();
		}

	}

  UnregisterClass( APPLICATION_NAME, wc.hInstance );

  // Añadir una llamada a la alicación para finalizar/liberar memoria de todos sus datos

  return 0;
}
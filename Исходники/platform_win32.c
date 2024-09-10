int 
WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
     MSG msg = {0};
     WNDCLASS wc = {0};
     RECT wr;
     unsigned threadNum;

     wr.left   = 0;
     wr.right  = VIEW_WIDTH;
     wr.top    = 0;
     wr.bottom = VIEW_HEIGHT;

     wc.lpfnWndProc = WndProc;
     wc.hInstance   = hInstance;
     wc.lpszClassName = "C8WinClass";

     if (!RegisterClass(&wc))
          return 0;

     AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

     long style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
     /*
     style ^= WS_THICKFRAME;
     style ^= WS_MAXIMIZEBOX;
     */

     CreateWindow(wc.lpszClassName, "C8", style, 0, 0, (SCREEN_WIDTH * 4)+30, (SCREEN_HEIGHT * 4) + 30,
                  0, 0, hInstance, 0);

     freopen("stdout.txt", "w", stdout);
     freopen("stderr.txt", "w", stderr);

     if (!CHIP8_Init(lpCmdLine)) {
          running = false;
          return;
     }

     CHIP8_Reset();

     InitKeymap();

     _beginthread(InterpreterThread, 0, NULL);

     // TODO: formatting?
     while (running)
     {
          PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
          TranslateMessage(&msg);
          DispatchMessage(&msg);

          glClear(GL_COLOR_BUFFER_BIT);

          UpdateDisplay();

          SwapBuffers(dc);
     }

     return 0;
}
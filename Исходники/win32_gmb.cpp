int WinMain(HINSTANCE instance, HINSTANCE previnstance, LPSTR cmdline,
            int cmdshow) {
  win32_gmbdll gmbDLL;
  win32_InitGmbDll(&gmbDLL);
  WNDCLASS tclass = {0};
  tclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  tclass.lpfnWndProc = &gmbWindowProc;
  tclass.hInstance = 0;
  tclass.lpszClassName = "gmb_class_lol";
  tclass.hCursor = LoadCursorA(0, IDC_ARROW);

  ATOM windowClass = RegisterClassA(&tclass);
  if (windowClass == 0) {
    errord((char *)"RegisterClassA");
  }
  HWND window = CreateWindow("gmb_class_lol", "gmb window",
                             WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT,
                             CW_USEDEFAULT, 960, 540, 0, 0, instance, 0);
  if (window == 0) {
    errord((char *)"CreateWindow");
  }
  WIN32WINDOWSIZE size = Win32GetWindowSize(window);
  Win32ResizeWindow(&screenBuffer, size.height, size.width);

// note(caf): use a specific starting address range so we can do some fancy
// stuff in debug mode
#ifdef WIN32_GMB_INTERNAL
  LPVOID StartAddress = (LPVOID)Tibibytes(2);
#else
  LPVOID StartAddress = 0;
#endif
  void *freshmemory = VirtualAlloc(StartAddress, Mibibytes(64),
                                   MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
  if (!freshmemory) {
    errord((char *)"VirtualAlloc permanent mem");
  }
  gmbstate state = {0};
  gmbmemory memory = {0};
  state.memory = &memory;
  state.memory->permanent = freshmemory;
  state.memory->permanentBytes = Mibibytes(64);
  state.DEBUGPlatformReadEntireFile = &DEBUGPlatformReadEntireFile;
  state.DEBUGPlatformFreeFile = &DEBUGPlatformFreeFile;
  state.DEBUGPlatformWriteEntireFile = &DEBUGPlatformWriteEntireFile;

  MSG msg;
  HDC hdc = GetDC(window);
  int win32ticks = 0;
  LARGE_INTEGER lastpf;
  LARGE_INTEGER curpf;
  LARGE_INTEGER startFrame;
  QueryPerformanceCounter(&curpf);
  lastpf = curpf;
  startFrame = curpf;
  LARGE_INTEGER freq;
  QueryPerformanceFrequency(&freq);
  uint64 elapsed = curpf.QuadPart - lastpf.QuadPart;
  POINT p;
  real32 ms = 0;
  framebuffer fb = {0};
  inputbuffer ib = {0};
  // note(caf): to watch for live reloading our main dll
  uint64 t = GetTickCount64();
  while (running) {
    if (GetTickCount64() - 1000 > t) {
      t = GetTickCount64();
      DWORD att;
      att = GetFileAttributesA("\\build\\gmb.dll");
      if (att != INVALID_FILE_ATTRIBUTES) {
        HANDLE DllHandle;
        DllHandle = CreateFileA("\\build\\gmb.dll", 0, FILE_SHARE_WRITE, 0,
                                OPEN_EXISTING, 0, 0);
        if (DllHandle == INVALID_HANDLE_VALUE) {
          // TODO(caf): handle errors
        }
        FILETIME DllTime;
        GetFileTime(DllHandle, 0, 0, &DllTime);
        CloseHandle(DllHandle);
        if (DllTime.dwHighDateTime != gmbDLL.lastCreationDate.dwHighDateTime ||
            DllTime.dwLowDateTime != gmbDLL.lastCreationDate.dwLowDateTime) {
          // it existed and was newer, so unload our current copy and load the
          // new one
          win32_UnloadGmbDll(&gmbDLL);
          win32_InitGmbDll(&gmbDLL);
          // TODO(caf): use a lockfile to avoid the race condition of compiler
          // creating file but buffer not flushed when we try to load it
        }
      }
    }
    QueryPerformanceCounter(&startFrame);
    while (PeekMessageA(&msg, window, 0, 0, PM_REMOVE)) {
      if (msg.message == WM_QUIT || msg.message == WM_CLOSE) {
        running = false;
      }
      if (msg.message == WM_KEYDOWN) {
        switch (msg.wParam) {
        case VK_RETURN:
          ib.enter.endedDown = true;
          break;
        case VK_SPACE:
          ib.space.endedDown = true;
          break;
        case VK_DOWN:
          ib.down.endedDown = true;
          break;
        case VK_UP:
          ib.up.endedDown = true;
          break;
        case VK_LEFT:
          ib.left.endedDown = true;
          break;
        case VK_RIGHT:
          ib.right.endedDown = true;
          break;
        default:
          break;
        }
      }
      TranslateMessage(&msg);
      DispatchMessageA(&msg);
    }
    fb.height = screenBuffer.height;
    fb.width = screenBuffer.width;
    fb.stride = 4;
    fb.pixels = screenBuffer.buf;
    GetCursorPos(&p);
    ScreenToClient(window, &p); // takes care of window/cursor offsets
    ib.mousex = p.x;
    ib.mousey = p.y;
    QueryPerformanceCounter(&curpf);
    elapsed = curpf.QuadPart - lastpf.QuadPart;
    lastpf = curpf;
    ms = (real32)((real32)elapsed / (real32)freq.QuadPart) * 1000;
    gmbDLL.gmbMainLoop(&state, &fb, &ib, ms); //(elapsed / freq.QuadPart));
    WIN32WINDOWSIZE size = Win32GetWindowSize(window);
    Win32BlitScreen(hdc, &screenBuffer, size.height, size.width);
    ++win32ticks;
    // QueryPerformanceCounter(&curpf);
    elapsed = curpf.QuadPart - startFrame.QuadPart;
    ms = (real32)((real32)elapsed / (real32)freq.QuadPart) * 1000;
    int msToSleep = int(targetMS) - (int)ms; // intentionally truncating to int
    if (msToSleep > 0) {
      Sleep(msToSleep);
    }
    while (ms < targetMS && ms > 0) {
      QueryPerformanceCounter(&curpf);
      elapsed = curpf.QuadPart - startFrame.QuadPart;
      ms = (real32)((real32)elapsed / (real32)freq.QuadPart) * 1000;
      Sleep(0); // do nothing sleep
    }
    ib = {0};
    // Win32DebugDrawFrameTime(hdc, ms, win32ticks);
  }
  win32_UnloadGmbDll(&gmbDLL);
  return 0;
}
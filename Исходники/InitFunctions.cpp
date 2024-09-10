//
//  FUNCTION: InitInstance()
//
//  PURPOSE: creates main window
//
//  COMMENTS:
//
//    In this function, we create and display the main program window.
//
BOOL InitInstance()
{
  extern bool CommandResolution;
  if(!IsEmbedded() && !CommandResolution) {
      ScreenSizeX = 800;
      ScreenSizeY = 480;
  }

#if defined(ENABLE_SDL) && defined(USE_FULLSCREEN)
 #if (SDL_MAJOR_VERSION >= 2)
  SDL_DisplayMode mode = {};
  if(SDL_GetCurrentDisplayMode(0, &mode) == 0) {
	ScreenSizeX = mode.w;
    ScreenSizeY = mode.h;
  } else {
	fprintf(stderr, "SDL_GetCurrentDisplayMode() has failed: %s\n", ::SDL_GetError());
  }
  #else
	ScreenSizeX = 0;
    ScreenSizeY = 0;
  #endif
#endif

  PreloadInitialisation(true);

  RECT WindowSize;

#ifdef __linux__
#ifdef USE_VIDEOCORE
  uint32_t iWidth, iHeight;
  if(graphics_get_display_size(0, &iWidth, &iHeight) >= 0) {
    ScreenSizeX=iWidth;
    ScreenSizeY=iHeight;
  }
#endif
#ifdef ANDROID
  const PixelSize Size = native_view->GetSize();
  ScreenSizeX=Size.cx;
  ScreenSizeY=Size.cy;
#endif


  WindowSize=WindowResize(ScreenSizeX, ScreenSizeY);
#endif
#ifdef WIN32
#if defined(UNDER_CE) || defined(USE_FULLSCREEN)
  WindowSize=WindowResize( GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
#else
  WindowSize=WindowResize(ScreenSizeX, ScreenSizeY);
#endif
#endif

  #if TESTBENCH
  StartupStore(TEXT(". Create main window%s"),NEWLINE);
  #endif

  if(!MainWindow.Create(WindowSize)) {
      StartupStore(TEXT(". FAILURE: Create main window%s"),NEWLINE);
      return FALSE;
  }
  const PixelRect rc(MainWindow.GetClientRect());
  ScreenSizeX = rc.GetSize().cx;
  ScreenSizeY = rc.GetSize().cy;
  ScreenHasChanged();

  InitLKScreen();
  InitLKFonts(); // causing problems with CreateButtonLabels?

  LKLoadFixedBitmaps();
  LKLoadProfileBitmaps();
  LKObjects_Create();

  ButtonLabel::CreateButtonLabels(rc);
  ButtonLabel::SetFont(MapWindowBoldFont);

  Message::Initialize(rc); // creates window, sets fonts

  MainWindow.SetVisible(true);

  return TRUE;
}
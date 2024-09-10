LONG WINAPI ScreenSaverProc(HWND hwnd_in,UINT message,WPARAM wparam,LPARAM lparam)
{

  RECT            r;
  int             key;
  float           delta_x, delta_y;
  POINT           p;

  // Handles screen saver messages
  switch(message)
  {
  case WM_SIZE:
    width = LOWORD(lparam);  // width of client area
    height = HIWORD(lparam); // height of client area
    if (wparam == SIZE_MAXIMIZED) {
      IniIntSet ("WindowMaximized", 1);
    } else {
      IniIntSet ("WindowWidth", width);
      IniIntSet ("WindowHeight", height);
      IniIntSet ("WindowMaximized", 0);
    }
    RenderResize ();
    break;
  case WM_KEYDOWN:
    key = (int) wparam;
    if (key == 'R')
      WorldReset ();
    else if (key == 'W')
      RenderWireframeToggle ();
    else if (key == 'E')
      RenderEffectCycle ();
    else if (key == 'L')
      RenderLetterboxToggle ();
    else if (key == 'F')
      RenderFPSToggle ();
    else if (key == 'G')
      RenderFogToggle ();
    else if (key == 'T')
      RenderFlatToggle ();
    else if (key == VK_F1)
      RenderHelpToggle ();
    else if (key == VK_ESCAPE)
      break;
    else if (!SCREENSAVER) {
      //Dev mode keys
      if (key == 'C')
        CameraAutoToggle ();
      if (key == 'B')
        CameraNextBehavior ();
      if (key == VK_F5)
        CameraReset ();
      if (key == VK_UP)
        CameraMedial (1.0f);
      if (key == VK_DOWN)
        CameraMedial (-1.0f);
      if (key == VK_LEFT)
        CameraLateral (1.0f);
      if (key == VK_RIGHT)
        CameraLateral (-1.0f);
      if (key == VK_PRIOR)
        CameraVertical (1.0f);
      if (key == VK_NEXT)
        CameraVertical (-1.0f);
      if (key == VK_F5)
        CameraReset ();
      return 0;
    } else
      break;
    return 0;
  case WM_MOVE:
    GetClientRect (hwnd, &r);
    height = r.bottom - r.top;
    width = r.right - r.left;
    IniIntSet ("WindowX", r.left);
    IniIntSet ("WindowY", r.top);
    IniIntSet ("WindowWidth", width);
    IniIntSet ("WindowHeight", height);
    half_width = width / 2;
    half_height = height / 2;
    return 0;
  case WM_LBUTTONDOWN:
    lmb = true;
    SetCapture (hwnd);
    break;
  case WM_RBUTTONDOWN:
    rmb = true;
    SetCapture (hwnd);
    break;
  case WM_LBUTTONUP:
    lmb = false;
    if (!rmb) {
      ReleaseCapture ();
      MoveCursor (select_pos.x, select_pos.y);
    }
    break;
  case WM_RBUTTONUP:
    rmb = false;
    if (!lmb) {
      ReleaseCapture ();
      MoveCursor (select_pos.x, select_pos.y);
    }
    break;
  case WM_MOUSEMOVE:
    p.x = LOWORD(lparam);  // horizontal position of cursor
    p.y = HIWORD(lparam);  // vertical position of cursor
    if (p.x < 0 || p.x > width)
      break;
    if (p.y < 0 || p.y > height)
      break;
    if (!mouse_forced && !lmb && !rmb) {
      select_pos = p;
    }
    if (mouse_forced) {
      mouse_forced = false;
    } else if (rmb || lmb) {
      CenterCursor ();
      delta_x = (float)(mouse_pos.x - p.x) * MOUSE_MOVEMENT;
      delta_y = (float)(mouse_pos.y - p.y) * MOUSE_MOVEMENT;
      if (rmb && lmb) {
        GLvector    pos;
        CameraPan (delta_x);
        pos = CameraPosition ();
        pos.y += delta_y;
        CameraPositionSet (pos);
      } else if (rmb) {
        CameraPan (delta_x);
        CameraForward (delta_y);
      } else if (lmb) {
        GLvector    angle;
        angle = CameraAngle ();
        angle.y -= delta_x;
        angle.x += delta_y;
        CameraAngleSet (angle);
      }
    }
    mouse_pos = p;
    break;
  case WM_CREATE:
    hwnd = hwnd_in;
    if (SCREENSAVER)
      AppInit ();
    SetTimer (hwnd, 1, 7, NULL);
    return 0;
  case WM_TIMER:
    AppUpdate ();
    return 0;
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  }
#if SCREENSAVER
  return DefScreenSaverProc(hwnd_in,message,wparam,lparam);
#else
  return DefWindowProc (hwnd_in,message,wparam,lparam);
#endif

}
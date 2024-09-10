LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  int wmId, wmEvent;
  PAINTSTRUCT ps;
  HDC hdc;

  switch (message) 
  {
  case WM_COMMAND:
    wmId    = LOWORD(wParam); 
    wmEvent = HIWORD(wParam); 
    // Parse the menu selections:
    switch (wmId)
    {
    case IDM_CONNECT:
      DialogBox(g_hInst, (LPCTSTR)IDD_NATNET, hWnd, (DLGPROC)NatNetDlgProc);
      break;
    case IDM_EXIT:
      DestroyWindow(hWnd);
      break;
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
    }
    break;
  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);
    wglMakeCurrent(hdc, g_hRenderContext);
    Render();
    SwapBuffers(hdc);
    wglMakeCurrent(0, 0);
    EndPaint(hWnd, &ps);
    break;
  case WM_SIZE:
    {
    int cx = LOWORD(lParam), cy = HIWORD(lParam);
    if(cx==0 || cy ==0 || hWnd==NULL)
      break;

    GLfloat fFovy  = 40.0f; // Field-of-view
    GLfloat fZNear = 1.0f;  // Near clipping plane
    GLfloat fZFar = 10000.0f;  // Far clipping plane

    HDC hDC = GetDC(hWnd);
    wglMakeCurrent(hDC, g_hRenderContext);

    // Calculate viewport aspect
    RECT rv;
    GetClientRect(hWnd, &rv);
    GLfloat fAspect = (GLfloat)(rv.right-rv.left) / (GLfloat)(rv.bottom-rv.top);

    // Define viewport
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fFovy, fAspect, fZNear, fZFar);
    glViewport(rv.left, rv.top, rv.right-rv.left, rv.bottom-rv.top);
    glMatrixMode(GL_MODELVIEW);

    wglMakeCurrent(0, 0);
    ReleaseDC(hWnd, hDC);
    }
    break;
  case WM_DESTROY:
    {
    HDC hDC = GetDC(hWnd);
    wglMakeCurrent(hDC, g_hRenderContext);
  	natnetClient.Uninitialize();
    wglMakeCurrent(0, 0);
    wglDeleteContext(g_hRenderContext);
    ReleaseDC(hWnd, hDC);
    PostQuitMessage(0);
    }
    break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}
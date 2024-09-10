LRESULT CALLBACK
window_proc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  GstGLWindowWin32 *window_win32;
  LRESULT ret = 0;

  if (uMsg == WM_CREATE) {
    window_win32 =
        GST_GL_WINDOW_WIN32 (((LPCREATESTRUCT) lParam)->lpCreateParams);

    GST_TRACE ("WM_CREATE");

    window_win32->device = GetDC (hWnd);
    /* Do this, otherwise we hang on exit. We can still use it (due to the
     * CS_OWNDC flag in the WindowClass) after we have Released.
     */
    ReleaseDC (hWnd, window_win32->device);

    SetProp (hWnd, "gl_window", window_win32);
  } else if (GetProp (hWnd, "gl_window")) {
    GstGLWindow *window;
    GstGLContext *context;
    GstGLContextClass *context_class;

    window_win32 = GST_GL_WINDOW_WIN32 (GetProp (hWnd, "gl_window"));
    window = GST_GL_WINDOW (window_win32);
    context = gst_gl_window_get_context (window);
    context_class = GST_GL_CONTEXT_GET_CLASS (context);

    g_assert (window_win32->internal_win_id == hWnd);

    switch (uMsg) {
      case WM_SIZE:
      {
        if (window->resize) {
          window->resize (window->resize_data, LOWORD (lParam),
              HIWORD (lParam));
        }
        break;
      }
      case WM_PAINT:
      {
        if (window->draw) {
          PAINTSTRUCT ps;
          BeginPaint (hWnd, &ps);
          window->draw (window->draw_data);
          context_class->swap_buffers (context);
          EndPaint (hWnd, &ps);
        }
        break;
      }
      case WM_CLOSE:
      {
        ShowWindowAsync (window_win32->internal_win_id, SW_HIDE);

        GST_TRACE ("WM_CLOSE");

        if (window->close)
          window->close (window->close_data);
        break;
      }
      case WM_CAPTURECHANGED:
      {
        GST_DEBUG ("WM_CAPTURECHANGED");
        if (window->draw)
          window->draw (window->draw_data);
        break;
      }
      case WM_ERASEBKGND:
      {
        ret = TRUE;
        break;
      }
      default:
      {
        /* transmit messages to the parrent (ex: mouse/keyboard input) */
        HWND parent_id = window_win32->parent_win_id;
        if (parent_id)
          PostMessage (parent_id, uMsg, wParam, lParam);
        ret = DefWindowProc (hWnd, uMsg, wParam, lParam);
      }
    }

    gst_object_unref (context);
  } else {
    ret = DefWindowProc (hWnd, uMsg, wParam, lParam);
  }

  return ret;
}
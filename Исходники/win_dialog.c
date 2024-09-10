/* Text log window callback. */
static LRESULT CALLBACK wlog_text_log_callback(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   CREATESTRUCT* create_struct;

   ALLEGRO_NATIVE_DIALOG* textlog = (ALLEGRO_NATIVE_DIALOG*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

   switch (uMsg) {
      case WM_CTLCOLORSTATIC:
         /* Set colors for text and background */
         SetBkColor((HDC)wParam, RGB(16, 16, 16));
         SetTextColor((HDC)wParam, RGB(128, 255, 128));
         return (LRESULT)CreateSolidBrush(RGB(16, 16, 16));

      case WM_CREATE:
         /* Set user data for window, so we will be able to retieve text log structure any time */
         create_struct = (CREATESTRUCT*)lParam;
         SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)create_struct->lpCreateParams);
         break;

      case WM_CLOSE:
         if (textlog->is_active) {
            if (!(textlog->flags & ALLEGRO_TEXTLOG_NO_CLOSE)) {
               wlog_emit_close_event(textlog, false);
            }
            return 0;
         }
         break;

      case WM_DESTROY:
         PostQuitMessage(0);
         break;

      case WM_KEYDOWN:
         if (wParam == VK_ESCAPE) {
            wlog_emit_close_event(textlog, true);
         }

         break;

      case WM_MOVE:
         InvalidateRect(hWnd, NULL, FALSE);
         break;

      case WM_SIZE:
         /* Match text log size to parent client area */
         if (wParam == SIZE_RESTORED || wParam == SIZE_MAXIMIZED) {
            RECT client_rect;
            GetClientRect(hWnd, &client_rect);
            MoveWindow(textlog->tl_textview, client_rect.left, client_rect.top,
               client_rect.right - client_rect.left, client_rect.bottom - client_rect.top, TRUE);
         }
         break;

      case WM_USER:
         al_lock_mutex(textlog->tl_text_mutex);
         wlog_do_append_native_text_log(textlog);
         al_unlock_mutex(textlog->tl_text_mutex);
         break;
   }

   return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
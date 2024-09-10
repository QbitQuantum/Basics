void
_ecore_win32_event_handle_configure_notify(Ecore_Win32_Callback_Data *msg)
{
   WINDOWINFO                          wi;
   Ecore_Win32_Event_Window_Configure *e;
   WINDOWPOS                          *window_pos;

   INF("window configure notify");

   e = calloc(1, sizeof(Ecore_Win32_Event_Window_Configure));
   if (!e) return;

   window_pos = (WINDOWPOS *)msg->data_param;
   wi.cbSize = sizeof(WINDOWINFO);
   if (!GetWindowInfo(window_pos->hwnd, &wi))
     {
        free(e);
        return;
     }

   e->window = (void *)GetWindowLongPtr(msg->window, GWLP_USERDATA);
   e->abovewin = (void *)GetWindowLongPtr(window_pos->hwndInsertAfter, GWLP_USERDATA);
   e->x = wi.rcClient.left;
   e->y = wi.rcClient.top;
   e->width = wi.rcClient.right - wi.rcClient.left;
   e->height = wi.rcClient.bottom - wi.rcClient.top;
   e->timestamp = _ecore_win32_event_last_time;

   ecore_event_add(ECORE_WIN32_EVENT_WINDOW_CONFIGURE, e, NULL, NULL);
}
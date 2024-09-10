LRESULT CALLBACK win_proc(HWND win, UINT message, WPARAM w_param, 
                          LPARAM l_param)
{
  DEV_BROADCAST_HDR *hdr = (DEV_BROADCAST_HDR *) l_param;

  switch(message) 
    {
    case WM_DESTROY:
      if(notification_handle_hub)
        UnregisterDeviceNotification(notification_handle_hub);
      if(notification_handle_dev)
        UnregisterDeviceNotification(notification_handle_dev);

      PostQuitMessage(0);
      break;

    case WM_SIZE:
      on_size(LOWORD(l_param), HIWORD(l_param));
      break;

    case WM_COMMAND:
      switch(LOWORD(w_param))
        {
        case ID_EXIT:
          PostQuitMessage(0);
          break;
        case ID_REFRESH:
          on_refresh();
          break;
        default:
          return DefWindowProc(win, message, w_param, l_param );
        }
      break;

    case WM_DEVICECHANGE:
      switch(w_param)
        {
        case DBT_DEVICEREMOVECOMPLETE:
          if(hdr->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE) 
            on_refresh();
          break;
        case DBT_DEVICEARRIVAL:
          if(hdr->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
            on_refresh();
          break;
        default:
          ;
        }
      break;

    default:
      return DefWindowProc(win, message, w_param, l_param);
    }

  return 0;
}
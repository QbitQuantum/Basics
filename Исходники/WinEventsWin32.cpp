LRESULT CALLBACK CWinEventsWin32::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  XBMC_Event newEvent;
  ZeroMemory(&newEvent, sizeof(newEvent));
  static HDEVNOTIFY hDeviceNotify;

  if (uMsg == WM_CREATE)
  {
    SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG)(((LPCREATESTRUCT)lParam)->lpCreateParams));
    DIB_InitOSKeymap();
    g_uQueryCancelAutoPlay = RegisterWindowMessage(TEXT("QueryCancelAutoPlay"));
    shcne.pidl = NULL;
    shcne.fRecursive = TRUE;
    long fEvents = SHCNE_DRIVEADD | SHCNE_DRIVEREMOVED | SHCNE_MEDIAREMOVED | SHCNE_MEDIAINSERTED;
    SHChangeNotifyRegister(hWnd, SHCNRF_ShellLevel | SHCNRF_NewDelivery, fEvents, WM_MEDIA_CHANGE, 1, &shcne);
    RegisterDeviceInterfaceToHwnd(USB_HID_GUID, hWnd, &hDeviceNotify);
    return 0;
  }

  m_pEventFunc = (PHANDLE_EVENT_FUNC)GetWindowLongPtr(hWnd, GWLP_USERDATA);
  if (!m_pEventFunc)
    return DefWindowProc(hWnd, uMsg, wParam, lParam);

  if(g_uQueryCancelAutoPlay != 0 && uMsg == g_uQueryCancelAutoPlay)
    return S_FALSE;

  switch (uMsg)
  {
    case WM_CLOSE:
    case WM_QUIT:
    case WM_DESTROY:
      newEvent.type = XBMC_QUIT;
      m_pEventFunc(newEvent);
      break;
    case WM_SHOWWINDOW:
      {
        bool active = g_application.m_AppActive;
        g_application.m_AppActive = wParam != 0;
        if (g_application.m_AppActive != active)
          g_Windowing.NotifyAppActiveChange(g_application.m_AppActive);
        CLog::Log(LOGDEBUG, __FUNCTION__"Window is %s", g_application.m_AppActive ? "shown" : "hidden");
      }
      break;
    case WM_ACTIVATE:
      {
        bool active = g_application.m_AppActive;
        if (HIWORD(wParam))
        {
          g_application.m_AppActive = false;
        }
        else
        {
          WINDOWPLACEMENT lpwndpl;
          lpwndpl.length = sizeof(lpwndpl);
          if (LOWORD(wParam) != WA_INACTIVE)
          {
            if (GetWindowPlacement(hWnd, &lpwndpl))
              g_application.m_AppActive = lpwndpl.showCmd != SW_HIDE;
          }
          else
          {
            g_application.m_AppActive = g_Windowing.WindowedMode();
          }
        }
        if (g_application.m_AppActive != active)
          g_Windowing.NotifyAppActiveChange(g_application.m_AppActive);
        CLog::Log(LOGDEBUG, __FUNCTION__"Window is %s", g_application.m_AppActive ? "active" : "inactive");
      }
      break;
    case WM_SETFOCUS:
    case WM_KILLFOCUS:
      g_application.m_AppFocused = uMsg == WM_SETFOCUS;
      g_Windowing.NotifyAppFocusChange(g_application.m_AppFocused);
      if (uMsg == WM_KILLFOCUS)
      {
        CStdString procfile;
        if (CWIN32Util::GetFocussedProcess(procfile))
          CLog::Log(LOGDEBUG, __FUNCTION__": Focus switched to process %s", procfile.c_str());
      }
      break;
    case WM_SYSKEYDOWN:
      switch (wParam)
      {
        case VK_F4: //alt-f4, default event quit.
          return(DefWindowProc(hWnd, uMsg, wParam, lParam));
        case VK_RETURN: //alt-return
          if ((lParam & REPEATED_KEYMASK) == 0)
            g_graphicsContext.ToggleFullScreenRoot();
          return 0;
      }
      //deliberate fallthrough
    case WM_KEYDOWN:
    {
      switch (wParam)
      {
        case VK_CONTROL:
          if ( lParam & EXTENDED_KEYMASK )
            wParam = VK_RCONTROL;
          else
            wParam = VK_LCONTROL;
          break;
        case VK_SHIFT:
          /* EXTENDED trick doesn't work here */
          if (GetKeyState(VK_LSHIFT) & 0x8000)
            wParam = VK_LSHIFT;
          else if (GetKeyState(VK_RSHIFT) & 0x8000)
            wParam = VK_RSHIFT;
          break;
        case VK_MENU:
          if ( lParam & EXTENDED_KEYMASK )
            wParam = VK_RMENU;
          else
            wParam = VK_LMENU;
          break;
      }
      XBMC_keysym keysym;
      TranslateKey(wParam, HIWORD(lParam), &keysym, 1);

      newEvent.type = XBMC_KEYDOWN;
      newEvent.key.keysym = keysym;
      m_pEventFunc(newEvent);
    }
    return(0);

    case WM_SYSKEYUP:
    case WM_KEYUP:
      {
      switch (wParam)
      {
        case VK_CONTROL:
          if ( lParam&EXTENDED_KEYMASK )
            wParam = VK_RCONTROL;
          else
            wParam = VK_LCONTROL;
          break;
        case VK_SHIFT:
          {
            uint32_t scanCodeL = MapVirtualKey(VK_LSHIFT, MAPVK_VK_TO_VSC);
            uint32_t scanCodeR = MapVirtualKey(VK_RSHIFT, MAPVK_VK_TO_VSC);
            uint32_t keyCode = (uint32_t)((lParam & 0xFF0000) >> 16);
            if (keyCode == scanCodeL)
              wParam = VK_LSHIFT;
            else if (keyCode == scanCodeR)
              wParam = VK_RSHIFT;
          }
          break;
        case VK_MENU:
          if ( lParam&EXTENDED_KEYMASK )
            wParam = VK_RMENU;
          else
            wParam = VK_LMENU;
          break;
      }
      XBMC_keysym keysym;
      TranslateKey(wParam, HIWORD(lParam), &keysym, 1);

      if (wParam == VK_SNAPSHOT)
        newEvent.type = XBMC_KEYDOWN;
      else
        newEvent.type = XBMC_KEYUP;
      newEvent.key.keysym = keysym;
      m_pEventFunc(newEvent);
    }
    return(0);
    case WM_APPCOMMAND: // MULTIMEDIA keys are mapped to APPCOMMANDS
    {
      CLog::Log(LOGDEBUG, "WinEventsWin32.cpp: APPCOMMAND %d", GET_APPCOMMAND_LPARAM(lParam));
      newEvent.appcommand.type = XBMC_APPCOMMAND;
      newEvent.appcommand.action = GET_APPCOMMAND_LPARAM(lParam);
      if (m_pEventFunc(newEvent))
        return TRUE;
      else
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    case WM_GESTURENOTIFY:
    {
      OnGestureNotify(hWnd, lParam);
      return DefWindowProc(hWnd, WM_GESTURENOTIFY, wParam, lParam);
    }
    case WM_GESTURE:
    {
      OnGesture(hWnd, lParam);
      return 0;
    }
    case WM_SYSCHAR:
      if (wParam == VK_RETURN) //stop system beep on alt-return
        return 0;
      break;
    case WM_SETCURSOR:
      if (HTCLIENT != LOWORD(lParam))
        g_Windowing.ShowOSMouse(true);
      break;
    case WM_MOUSEMOVE:
      newEvent.type = XBMC_MOUSEMOTION;
      newEvent.motion.x = GET_X_LPARAM(lParam);
      newEvent.motion.y = GET_Y_LPARAM(lParam);
      newEvent.motion.state = 0;
      m_pEventFunc(newEvent);
      return(0);
    case WM_LBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_RBUTTONDOWN:
      newEvent.type = XBMC_MOUSEBUTTONDOWN;
      newEvent.button.state = XBMC_PRESSED;
      newEvent.button.x = GET_X_LPARAM(lParam);
      newEvent.button.y = GET_Y_LPARAM(lParam);
      newEvent.button.button = 0;
      if (uMsg == WM_LBUTTONDOWN) newEvent.button.button = XBMC_BUTTON_LEFT;
      else if (uMsg == WM_MBUTTONDOWN) newEvent.button.button = XBMC_BUTTON_MIDDLE;
      else if (uMsg == WM_RBUTTONDOWN) newEvent.button.button = XBMC_BUTTON_RIGHT;
      m_pEventFunc(newEvent);
      return(0);
    case WM_LBUTTONUP:
    case WM_MBUTTONUP:
    case WM_RBUTTONUP:
      newEvent.type = XBMC_MOUSEBUTTONUP;
      newEvent.button.state = XBMC_RELEASED;
      newEvent.button.x = GET_X_LPARAM(lParam);
      newEvent.button.y = GET_Y_LPARAM(lParam);
      newEvent.button.button = 0;
      if (uMsg == WM_LBUTTONUP) newEvent.button.button = XBMC_BUTTON_LEFT;
      else if (uMsg == WM_MBUTTONUP) newEvent.button.button = XBMC_BUTTON_MIDDLE;
      else if (uMsg == WM_RBUTTONUP) newEvent.button.button = XBMC_BUTTON_RIGHT;
      m_pEventFunc(newEvent);
      return(0);
    case WM_MOUSEWHEEL:
      {
        // SDL, which our events system is based off, sends a MOUSEBUTTONDOWN message
        // followed by a MOUSEBUTTONUP message.  As this is a momentary event, we just
        // react on the MOUSEBUTTONUP message, resetting the state after processing.
        newEvent.type = XBMC_MOUSEBUTTONDOWN;
        newEvent.button.state = XBMC_PRESSED;
        // the coordinates in WM_MOUSEWHEEL are screen, not client coordinates
        POINT point;
        point.x = GET_X_LPARAM(lParam);
        point.y = GET_Y_LPARAM(lParam);
        WindowFromScreenCoords(hWnd, &point);
        newEvent.button.x = (uint16_t)point.x;
        newEvent.button.y = (uint16_t)point.y;
        newEvent.button.button = GET_Y_LPARAM(wParam) > 0 ? XBMC_BUTTON_WHEELUP : XBMC_BUTTON_WHEELDOWN;
        m_pEventFunc(newEvent);
        newEvent.type = XBMC_MOUSEBUTTONUP;
        newEvent.button.state = XBMC_RELEASED;
        m_pEventFunc(newEvent);
      }
      return(0);
    case WM_SIZE:
      newEvent.type = XBMC_VIDEORESIZE;
      newEvent.resize.type = XBMC_VIDEORESIZE;
      newEvent.resize.w = GET_X_LPARAM(lParam);
      newEvent.resize.h = GET_Y_LPARAM(lParam);
      if (newEvent.resize.w * newEvent.resize.h)
        m_pEventFunc(newEvent);
      return(0);
    case WM_MEDIA_CHANGE:
      {
        // There may be multiple notifications for one event
        // There are also a few events we're not interested in, but they cause no harm
        // For example SD card reader insertion/removal
        long lEvent;
        PIDLIST_ABSOLUTE *ppidl;
        HANDLE hLock = SHChangeNotification_Lock((HANDLE)wParam, (DWORD)lParam, &ppidl, &lEvent);

        if (hLock)
        {
          char drivePath[MAX_PATH+1];
          if (!SHGetPathFromIDList(ppidl[0], drivePath))
            break;

          switch(lEvent)
          {
            case SHCNE_DRIVEADD:
            case SHCNE_MEDIAINSERTED:
              CLog::Log(LOGDEBUG, __FUNCTION__": Drive %s Media has arrived.", drivePath);
              if (GetDriveType(drivePath) == DRIVE_CDROM)
                g_application.getApplicationMessenger().OpticalMount(drivePath, true);
              else
                CWin32StorageProvider::SetEvent();
              break;

            case SHCNE_DRIVEREMOVED:
            case SHCNE_MEDIAREMOVED:
              CLog::Log(LOGDEBUG, __FUNCTION__": Drive %s Media was removed.", drivePath);
              if (GetDriveType(drivePath) == DRIVE_CDROM)
                g_application.getApplicationMessenger().OpticalUnMount(drivePath);
              else
                CWin32StorageProvider::SetEvent();
              break;
          }
          SHChangeNotification_Unlock(hLock);
        }
        break;
      }
    case WM_POWERBROADCAST:
      if (wParam==PBT_APMSUSPEND)
      {
        CLog::Log(LOGDEBUG,"WM_POWERBROADCAST: PBT_APMSUSPEND event was sent");
        CWin32PowerSyscall::SetOnSuspend();
      }
      else if(wParam==PBT_APMRESUMEAUTOMATIC)
      {
        CLog::Log(LOGDEBUG,"WM_POWERBROADCAST: PBT_APMRESUMEAUTOMATIC event was sent");
        CWin32PowerSyscall::SetOnResume();
      }
      break;
    case WM_DEVICECHANGE:
      {
        PDEV_BROADCAST_DEVICEINTERFACE b = (PDEV_BROADCAST_DEVICEINTERFACE) lParam;
        CStdString dbcc_name(b->dbcc_name);
        dbcc_name = CKeymapLoader::ParseWin32HIDName(b->dbcc_name);
        switch (wParam)
        {
          case DBT_DEVICEARRIVAL:
            CKeymapLoader().DeviceAdded(dbcc_name);
            break;
          case DBT_DEVICEREMOVECOMPLETE:
            CKeymapLoader().DeviceRemoved(dbcc_name);
            break;
          case DBT_DEVNODES_CHANGED:
            //CLog::Log(LOGDEBUG, "HID Device Changed");
            //We generally don't care about Change notifications, only need to know if a device is removed or added to rescan the device list
            break;
        }
        break;
      }
    case WM_PAINT:
      //some other app has painted over our window, mark everything as dirty
      g_windowManager.MarkDirty();
      break;
  }
  return(DefWindowProc(hWnd, uMsg, wParam, lParam));
}
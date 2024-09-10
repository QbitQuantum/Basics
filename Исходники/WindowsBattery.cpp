void
EnableBatteryNotifications()
{
#if MOZ_WINSDK_TARGETVER >= MOZ_NTDDI_LONGHORN
  if (IsVistaOrLater()) {
    // RegisterPowerSettingNotification is from Vista or later.
    // Use this API if available.
    HMODULE hUser32 = GetModuleHandleW(L"USER32.DLL");
    if (!sRegisterPowerSettingNotification)
      sRegisterPowerSettingNotification = (REGISTERPOWERSETTINGNOTIFICATION)
        GetProcAddress(hUser32, "RegisterPowerSettingNotification");
    if (!sUnregisterPowerSettingNotification)
      sUnregisterPowerSettingNotification = (UNREGISTERPOWERSETTINGNOTIFICATION)
        GetProcAddress(hUser32, "UnregisterPowerSettingNotification");

    if (!sRegisterPowerSettingNotification ||
        !sUnregisterPowerSettingNotification) {
      NS_ASSERTION(false, "Canot find PowerSettingNotification functions.");
      return;
    }

    // Create custom window to watch battery event
    // If we can get Gecko's window handle, this is unnecessary.

    if (sHWnd == nsnull) {
      WNDCLASSW wc;
      HMODULE hSelf = GetModuleHandle(nsnull);

      if (!GetClassInfoW(hSelf, L"MozillaBatteryClass", &wc)) {
        ZeroMemory(&wc, sizeof(WNDCLASSW));
        wc.hInstance = hSelf;
        wc.lpfnWndProc = BatteryWindowProc;
        wc.lpszClassName = L"MozillaBatteryClass";
        RegisterClassW(&wc);
      }

      sHWnd = CreateWindowW(L"MozillaBatteryClass", L"Battery Watcher",
                            0, 0, 0, 0, 0,
                            nsnull, nsnull, hSelf, nsnull);
    }

    if (sHWnd == nsnull) {
      return;
    }

    sPowerHandle =
      sRegisterPowerSettingNotification(sHWnd,
                                        &GUID_ACDC_POWER_SOURCE,
                                        DEVICE_NOTIFY_WINDOW_HANDLE);
    sCapacityHandle =
      sRegisterPowerSettingNotification(sHWnd,
                                        &GUID_BATTERY_PERCENTAGE_REMAINING,
                                        DEVICE_NOTIFY_WINDOW_HANDLE);
  } else
#endif
  {
    // for Windows 2000 and Windwos XP.  If we remove Windows XP support,
    // we should remove timer-based power notification
    sUpdateTimer = do_CreateInstance(NS_TIMER_CONTRACTID);
    if (sUpdateTimer) {
      sUpdateTimer->InitWithFuncCallback(UpdateHandler,
                                         nsnull,
                                         Preferences::GetInt("dom.battery.timer",
                                                             30000 /* 30s */),
                                         nsITimer::TYPE_REPEATING_SLACK);
    } 
  }
}
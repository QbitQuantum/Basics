void InstallService()
// this function is executed, if someone starts our service exe manually
// if our service is installed, we uninstall it and vice versa
{
  CHAR                   arrCh [MAX_PATH + 1];
  SC_HANDLE              c1, c2;
  DWORD                  c3;
  SERVICE_STATUS         ss;
  LPQUERY_SERVICE_CONFIG qsc;
  int                    i1;
  bool                   b1;

  GetModuleFileName(GetModuleHandle(NULL), arrCh, MAX_PATH);
  // first we contact the service control manager
  c1 = OpenSCManagerA(NULL, NULL, SC_MANAGER_ALL_ACCESS);
  if (!c1)
    // didn't work, maybe we asked for too many access rights?
    c1 = OpenSCManagerA(NULL, NULL, 0);
  if (c1) {
    // okay, that worked, now we try to open our service
    c2 = OpenServiceA(c1, CServiceName, SERVICE_ALL_ACCESS | DELETE);
    if (c2) {
      // our service is already installed, let's check the parameters
      b1 = false;
      c3 = 0;
      QueryServiceConfigA(c2, NULL, 0, &c3);
      if (c3) {
        qsc = (LPQUERY_SERVICE_CONFIG) LocalAlloc(LPTR, c3 * 2);
        b1 = (QueryServiceConfigA(c2, qsc, c3 * 2, &c3)) &&
             ( (qsc->dwServiceType != CServiceType ) ||
               (qsc->dwStartType   != CServiceStart) ||
               (lstrcmpiA(qsc->lpDisplayName, CServiceDescr)) );
        LocalFree(qsc);
      }
      if (!ControlService(c2, SERVICE_CONTROL_INTERROGATE, &ss))
        ss.dwCurrentState = SERVICE_STOPPED;
      if ((!b1) && (ss.dwCurrentState == SERVICE_RUNNING)) {
        // the parameters are correct, so we try to stop and remove it
        if (ControlService(c2, SERVICE_CONTROL_STOP, &ss)) {
          if (DeleteService(c2))
               MessageBox(0, "the service is removed again",                "information...", MB_ICONINFORMATION);
          else MessageBox(0, "the service is stopped, but removing failed", "warning...",     MB_ICONWARNING);
        } else
          MessageBox(0, "stopping failed", "warning...", MB_ICONWARNING);
      } else {
        if (b1)
          // not all parameters are correct, so we try to correct them
          if (ChangeServiceConfigA(c2, CServiceType, CServiceStart, SERVICE_ERROR_NORMAL,
                                   arrCh, NULL, NULL, NULL, NULL, NULL, CServiceDescr))
               MessageBox(0, "correction of service parameters succeeded", "information...", MB_ICONINFORMATION);
          else MessageBox(0, "correction of service parameters failed",    "warning...",     MB_ICONWARNING);
        if (ss.dwCurrentState != SERVICE_RUNNING)
          // our service was installed, but not running, so we start it
          if (StartServiceA(c2, 0, NULL))
               MessageBox(0, "the service was restarted", "information...", MB_ICONINFORMATION);
          else MessageBox(0, "restarting failed",         "warning...",     MB_ICONWARNING);
      }
      CloseServiceHandle(c2);
    } else {
      // probably our service is not installed yet, so we do that now
      c2 = CreateServiceA(c1, CServiceName, CServiceDescr,
                          SERVICE_ALL_ACCESS | STANDARD_RIGHTS_ALL,
                          CServiceType, CServiceStart,
                          SERVICE_ERROR_NORMAL, arrCh, NULL, NULL, NULL, NULL, NULL);
      if (c2) {
        // installation went smooth
        // we want to give everyone full access to our service
        if (!AddAccessForEveryone(c2, SERVICE_ALL_ACCESS | DELETE))
          MessageBox(0, "access manipulation didn't work", "warning...", MB_ICONWARNING);
        // now let's start the service
        if (StartServiceA(c2, 0, NULL)) {
          // starting succeeded, but does the service run through?
          // the service tries to create an ipc queue
          // if that fails, it stops and removes itself
          for (i1 = 1; (i1 < 50); i1++) {
            if (!ControlService(c2, SERVICE_CONTROL_INTERROGATE, &ss))
              ss.dwCurrentState = SERVICE_STOPPED;
            if ((ss.dwCurrentState == SERVICE_RUNNING) || (ss.dwCurrentState == SERVICE_STOPPED))
              break;
            Sleep(50);
          }
          if (ss.dwCurrentState == SERVICE_RUNNING)
               MessageBox(0, "the service is installed now",      "information...", MB_ICONINFORMATION);
          else MessageBox(0, "installation failed (ipc failure)", "warning...",     MB_ICONWARNING);
        } else 
          MessageBox(0, "installation succeeded, but starting failed", "warning...", MB_ICONWARNING);
        CloseServiceHandle(c2);
      } else
        MessageBox(0, "you don't have enough privileges", "sorry...", MB_ICONWARNING);
    }
    CloseServiceHandle(c1);
  } else
    MessageBox(0, "you don't have enough privileges", "sorry...", MB_ICONWARNING);
}
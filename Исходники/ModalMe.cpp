int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	try {
  wchar_t* desktop   = L"NewDesktop";

  HDESK hThreadDT = GetThreadDesktop(GetCurrentThreadId());
  HDESK hInputDT  = OpenInputDesktop(0, FALSE, DESKTOP_SWITCHDESKTOP);
  HDESK hNewDT    = CreateDesktop(desktop, NULL, NULL, 0, GENERIC_ALL, NULL);

  SetThreadDesktop(hNewDT);
  SwitchDesktop(hNewDT);

   PROCESS_INFORMATION pi;
    STARTUPINFO si;

    memset(&pi, 0, sizeof(pi));
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    si.lpDesktop = desktop;

	wchar_t cmdline[MAX_PATH];
	wsprintf(cmdline, L"%s %s", L"NAMCredentialWizard.exe", L"/u");
	if (CreateProcess(L"NAMCredentialWizard.exe", cmdline,
		NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {

      WaitForSingleObject(pi.hProcess, INFINITE);
    }
    else {
      wchar_t msg[1000];
      wsprintf(msg,L"CreateProcess failed (%d)",GetLastError());
      MessageBox(NULL,msg,NULL,MB_OK);
    }
  

  SwitchDesktop(hInputDT);
  SetThreadDesktop(hThreadDT);
  CloseDesktop(hNewDT);

  return 0;

	} catch(...)
	{ MessageBox(NULL,L"Caught Exception",NULL,MB_OK);


	}
}
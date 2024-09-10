void CPageConnect::CreateSessionThreadProc()
{
  // Create the AdminSession class object
  IAdminSessionClassPtr spClass;
  HRESULT hr = CoGetClassObject(__uuidof(AdminSession), CLSCTX_LOCAL_SERVER,
    NULL, __uuidof(spClass), (void**)&spClass);
  if (FAILED(hr))
  {
    PostMessage(wm_SessionFailed, hr);
    return;
  }

  // Create an instance of the host object for an IAdminSessionHost interface
  AdminSessionSecureHost    xHost;

  // Create an AdminSession object
  IAdminSessionPtr spSession;
  hr = spClass->CreateSession(&xHost, &spSession);
  ::CoDisconnectObject(&xHost, 0);
  if (FAILED(hr))
  {
    PostMessage(wm_SessionFailed, hr);
    return;
  }

  // Get a reference to the GIT
  IGlobalInterfaceTablePtr spGIT;
  hr = spGIT.CreateInstance(CLSID_StdGlobalInterfaceTable);
  if (FAILED(hr))
  {
    PostMessage(wm_SessionFailed, hr);
    return;
  }

  // Add the Session pointer to the GIT
  DWORD dwCookie = 0;
  hr = spGIT->RegisterInterfaceInGlobal(spSession,
    __uuidof(IAdminSession), &dwCookie);
  if (FAILED(hr))
  {
    PostMessage(wm_SessionFailed, hr);
    return;
  }

  TCHandle shEvent = CreateEvent(NULL, false, false, NULL);
  PostMessage(wm_SessionSucceeded, dwCookie, (LPARAM)shEvent.GetHandle());
  WaitForSingleObject(shEvent, INFINITE);
}
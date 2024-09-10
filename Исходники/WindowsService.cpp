BOOL WindowsService::Remove()
{
  bool  ret_val= false;

  if (! IsInstalled())
    return true;

  // open a connection to the SCM
  SC_HANDLE scm= OpenSCManager(0, 0,SC_MANAGER_CREATE_SERVICE);
  if (! scm)
    return false;

  SC_HANDLE service= OpenService(scm, serviceName, DELETE);
  if (service)
  {
    if (DeleteService(service))
      ret_val= true;
    DWORD dw= ::GetLastError();
    CloseServiceHandle(service);
  }

  CloseServiceHandle(scm);
  return ret_val;
}
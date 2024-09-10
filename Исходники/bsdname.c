/*
 * Get hostname excluding domain-name
 */
int _get_machine_name (char *buf, int size)
{
  int     rc;
  DWORD   sz  = size;
  HMODULE mod = GetModuleHandle ("KERNEL32.DLL");
  BOOL (WINAPI *_GetComputerNameExA) (int, char*, DWORD*) = NULL;
  typedef BOOL (WINAPI *gcn_ex) (int, char*, DWORD*);

  if (mod)
     _GetComputerNameExA = (gcn_ex) GetProcAddress (mod, "GetComputerNameExA");

  if (!_GetComputerNameExA)
       rc = GetComputerNameA (buf, &sz);
  else rc = (*_GetComputerNameExA) (ComputerNameDnsHostname, buf, &sz);

  rc = rc ? 0 : -1;
  TCP_CONSOLE_MSG (2, ("_get_machine_name(): \"%s\", rc %d\n", buf, rc));
  return (rc);
}
static gpointer
find_in_any_module_using_toolhelp (const gchar *symbol_name)
{
  HANDLE snapshot; 
  MODULEENTRY32 me32;

  gpointer p;

  if ((snapshot = CreateToolhelp32Snapshot (TH32CS_SNAPMODULE, 0)) == (HANDLE) -1)
    return NULL;

  me32.dwSize = sizeof (me32);
  p = NULL;
  if (Module32First (snapshot, &me32))
    {
      do {
	if ((p = GetProcAddress (me32.hModule, symbol_name)) != NULL)
	  break;
      } while (Module32Next (snapshot, &me32));
    }

  CloseHandle (snapshot);

  return p;
}
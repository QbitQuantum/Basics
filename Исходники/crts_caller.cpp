crts_caller::crts_caller(const char* func_name)
{
  assert(func_name);
  assert(func_name[0]);
  if (func_name == NULL)
    return;

  for (const std::wstring& crtName : s_crtNames)
  {
    HMODULE hCrt = NULL;
    if (!GetModuleHandleExW(0, crtName.c_str(), &hCrt) || hCrt == NULL) // Flag 0 ensures that CRL will not be unloaded while we are using it here
      continue; // Module not loaded

    void* func_ptr = GetProcAddress(hCrt, func_name);
    if (func_ptr != NULL)
    {
      m_crts.push_back(hCrt);
      m_funcPointers.push_back(func_ptr);
    }
    else
      FreeLibrary(hCrt); // this CRT will not be used
  }
}
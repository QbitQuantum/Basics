HRESULT
Module::Register()
{
  TCHAR module_file_name[MAX_PATH + 1];

  if (0 == GetModuleFileName(m_hModule,
			     module_file_name,
			     sizeof module_file_name / sizeof (TCHAR)))
    return E_FAIL;

  DllUnregisterServer();

  for (int i = 0; i < REG_INFO_SIZE; i++)
    {
      const RegInfo* ri = reg_info + i;

      TCHAR buffer[1024];
      size_t size;
      if (ri->type == REG_DWORD)
	{
	  *(DWORD*)buffer = _ttoi(ri->value);
	  size = sizeof (DWORD);
	}
      else
	{
	  _stprintf(buffer, ri->value, module_file_name);
	  size = _tcslen(buffer) + 1;
	}

      HKEY hkey;
      DWORD disposition;
      LONG stat = RegCreateKeyEx(HKEY_CLASSES_ROOT, ri->reg_key, 0, NULL,
	                         REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
				 NULL, &hkey, &disposition);
      if (stat != ERROR_SUCCESS)
	return E_FAIL;

      stat = RegSetValueEx(hkey, ri->value_name, 0, ri->type, (BYTE*) buffer, size);
      RegCloseKey(hkey);
      if (stat != ERROR_SUCCESS)
	return E_FAIL;
    }

  return S_OK;
}
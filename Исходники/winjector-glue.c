void *
frida_winjector_helper_factory_spawn (const gchar * path, const gchar * parameters, FridaWinjectorPrivilegeLevel level, GError ** error)
{
  HANDLE process_handle;
  SHELLEXECUTEINFOW ei = { 0, };
  WCHAR * path_utf16;
  WCHAR * parameters_utf16;

  CoInitializeEx (NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

  ei.cbSize = sizeof (ei);

  ei.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_NOASYNC | SEE_MASK_FLAG_NO_UI
      | SEE_MASK_UNICODE | SEE_MASK_WAITFORINPUTIDLE;
  if (level == FRIDA_WINJECTOR_PRIVILEGE_LEVEL_ELEVATED)
    ei.lpVerb = L"runas";
  else
    ei.lpVerb = L"open";

  path_utf16 = (WCHAR *) g_utf8_to_utf16 (path, -1, NULL, NULL, NULL);
  ei.lpFile = path_utf16;

  parameters_utf16 =
      (WCHAR *) g_utf8_to_utf16 (parameters, -1, NULL, NULL, NULL);
  ei.lpParameters = parameters_utf16;

  ei.nShow = SW_HIDE;

  if (ShellExecuteExW (&ei))
  {
    process_handle = ei.hProcess;
  }
  else
  {
    process_handle = NULL;

    g_set_error (error,
        FRIDA_ERROR,
        FRIDA_ERROR_PERMISSION_DENIED,
        "Unable to spawn helper executable at '%s': 0x%08lx",
        path, GetLastError ());
  }

  g_free (parameters_utf16);
  g_free (path_utf16);

  CoUninitialize ();

  return process_handle;
}
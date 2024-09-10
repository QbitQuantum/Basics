/** 
 * Opens a shared library.
 *
 * @param[in] portLibrary The port library.
 * @param[in] name path Null-terminated string containing the shared library.
 * @param[out] descriptor Pointer to memory which is filled in with shared-library handle on success.
 * @param[in] decorate Boolean value indicates whether name should be decorated
 *            if it contains path information and cannot be found.
 *
 * @return 0 on success, any other value on failure.
 *
 * @note contents of descriptor are undefined on failure.
 */
UDATA VMCALL
hysl_open_shared_library (struct HyPortLibrary * portLibrary, char *name,
			  UDATA * descriptor, BOOLEAN decorate)
{
  HINSTANCE dllHandle;
  UINT prevMode;
  DWORD error;
  UDATA notFound;
  const char *errorMessage;
  char errBuf[512];
  char mangledName[1024];
  char *openName = name;

  if (decorate)
    {
      portLibrary->str_printf (portLibrary, mangledName, 1024, "%s.dll",
			       name);
      openName = mangledName;
    }				/* TODO make windows not try to append .dll if we do not want it to */

  prevMode = SetErrorMode (SEM_NOOPENFILEERRORBOX | SEM_FAILCRITICALERRORS);

  /* LoadLibrary will try appending .DLL if necessary */
  dllHandle = LoadLibrary ((LPCSTR) openName);
  if (dllHandle >= (HINSTANCE) HINSTANCE_ERROR)
    {
      *descriptor = (UDATA) dllHandle;
      SetErrorMode (prevMode);
      return 0;
    }

  error = GetLastError ();

  notFound = (error == ERROR_MOD_NOT_FOUND || error == ERROR_DLL_NOT_FOUND);
  if (notFound)
    {
      /* try to report a better error message.  Check if the library can be found at all. */
      dllHandle =
	LoadLibraryEx ((LPCSTR) openName, NULL, DONT_RESOLVE_DLL_REFERENCES);
      if (dllHandle)
	{
	  if (sizeof (errBuf))
	    {
	      errorMessage = portLibrary->nls_lookup_message (portLibrary,
							      HYNLS_ERROR |
							      HYNLS_DO_NOT_APPEND_NEWLINE,
							      HYNLS_PORT_SL_UNABLE_TO_RESOLVE_REFERENCES,
							      NULL);
	      strncpy (errBuf, errorMessage, sizeof (errBuf));
	      errBuf[sizeof (errBuf) - 1] = '\0';
	    }
	  FreeLibrary (dllHandle);
	  SetErrorMode (prevMode);
	  return portLibrary->error_set_last_error_with_message (portLibrary,
								 HYPORT_SL_INVALID,
								 errBuf);
	}
    }

  if (sizeof (errBuf))
    {
      LPWSTR message = NULL;
      int nameSize = strlen (name);
      LPWSTR filename =
	(LPWSTR) portLibrary->mem_allocate_memory (portLibrary,
						   nameSize * 2 + 2);

      if (filename == NULL)
	{
	  errorMessage = portLibrary->nls_lookup_message (portLibrary,
							  HYNLS_ERROR |
							  HYNLS_DO_NOT_APPEND_NEWLINE,
							  HYNLS_PORT_SL_INTERNAL_ERROR,
							  NULL);
	  portLibrary->str_printf (portLibrary, errBuf, sizeof (errBuf),
				   errorMessage, error);
	  errBuf[sizeof (errBuf) - 1] = '\0';
	  SetErrorMode (prevMode);
	  return portLibrary->error_set_last_error_with_message (portLibrary,
								 notFound ?
								 HYPORT_SL_NOT_FOUND
								 :
								 HYPORT_SL_INVALID,
								 errBuf);
	}

      MultiByteToWideChar (CP_ACP, 0, (LPCTSTR) name, -1, filename,
			   nameSize * 2 + 2);
      filename[nameSize] = '\0';

      FormatMessageW (FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ARGUMENT_ARRAY | FORMAT_MESSAGE_MAX_WIDTH_MASK, NULL, error, MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT),	/* Default language */
		      (LPWSTR) & message, 0, (va_list *) & filename);

      portLibrary->mem_free_memory (portLibrary, filename);

      if (message)
	{
	  WideCharToMultiByte (CP_UTF8, 0, (LPCWSTR) message, -1, errBuf,
			       sizeof (errBuf) - 1, NULL, NULL);
	  LocalFree (message);
	}
      else
	{
	  errorMessage = portLibrary->nls_lookup_message (portLibrary,
							  HYNLS_ERROR |
							  HYNLS_DO_NOT_APPEND_NEWLINE,
							  HYNLS_PORT_SL_INTERNAL_ERROR,
							  NULL);
	  portLibrary->str_printf (portLibrary, errBuf, sizeof (errBuf),
				   errorMessage, error);
	}
      errBuf[sizeof (errBuf) - 1] = '\0';
    }

  SetErrorMode (prevMode);

  return portLibrary->error_set_last_error_with_message (portLibrary,
							 notFound ?
							 HYPORT_SL_NOT_FOUND :
							 HYPORT_SL_INVALID,
							 errBuf);
}
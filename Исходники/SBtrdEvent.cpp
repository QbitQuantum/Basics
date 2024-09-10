// Diagnostic logging
SBTRDUTIL_API_CLASS void
SBtrdEvent::Diag (VXIunsigned tag, const VXIchar *subtag, 
		  const VXIchar *format, ...) const
{
  if ( _log ) {
    if ( format ) {
      va_list arguments;
      va_start(arguments, format);
      (*_log->VDiagnostic)(_log, tag + _diagTagBase, subtag, format, 
			   arguments);
      va_end(arguments);
    } else {
      (*_log->Diagnostic)(_log, tag + _diagTagBase, subtag, NULL);
    }
#if 0
  } else {
    VXIchar temp[1024];
    va_list arguments;
    va_start(arguments, format);
    wcscpy (temp, subtag);
    wcscat (temp, L"|");
    wcscat (temp, format);
    wcscat (temp, L"\n");
    vfwprintf(stderr, temp, arguments);
    va_end(arguments);
#endif
  }
}
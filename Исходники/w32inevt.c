static inline BOOL
w32_read_console_input (HANDLE h, INPUT_RECORD *rec, DWORD recsize,
			DWORD *waiting)
{
  return (w32_console_unicode_input
	  ? ReadConsoleInputW (h, rec, recsize, waiting)
	  : ReadConsoleInputA (h, rec, recsize, waiting));
}
static void
lookup_funcs (void)
{
  HMODULE winhttp = NULL;
  WCHAR winhttp_dll[MAX_PATH + 100];
  int n;

  if (lookup_done)
    return;

  n = GetSystemDirectoryW (winhttp_dll, MAX_PATH);
  if (n > 0 && n < MAX_PATH)
    {
        if (winhttp_dll[n-1] != L'\\' &&
            winhttp_dll[n-1] != L'/')
            wcscat (winhttp_dll, L"\\");
        wcscat (winhttp_dll, L"winhttp.dll");
        winhttp = LoadLibraryW (winhttp_dll);
    }

  if (winhttp != NULL)
    {
      funcs.pWinHttpCloseHandle = (BOOL (WINAPI *) (HINTERNET)) GetProcAddress (winhttp, "WinHttpCloseHandle");
      funcs.pWinHttpCrackUrl = (BOOL (WINAPI *) (LPCWSTR,DWORD,DWORD,LPURL_COMPONENTS)) GetProcAddress (winhttp, "WinHttpCrackUrl");
      funcs.pWinHttpConnect = (HINTERNET (WINAPI *) (HINTERNET,LPCWSTR,INTERNET_PORT,DWORD)) GetProcAddress (winhttp, "WinHttpConnect");
      funcs.pWinHttpCreateUrl = (BOOL (WINAPI *) (LPURL_COMPONENTS,DWORD,LPWSTR,LPDWORD)) GetProcAddress (winhttp, "WinHttpCreateUrl");
      funcs.pWinHttpOpen = (HINTERNET (WINAPI *) (LPCWSTR,DWORD,LPCWSTR,LPCWSTR,DWORD)) GetProcAddress (winhttp, "WinHttpOpen");
      funcs.pWinHttpOpenRequest = (HINTERNET (WINAPI *) (HINTERNET,LPCWSTR,LPCWSTR,LPCWSTR,LPCWSTR,LPCWSTR*,DWORD)) GetProcAddress (winhttp, "WinHttpOpenRequest");
      funcs.pWinHttpQueryDataAvailable = (BOOL (WINAPI *) (HINTERNET,LPDWORD)) GetProcAddress (winhttp, "WinHttpQueryDataAvailable");
      funcs.pWinHttpQueryHeaders = (BOOL (WINAPI *) (HINTERNET,DWORD,LPCWSTR,LPVOID,LPDWORD,LPDWORD)) GetProcAddress (winhttp, "WinHttpQueryHeaders");
      funcs.pWinHttpReadData = (BOOL (WINAPI *) (HINTERNET,LPVOID,DWORD,LPDWORD)) GetProcAddress (winhttp, "WinHttpReadData");
      funcs.pWinHttpReceiveResponse = (BOOL (WINAPI *) (HINTERNET,LPVOID)) GetProcAddress (winhttp, "WinHttpReceiveResponse");
      funcs.pWinHttpSendRequest = (BOOL (WINAPI *) (HINTERNET,LPCWSTR,DWORD,LPVOID,DWORD,DWORD,DWORD_PTR)) GetProcAddress (winhttp, "WinHttpSendRequest");
      funcs.pWinHttpWriteData = (BOOL (WINAPI *) (HINTERNET,LPCVOID,DWORD,LPDWORD)) GetProcAddress (winhttp, "WinHttpWriteData");

      if (funcs.pWinHttpCloseHandle &&
	  funcs.pWinHttpCrackUrl &&
	  funcs.pWinHttpConnect &&
	  funcs.pWinHttpCreateUrl &&
	  funcs.pWinHttpOpen &&
	  funcs.pWinHttpOpenRequest &&
	  funcs.pWinHttpQueryDataAvailable &&
	  funcs.pWinHttpQueryHeaders &&
	  funcs.pWinHttpReadData &&
	  funcs.pWinHttpReceiveResponse &&
	  funcs.pWinHttpSendRequest &&
	  funcs.pWinHttpWriteData)
	funcs_found = TRUE;
    }
  lookup_done = TRUE;
}
/*
 * @implemented
 */
HANDLE WINAPI
RemovePropA(HWND hWnd, LPCSTR lpString)
{
  PWSTR lpWString;
  UNICODE_STRING UString;
  HANDLE Ret;

  if (HIWORD(lpString))
    {
      RtlCreateUnicodeStringFromAsciiz(&UString, (LPSTR)lpString);
      lpWString = UString.Buffer;
      if (lpWString == NULL)
	{
	  return(FALSE);
	}
      Ret = RemovePropW(hWnd, lpWString);
      RtlFreeUnicodeString(&UString);
    }
  else
    {
      Ret = RemovePropW(hWnd, (LPCWSTR)lpString);
    }
  return(Ret);
}
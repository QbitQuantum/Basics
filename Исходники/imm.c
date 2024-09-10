HRESULT WINAPI GetImmFileName(PWSTR lpBuffer, UINT uSize)
{
  UINT length;
  STRSAFE_LPWSTR Safe = lpBuffer;

  length = GetSystemDirectoryW(lpBuffer, uSize);
  if ( length && length < uSize )
  {
    StringCchCatW(Safe, uSize, L"\\");
    return StringCchCatW(Safe, uSize, L"imm32.dll");
  }
  return StringCchCopyW(Safe, uSize, L"imm32.dll");
}  
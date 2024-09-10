/***********************************************************************
 *          RegRestoreAllA (advpack.@)
 *
 * See RegRestoreAllW.
 */
HRESULT WINAPI RegRestoreAllA(HWND hWnd, LPSTR pszTitleString, HKEY hkBackupKey)
{
    UNICODE_STRING title;
    HRESULT hr;

    TRACE("(%p, %s, %p)\n", hWnd, debugstr_a(pszTitleString), hkBackupKey);

    RtlCreateUnicodeStringFromAsciiz(&title, pszTitleString);

    hr = RegRestoreAllW(hWnd, title.Buffer, hkBackupKey);

    RtlFreeUnicodeString(&title);

    return hr;
}
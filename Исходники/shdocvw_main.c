/******************************************************************
 *  URLSubRegQueryA (SHDOCVW.151)
 */
HRESULT WINAPI URLSubRegQueryA(LPCSTR regpath, LPCSTR name, DWORD type,
                               LPSTR out, DWORD outlen, DWORD unknown)
{
    CHAR buffer[INTERNET_MAX_URL_LENGTH];
    DWORD len;
    LONG res;

    TRACE("(%s, %s, %d, %p, %d, %d)\n", debugstr_a(regpath), debugstr_a(name),
            type, out, outlen, unknown);

    if (!out) return S_OK;

    len = sizeof(buffer);
    res = SHRegGetUSValueA(regpath, name, NULL, buffer,  &len, FALSE, NULL, 0);
    if (!res) {
        lstrcpynA(out, buffer, outlen);
        return S_OK;
    }

    return E_FAIL;
}
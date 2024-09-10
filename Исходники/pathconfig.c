/* Search for a prefix value in an environment file (pyvenv.cfg).
   If found, copy it into the provided buffer. */
int
_Py_FindEnvConfigValue(FILE *env_file, const wchar_t *key,
                       wchar_t *value, size_t value_size)
{
    int result = 0; /* meaning not found */
    char buffer[MAXPATHLEN*2+1];  /* allow extra for key, '=', etc. */

    fseek(env_file, 0, SEEK_SET);
    while (!feof(env_file)) {
        char * p = fgets(buffer, MAXPATHLEN*2, env_file);

        if (p == NULL) {
            break;
        }

        size_t n = strlen(p);
        if (p[n - 1] != '\n') {
            /* line has overflowed - bail */
            break;
        }
        if (p[0] == '#') {
            /* Comment - skip */
            continue;
        }

        wchar_t *tmpbuffer = _Py_DecodeUTF8_surrogateescape(buffer, n);
        if (tmpbuffer) {
            wchar_t * state;
            wchar_t * tok = wcstok(tmpbuffer, L" \t\r\n", &state);
            if ((tok != NULL) && !wcscmp(tok, key)) {
                tok = wcstok(NULL, L" \t", &state);
                if ((tok != NULL) && !wcscmp(tok, L"=")) {
                    tok = wcstok(NULL, L"\r\n", &state);
                    if (tok != NULL) {
                        wcsncpy(value, tok, MAXPATHLEN);
                        result = 1;
                        PyMem_RawFree(tmpbuffer);
                        break;
                    }
                }
            }
            PyMem_RawFree(tmpbuffer);
        }
    }
    return result;
}
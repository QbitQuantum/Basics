static int vice_ismsystty(int fd)
{
    intptr_t h_stdin = _get_osfhandle(fd);
    char ntfn_bytes[sizeof(OBJECT_NAME_INFORMATION) + 256 * sizeof(WCHAR)];
    OBJECT_NAME_INFORMATION *ntfn = (OBJECT_NAME_INFORMATION*) ntfn_bytes;
    NTSTATUS status;
    ULONG ntfn_size = sizeof(ntfn_bytes);
    USHORT i, l;
    wchar_t c, *s0;

    memset(ntfn, 0, ntfn_size);
    status = NtQueryObject((HANDLE)h_stdin, ObjectNameInformation, ntfn, ntfn_size, &ntfn_size);

    if (!NT_SUCCESS(status)) {
        return 0;
    }

    l = ntfn->Name.Length;
    s0 = ntfn->Name.Buffer;
    /* Check for "\Device\NamedPipe" */
    {
        USHORT l1 = l;
        wchar_t *s1 = s0;
        wchar_t expect[] = L"\\Device\\NamedPipe\\";

        if (s0[0] == '\\' && s0[1] == '\\' && s0[2] == '?' && s0[3] == '\\') {
            l1 -= 4;
            s1 += 4;
        }
        for (i = 0; i < l1; i++) {
            wchar_t e = expect[i];
            c = s1[i];
            if (!e) {
                break;
            }
            if (c != e) {
                return 0;
            }
        }
    }
    /* Look for "-pty%d-" */
    for (i = 0; i < l; i++) {
        c = s0[i];
        if (c == '-') {
            wchar_t *s = s0 + i + 1;
            if (s[0] == 'p' && s[1] == 't' && s[2] == 'y' && (c = s[3]) && (c >= '0') && (c <= '9'))
            {
                s += 4;
                while ((c = *s) && (c >= '0') && (c <= '9')) {
                    s++;
                }
                if (c == '-' || c == 0) {
                    return 1;
                }
            }
        }
    }

    return 0;
}
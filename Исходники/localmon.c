/******************************************************************
 * does_port_exist (internal)
 *
 * returns TRUE, when the Port already exists
 *
 */
static BOOL does_port_exist(LPCWSTR myname)
{

    LPPORT_INFO_1W  pi;
    DWORD   needed = 0;
    DWORD   returned;
    DWORD   id;

    TRACE("(%s)\n", debugstr_w(myname));

    id = EnumPortsW(NULL, 1, NULL, 0, &needed, &returned);
    pi = heap_alloc(needed);
    returned = 0;
    if (pi)
        id = EnumPortsW(NULL, 1, (LPBYTE) pi, needed, &needed, &returned);

    if (id && returned > 0) {
        /* we got a number of valid names. */
        for (id = 0; id < returned; id++)
        {
            if (lstrcmpiW(myname, pi[id].pName) == 0) {
                TRACE("(%u) found %s\n", id, debugstr_w(pi[id].pName));
                heap_free(pi);
                return TRUE;
            }
        }
    }

    heap_free(pi);
    return FALSE;
}
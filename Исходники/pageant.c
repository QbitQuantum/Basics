// "in" means "to pageant", "out" means "from pageant". Sorry.
int
send_request_to_pageant(byte *inbuf, int inbytes, byte *outbuf, int outbuflen)
{
    EPRINTF(3, "Sending %d bytes to pageant.\n", inbytes);

    if (inbytes < 4) {
        EPRINTF(0, "Pageant-bound message too short (%d bytes).\n", inbytes);
        return 0;
    }
    int claimed_inbytes = GET_32BIT(inbuf);
    if (inbytes != claimed_inbytes + 4) {
        EPRINTF(0, "Pageant-bound message is %d bytes long, but it "
                "*says* it has %d=%d+4 bytes in it.\n",
                inbytes, claimed_inbytes+4, claimed_inbytes);
        return 0;
    }

    EPRINTF(5, "Message to pageant (%d bytes):\n", inbytes);
    print_buf(5, inbuf, inbytes);

    HWND hwnd;
    hwnd = FindWindow("Pageant", "Pageant");
    if (!hwnd) {
        EPRINTF(0, "Can't FindWindow(\"Pageant\"...) - "
                   "is pageant running?. (GetLastError is %x)\n",
                   (unsigned) GetLastError());
        return 0;
    }

    char mapname[512];
    sprintf(mapname, "PageantRequest%08x", (unsigned)GetCurrentThreadId());

    PSECURITY_ATTRIBUTES psa = NULL;
#ifndef NO_SECURITY
    SECURITY_ATTRIBUTES sa = {0};
    if (advapi_initialised || init_advapi()) {
        /*
         * Set the security info for the file mapping to the same as Pageant's
         * process, to make sure Pageant's SID check will pass.
         */

        DWORD dwProcId = 0;
        GetWindowThreadProcessId(hwnd, &dwProcId);
        HANDLE proc = OpenProcess(MAXIMUM_ALLOWED, FALSE, dwProcId);
        if (proc != NULL) {
			sa.nLength = sizeof(sa);
			sa.bInheritHandle = TRUE;
			sa.lpSecurityDescriptor = NULL;
			GetSecurityInfo(proc, SE_KERNEL_OBJECT, OWNER_SECURITY_INFORMATION,
					NULL, NULL, NULL, NULL, (PSECURITY_DESCRIPTOR*)&sa.lpSecurityDescriptor);
			if (sa.lpSecurityDescriptor) {
				psa = &sa;
			}
        }
		CloseHandle(proc);
    } else {
        EPRINTF(0, "Couldn't initialize advapi.\n");
    }
#endif /* NO_SECURITY */

    HANDLE filemap = CreateFileMapping(INVALID_HANDLE_VALUE, psa, 
                                       PAGE_READWRITE, 0, 
                                       AGENT_MAX_MSGLEN, mapname);
    if (filemap == NULL || filemap == INVALID_HANDLE_VALUE) {
        EPRINTF(0, "Can't CreateFileMapping.\n");
        return 0;
    }

    byte *shmem = MapViewOfFile(filemap, FILE_MAP_WRITE, 0, 0, 0);
    memcpy(shmem, inbuf, inbytes);
    COPYDATASTRUCT cds;
    cds.dwData = AGENT_COPYDATA_ID;
    cds.cbData = 1 + strlen(mapname);
    cds.lpData = mapname;

    int id = SendMessage(hwnd, WM_COPYDATA, (WPARAM) NULL, (LPARAM) &cds);
    int retlen = 0;
    if (id > 0) {
        retlen = 4 + GET_32BIT(shmem);
        if (retlen > outbuflen) {
            EPRINTF(0, "Buffer too small to contain reply from pageant.\n");
            return 0;
        }

        memcpy(outbuf, shmem, retlen);

        EPRINTF(5, "Reply from pageant (%d bytes):\n", retlen);
        print_buf(5, outbuf, retlen);
    } else {
        EPRINTF(0, "Couldn't SendMessage().\n");
        return 0;
    }

    // enum_windows();


    UnmapViewOfFile(shmem);
    CloseHandle(filemap);
#ifndef NO_SECURITY
    if (sa.lpSecurityDescriptor)
        LocalFree(sa.lpSecurityDescriptor);
#endif

    EPRINTF(3, "Got %d bytes back from pageant.\n", retlen);

    return retlen;
}
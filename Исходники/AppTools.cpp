void DDEExecute(const WCHAR* server, const WCHAR* topic, const WCHAR* command)
{
    unsigned long inst = 0;
    HSZ hszServer = NULL, hszTopic = NULL;
    HCONV hconv = NULL;
    HDDEDATA hddedata = NULL;

#ifdef _WIN64
    CrashIf(str::Len(command) >= (DWORD)-1);
    if (str::Len(command) >= (DWORD)-1)
        return;
#endif
    UINT result = DdeInitialize(&inst, &DdeCallback, APPCMD_CLIENTONLY, 0);
    if (result != DMLERR_NO_ERROR)
        goto Exit;
    hszServer = DdeCreateStringHandle(inst, server, CP_WINNEUTRAL);
    if (!hszServer)
        goto Exit;
    hszTopic = DdeCreateStringHandle(inst, topic, CP_WINNEUTRAL);
    if (!hszTopic)
        goto Exit;
    hconv = DdeConnect(inst, hszServer, hszTopic, 0);
    if (!hconv)
        goto Exit;
    DWORD cbLen = ((DWORD)str::Len(command) + 1) * sizeof(WCHAR);
    hddedata = DdeCreateDataHandle(inst, (BYTE*)command, cbLen, 0, 0, CF_UNICODETEXT, 0);
    if (!hddedata)
        goto Exit;

    HDDEDATA answer = DdeClientTransaction((BYTE*)hddedata, (DWORD)-1, hconv, 0, 0, XTYP_EXECUTE, 10000, 0);
    if (answer)
        DdeFreeDataHandle(answer);

Exit:
    if (hddedata)
        DdeFreeDataHandle(hddedata);
    if (hconv)
        DdeDisconnect(hconv);
    if (hszTopic)
        DdeFreeStringHandle(inst, hszTopic);
    if (hszServer)
        DdeFreeStringHandle(inst, hszServer);
    DdeUninitialize(inst);
}
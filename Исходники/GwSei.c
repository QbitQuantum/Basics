/**
 * Creates MidpSession for the specified XRPC client id. Invoked on the XRPC
 * thread under synchronization.
 */
STATIC MidpSession* GWENG_MidpCreateSession(EcmtGateway* gw, int xrpcSid)
{
    MidpSession* ses = MEM_New(MidpSession);
    if (ses) {
        LUID luid;
        /* Just in case if AllocateLocallyUniqueId fails... */
        luid.LowPart = (DWORD)ses;
        AllocateLocallyUniqueId(&luid);
        memset(ses, 0, sizeof(*ses));
        ses->key.xrpcSid = xrpcSid;
        ses->key.xrpcSession = XRPC_GetCurrentSession(gw->xrpc);
        ses->sid = luid.LowPart;
        ASSERT(!HASH_Contains(&gw->ecmtSessionMap,(HashKey)ses->sid));
        ASSERT(!HASH_Contains(&gw->midpSessionMap,&ses->key));
        if (HASH_Init(&ses->connMap, 1, NULL, NULL, hashFreeValueProc)) {
            /* Create context for the control connection (number zero) */
            MidpConnection* conn = MEM_New(MidpConnection);
            if (conn) {
                memset(conn, 0, sizeof(*conn));
                if (HASH_Put(&ses->connMap, (HashKey)0, conn)) {
                    if (HASH_Put(&gw->ecmtSessionMap,(HashKey)ses->sid,ses)) {
                        if (HASH_Put(&gw->midpSessionMap, &ses->key, ses)) {
                            if (MUTEX_Init(&ses->xrpcMutex)) {
                                ses->xrpcWorkThread = WKQ_Create();
                                if (ses->xrpcWorkThread) {
                                    ses->xrpcWorkItem = WKI_Create(
                                        ses->xrpcWorkThread, GWENG_AsyncXRpc,
                                        ses);
                                    if (ses->xrpcWorkItem) {
                                        QUEUE_Init(&ses->xrpcQueue);
                                        TRACE3("GW: new session %08x for "
                                            "%08x.%08x\n", ses->sid,
                                            ses->key.xrpcSession,
                                            ses->key.xrpcSid);
                                        return ses;
                                    }
                                    WKQ_Delete(ses->xrpcWorkThread);
                                }
                                MUTEX_Destroy(&ses->xrpcMutex);
                            }
                            HASH_Remove(&gw->midpSessionMap, &ses->key);
                        }
                        HASH_Remove(&gw->ecmtSessionMap, (HashKey)ses->sid);
                    }
                } else {
                    MEM_Free(conn);
                }
            }
            HASH_Destroy(&ses->connMap);
        }
        MEM_Free(ses);
    }
    return NULL;
}
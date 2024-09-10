/*
 * Creates a thread-local key
 */
ThrKey THREAD_CreateKey(ThrClean proc)
{
    ASSERT(THREAD_IsInited());
    if (THREAD_IsInited()) {
        DWORD index = TlsAlloc();
        ASSERT(index != TLS_OUT_OF_INDEXES);
        if (index != TLS_OUT_OF_INDEXES) {
            ThrKey key = MEM_New(struct _ThrKey);
            if (key) {
                key->index = index;
                key->clean = proc;
                key->ref = 1;
                return key;
            }
            TlsFree(index);
        }
    }
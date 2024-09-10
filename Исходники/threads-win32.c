int virThreadLocalInit(virThreadLocalPtr l,
                       virThreadLocalCleanup c)
{
    if ((l->key = TlsAlloc()) == TLS_OUT_OF_INDEXES) {
        errno = ESRCH;
        return -1;
    }
    TlsSetValue(l->key, NULL);

    if (c) {
        virMutexLock(&virThreadLocalLock);
        if (VIR_REALLOC_N(virThreadLocalList,
                          virThreadLocalCount + 1) < 0)
            return -1;
        virThreadLocalList[virThreadLocalCount].key = l->key;
        virThreadLocalList[virThreadLocalCount].cleanup = c;
        virThreadLocalCount++;
        virMutexUnlock(&virThreadLocalLock);
    }

    return 0;
}
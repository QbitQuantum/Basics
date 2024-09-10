UNITEX_FUNC SYNC_Mutex_OBJECT UNITEX_CALL SyncBuildMutex()
{
    SYNC_MUTEX_OBJECT_INTERNAL* pMoi = (SYNC_MUTEX_OBJECT_INTERNAL*)malloc(sizeof(SYNC_MUTEX_OBJECT_INTERNAL));
    if (pMoi == NULL)
        return NULL;
#ifdef UNITEX_USING_WINRT_API
    InitializeCriticalSectionEx(&(pMoi->cs),0,0);
#else
    InitializeCriticalSection(&(pMoi->cs));
#endif

    return (SYNC_Mutex_OBJECT)pMoi;
}
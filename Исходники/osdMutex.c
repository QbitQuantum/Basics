/*
 * epicsMutexOsdTryLock ()
 */
epicsMutexLockStatus epicsMutexOsdTryLock ( epicsMutexOSD * pSem ) 
{ 
    if ( thisIsNT ) {
        if ( TryEnterCriticalSection ( &pSem->os.criticalSection ) ) {
            return epicsMutexLockOK;
        }
        else {
            return epicsMutexLockTimeout;
        }
    }
    else {
        DWORD status = WaitForSingleObject ( pSem->os.mutex, 0 );
        if ( status != WAIT_OBJECT_0 ) {
            if (status == WAIT_TIMEOUT) {
                return epicsMutexLockTimeout;
            }
            else {
                return epicsMutexLockError;
            }
        }
    }
    return epicsMutexLockOK;
}
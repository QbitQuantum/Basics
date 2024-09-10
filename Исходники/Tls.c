BOOL PASCAL EXPORT TlsSetValue(ITLS itls, LPVOID pvParam)
{
    TID tid;
    PTHREAD pthread, pthreadFree;
    LPVOID * ppv;
#if ID_DEBUG
    PID pidTmp;
#endif  //ID_DEBUG

    tid = GETTID(&tid);   // tid = caller's SS

    DebAssert(tid != TID_EMPTY, "");
    DebAssert(itls < ITLS_COMPONENTS, "TlsSetValue err1");
    DebAssert(g_rgbSlot[itls] != 0, "TlsSetValue err2");

    // search for thread's tid field

    pthreadFree = NULL;
    for (pthread = g_rgthread; pthread < g_pthreadEnd; pthread++) {
      if (pthread->tid == tid) {
#if ID_DEBUG
	  GETPID(pidTmp);
	  DebAssert(ISEQUALPID(pidTmp, pthread->pid), "bad pid");
#endif  //ID_DEBUG
	  goto SetValue;	// found it -- set the value
	}
      if ((pthreadFree == NULL) &&
          (pthread->tid == TID_EMPTY)) {
        // remember 1st free thread
        pthreadFree = pthread;
      }
    }
    if (pthreadFree == NULL)
      return FALSE;  // no free slots available for this thread

    // allocate a new THREAD instance
    pthread = pthreadFree;
    GETPID(pthread->pid);

SetValue:
    pthread->rgtls[itls] = pvParam;

    // WARNING: setting of tid must be AFTER the data value is set (directly
    // above).  This is required for the interrupt-driven break check, 
    // which assumes the data is valid if the tid is non-empty.
    //
    pthread->tid = tid;

#if ID_DEBUG
    pthread->rgfSlotUsed[ itls ] = -1;
#endif 
    if (pvParam != NULL)
      return TRUE;

    // See if all of this thread's slots are NULL.
    // If so, release resources occupied by the thread.

    for (ppv = &pthread->rgtls[0];
         ppv < &pthread->rgtls[ITLS_COMPONENTS];
         ppv++) {
      if (*ppv != NULL)
        return TRUE; // at least one slot is still in use by this thread
    }

    // This thread's last field is NULL - release the thread, flush cache

    pthread->tid = TID_EMPTY;
    g_tidThreadCache = TID_EMPTY;
    return TRUE;
}
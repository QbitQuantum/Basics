/* See Porting Layer Definition - p. 6 */
void
winBlockHandler(ScreenPtr pScreen, void *pTimeout)
{
#if defined(XWIN_CLIPBOARD) || defined(XWIN_MULTIWINDOW)
    winScreenPriv(pScreen);
#endif

#ifndef HAS_DEVWINDOWS
    struct timeval **tvp = pTimeout;

    if (*tvp != NULL) {
      if (GetQueueStatus(QS_ALLINPUT | QS_ALLPOSTMESSAGE) != 0) {
        /* If there are still messages to process on the Windows message
           queue, make sure select() just polls rather than blocking.
        */
        (*tvp)->tv_sec = 0;
        (*tvp)->tv_usec = 0;
      }
      else {
        /* Otherwise, lacking /dev/windows, we must wake up again in
           a reasonable time to check the Windows message queue. without
           noticeable delay.
         */
        (*tvp)->tv_sec = 0;
        (*tvp)->tv_usec = 100;
      }
    }
#endif

#if defined(XWIN_CLIPBOARD) || defined(XWIN_MULTIWINDOW)
    /* Signal threaded modules to begin */
    if (pScreenPriv != NULL && !pScreenPriv->fServerStarted) {
        int iReturn;

        winDebug("winBlockHandler - pthread_mutex_unlock()\n");

        /* Flag that modules are to be started */
        pScreenPriv->fServerStarted = TRUE;

        /* Unlock the mutex for threaded modules */
        iReturn = pthread_mutex_unlock(&pScreenPriv->pmServerStarted);
        if (iReturn != 0) {
            ErrorF("winBlockHandler - pthread_mutex_unlock () failed: %d\n",
                   iReturn);
        }
        else {
            winDebug("winBlockHandler - pthread_mutex_unlock () returned\n");
        }
    }
#endif

  /*
    At least one X client has asked to suspend the screensaver, so
    reset Windows' display idle timer
  */
#ifdef SCREENSAVER
  if (screenSaverSuspended)
    SetThreadExecutionState(ES_DISPLAY_REQUIRED);
#endif
}
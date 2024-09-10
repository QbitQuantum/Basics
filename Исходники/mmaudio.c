/**
 * Timer callback used to check about end of media (except JTS type)
 */
static void CALLBACK audio_timer_callback(UINT uID, UINT uMsg, 
                                          DWORD dwUser, 
                                          DWORD dw1, 
                                          DWORD dw2) {
    audio_handle* pHandle = (audio_handle*)dwUser;

    if (pHandle->hWnd) {
        if (-1 == pHandle->duration) {
            pHandle->duration = MCIWndGetLength(pHandle->hWnd);
            JAVA_DEBUG_PRINT1("[jc_media] audio_timer_callback %d\n", 
                pHandle->duration);
        }

        pHandle->offset = MCIWndGetPosition(pHandle->hWnd);
        pHandle->curTime = pHandle->offset;
        
        /* Is end of media reached? */
        if (pHandle->offset >= pHandle->duration) {
            /* Post EOM event to Java and kill player timer */
            pHandle->timerId = 0;
            pHandle->offset = 0;
            timeKillEvent(uID);
            JAVA_DEBUG_PRINT1("[jc_media] javanotify_on_media_notification %d\n", 
                pHandle->playerId);

            javanotify_on_media_notification(JAVACALL_EVENT_MEDIA_END_OF_MEDIA, 
                pHandle->playerId, (void*)pHandle->duration);
        }
    }

}
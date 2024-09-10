/**
 * Called after a WaitForMultipleObjects returned in order to check for pending
 * events and stop whatever actions that rtPipePollStart() initiated.
 *
 * @returns Event mask or 0.
 *
 * @param   hPipe               The pipe handle.
 * @param   fEvents             The events we're polling for.
 * @param   fFinalEntry         Set if this is the final entry for this handle
 *                              in this poll set.  This can be used for dealing
 *                              with duplicate entries.  Only keep in mind that
 *                              this method is called in reverse order, so the
 *                              first call will have this set (when the entire
 *                              set was processed).
 * @param   fHarvestEvents      Set if we should check for pending events.
 */
uint32_t rtPipePollDone(RTPIPE hPipe, uint32_t fEvents, bool fFinalEntry, bool fHarvestEvents)
{
    RTPIPEINTERNAL *pThis = hPipe;
    AssertPtrReturn(pThis, 0);
    AssertReturn(pThis->u32Magic == RTPIPE_MAGIC, 0);

    int rc = RTCritSectEnter(&pThis->CritSect);
    AssertRCReturn(rc, 0);

    Assert(pThis->cUsers > 0);


    /* Cancel the zero byte read. */
    uint32_t fRetEvents = 0;
    if (pThis->fZeroByteRead)
    {
        CancelIo(pThis->hPipe);
        DWORD cbRead = 0;
        if (   !GetOverlappedResult(pThis->hPipe, &pThis->Overlapped, &cbRead, TRUE /*fWait*/)
            && GetLastError() != ERROR_OPERATION_ABORTED)
            fRetEvents = RTPOLL_EVT_ERROR;

        pThis->fIOPending    = false;
        pThis->fZeroByteRead = false;
    }

    /* harvest events. */
    fRetEvents |= rtPipePollCheck(pThis, fEvents);

    /* update counters. */
    pThis->cUsers--;
    if (!pThis->cUsers)
        pThis->hPollSet = NIL_RTPOLLSET;

    RTCritSectLeave(&pThis->CritSect);
    return fRetEvents;
}
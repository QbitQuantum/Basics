RTDECL(int) RTReqQueueProcess(RTREQQUEUE hQueue, RTMSINTERVAL cMillies)
{
    LogFlow(("RTReqQueueProcess %x\n", hQueue));

    /*
     * Check input.
     */
    PRTREQQUEUEINT pQueue = hQueue;
    AssertPtrReturn(pQueue, VERR_INVALID_HANDLE);
    AssertReturn(pQueue->u32Magic == RTREQQUEUE_MAGIC, VERR_INVALID_HANDLE);

    /*
     * Process loop.
     *
     * We do not repeat the outer loop if we've got an informational status code
     * since that code needs processing by our caller.
     */
    int rc = VINF_SUCCESS;
    while (rc <= VINF_SUCCESS)
    {
        /*
         * Get pending requests.
         */
        PRTREQ pReqs = ASMAtomicXchgPtrT(&pQueue->pReqs, NULL, PRTREQ);
        if (!pReqs)
        {
            ASMAtomicWriteBool(&pQueue->fBusy, false); /* this aint 100% perfect, but it's good enough for now... */
            /** @todo We currently don't care if the entire time wasted here is larger than
             *        cMillies */
            rc = RTSemEventWait(pQueue->EventSem, cMillies);
            if (rc != VINF_SUCCESS)
                break;
            continue;
        }
        ASMAtomicWriteBool(&pQueue->fBusy, true);

        /*
         * Reverse the list to process it in FIFO order.
         */
        PRTREQ pReq = pReqs;
        if (pReq->pNext)
            Log2(("RTReqQueueProcess: 2+ requests: %p %p %p\n", pReq, pReq->pNext, pReq->pNext->pNext));
        pReqs = NULL;
        while (pReq)
        {
            Assert(pReq->enmState == RTREQSTATE_QUEUED);
            Assert(pReq->uOwner.hQueue == pQueue);
            PRTREQ pCur = pReq;
            pReq = pReq->pNext;
            pCur->pNext = pReqs;
            pReqs = pCur;
        }


        /*
         * Process the requests.
         */
        while (pReqs)
        {
            /* Unchain the first request and advance the list. */
            pReq = pReqs;
            pReqs = pReqs->pNext;
            pReq->pNext = NULL;

            /* Process the request */
            rc = rtReqProcessOne(pReq);
            AssertRC(rc);
            if (rc != VINF_SUCCESS)
                break; /** @todo r=bird: we're dropping requests here! Add 2nd queue that can hold them. (will fix when writing a testcase)  */
        }
    }

    LogFlow(("RTReqQueueProcess: returns %Rrc\n", rc));
    return rc;
}
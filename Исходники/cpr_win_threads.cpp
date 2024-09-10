/**
 * cprResumeThread
 *
 * Resume execution of a previously suspended thread 
 *
 * Parameters: thread - which system thread to resume
 *
 * Return Value: Success or failure indication
 */
cprRC_t
cprResumeThread(cprThread_t thread)
{
    int32_t returnCode;
    static const char fname[] = "cprResumeThread";
    cpr_thread_t *cprThreadPtr;
	
    cprThreadPtr = (cpr_thread_t*)thread;
    if (cprThreadPtr != NULL) {
		CWinThread *pCWinThread;
		pCWinThread = (CWinThread *)cprThreadPtr->u.handlePtr;
		if (pCWinThread != NULL) {
			
			returnCode = pCWinThread->ResumeThread();
			if (returnCode == -1) {
				CPR_ERROR("%s - Resume thread failed: %d\n",
					fname, GetLastError());
				return(CPR_FAILURE);
			}
			return(CPR_SUCCESS);
		}
		/* Bad application! */
    }
	CPR_ERROR("%s - NULL pointer passed in.\n", fname);
    return(CPR_FAILURE);
};
TCB createNewTCB()
{
    TCB newTCB = (TCB)malloc(sizeof(struct ThreadNodes));
    if(newTCB == NULL)
    {
    	free(newTCB);
        return NULL;
    }
    else
    {
	    newTCB->threadContext.uc_stack.ss_sp = malloc(STACKSIZE);
	    if(newTCB->threadContext.uc_stack.ss_sp == NULL)
	    {
	        free(newTCB);
	        return NULL;
	    }
	    else
	    {
	    	newTCB->threadContext.uc_stack.ss_size = STACKSIZE;
		    newTCB->threadContext.uc_stack.ss_flags = 0;
	    	newTCB->nextThread = NULL;
		    newTCB->threadContext.uc_link = 0;
		    newTCB->threadCompleted = 0;
		    newTCB->waitingThread = NULL;
		    newTCB->threadBlocked = 0;
		    newTCB->threadsWaiting = 0;
            newTCB->roundRobin = 0;
            newTCB->sort = 0;
            newTCB->initialTicket = 0;
            newTCB->finalTicket = 0;
            newTCB->warningLevel = 0;
            newTCB->ultimateWarningLevel = 0;
            newTCB->limitTime = 0;
		    newTCB->detach = 0;
            newTCB->startQuantum = 0;
		    newTCB->threadID = getThreadID();
		    return newTCB;
	    }
    }
}
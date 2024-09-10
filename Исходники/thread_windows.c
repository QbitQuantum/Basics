void
ThreadExit(TThread * const threadP,
           int       const retValue) {

    threadP->threadDone(threadP->userHandle);

    _endthreadex(retValue);
}
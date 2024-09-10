void ExecutionTracker::thrilleAssert(thrID myself,
        void * ret_addr, bool cond) {
    if (!cond) {
        log->programAssertFail(myself, ret_addr);
        destructorHelper();
        _Exit(UNRECOVERABLE_ERROR);
    }
}
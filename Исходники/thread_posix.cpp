void * TThread::EntryPoint(void * pArg) {
    TThread *pThis = (TThread *)pArg;

    // set the routine which cleans up after the thread has finished
    pthread_cleanup_push(SetFinished, pThis);

    try {
        pThis->Run();
    } catch (...) {
        printf("Unknown exception while running thread: %ul!\n", pThis->GetThreadId());
    }

    // pop and execute the cleanup routine
    pthread_cleanup_pop(1);
    return 0;
}
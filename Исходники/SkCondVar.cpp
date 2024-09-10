void SkCondVar::wait() {
#ifdef SK_USE_POSIX_THREADS
    pthread_cond_wait(&fCond, &fMutex);
#elif defined(SK_BUILD_FOR_WIN32)
    SleepConditionVariableCS(&fCondition, &fCriticalSection, INFINITE);
#endif
}
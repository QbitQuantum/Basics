int iaxci_prioboostbegin() {
    if ( !SetThreadPriority(GetCurrentThread(),THREAD_PRIORITY_TIME_CRITICAL)  ) {
        fprintf(stderr, "SetThreadPriority failed: %ld.\n", GetLastError());
    }
    return 0;
}
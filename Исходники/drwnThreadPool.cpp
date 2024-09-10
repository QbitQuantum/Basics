// Destructor
drwnThreadPool::~drwnThreadPool()
{
#ifdef DRWN_USE_PTHREADS
    // tell threads to stop
    if (!_bQuit) {
        _bQuit = true;
        pthread_mutex_lock(&_mutex);
        pthread_cond_broadcast(&_cond);
        pthread_mutex_unlock(&_mutex);

        // wait for them to finish
        for (unsigned i = 0; i < _nThreads; i++) {
            pthread_join(_threads[i], NULL);
        }
    }

    pthread_mutex_destroy(&_mutex);
    pthread_cond_destroy(&_cond);
    if (_threads != NULL) delete[] _threads;
    if (_args != NULL) delete[] _args;
#endif

#ifdef DRWN_USE_WIN32THREADS
    // tell threads to stop
    if (!_bQuit) {
        _bQuit = true;
        WakeAllConditionVariable(&_cond);

        // wait for them to finish
        for (unsigned i = 0; i < _nThreads; i++) {
            WaitForSingleObject(_threads[i], INFINITE);
            CloseHandle(_threads[i]);
        }
    }

    if (_threads != NULL) delete[] _threads;
    if (_args != NULL) delete[] _args;
#endif
}
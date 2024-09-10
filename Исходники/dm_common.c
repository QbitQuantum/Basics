/**
 * Mutex
 */
LPDM_MUTEX mutexNew(const char *name)
{
    LPDM_MUTEX m = NULL;
#ifdef WIN32
    m = CreateMutexA(NULL, FALSE, name);
    if(m == NULL){
        DWORD dwError = GetLastError();
        if(dwError == ERROR_ACCESS_DENIED)
            m = OpenMutexA(SYNCHRONIZE, FALSE, name);
    }
#else
	pthread_mutexattr_t mutexattr;

	pthread_mutexattr_init(&mutexattr);
    m = (LPDM_MUTEX)malloc(sizeof(DM_MUTEX));
    m->context = NULL;
    if(name){
        int mutexexist = 0;
        mutexexist = shm_exist(name);
        m->context = mmapOpen(name, sizeof(pthread_mutex_t));
        m->mutex = (pthread_mutex_t*)m->context->data;
        if(mutexexist)
            return m;
        pthread_mutexattr_setpshared(&mutexattr, PTHREAD_PROCESS_SHARED);
        pthread_mutexattr_setrobust(&mutexattr, PTHREAD_MUTEX_ROBUST);
    }
    else
        m->mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));

	pthread_mutex_init(m->mutex, &mutexattr);
	pthread_mutexattr_destroy(&mutexattr);
#endif
    return m;
}
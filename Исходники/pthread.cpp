/**
@Status Caveat
@Notes Ignores Error codes, ignores error cases
*/
extern "C" int pthread_cond_wait(pthread_cond_t* cond, pthread_mutex_t* mutex) {
    if (*((uint32_t*)cond) == (uint32_t)PTHREAD_COND_INITIALIZER) {
        pthread_cond_init(cond, 0);
    }
    if (*mutex == PTHREAD_MUTEX_INITIALIZER) {
        pthread_mutex_init(mutex, 0);
    }
    SleepConditionVariableCS((CONDITION_VARIABLE*)*cond, (CRITICAL_SECTION*)*mutex, INFINITE);
    return 0;
}
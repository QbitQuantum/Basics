static int pthread_mutex_unlock(pthread_mutex_t *mutex) {
    return ReleaseMutex(*mutex) == 0 ? -1 : 0;
}